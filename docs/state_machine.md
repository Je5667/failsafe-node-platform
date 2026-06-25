# Node State Machines (Master / Slave)

이 플랫폼은 런타임 역할(`NodeRole`)에 따라 서로 다른 상태 머신을 실행합니다. 하나의 리포지토리와 단일 메인 루프에서 Master와 Slave 동작을 분리합니다.

## NodeRole

```c
typedef enum {
    NODE_ROLE_MASTER,
    NODE_ROLE_SLAVE
} NodeRole;
```

`NodeRole`은 `Middleware/Node/node_role.h`에 정의되어 있으며, `NodeRole_Get()`/`NodeRole_Set()` API로 런타임에 변경할 수 있습니다.

## Master state

```c
typedef enum {
    MASTER_INIT,
    MASTER_READY,
    MASTER_MONITORING,
    MASTER_FAULT_MANAGEMENT,
    MASTER_OTA_UPDATE,
    MASTER_ERROR
} MasterState;
```

주요 전이 및 의미

- `MASTER_INIT` -> `MASTER_READY`: 시스템 초기화 완료
- `MASTER_READY` -> `MASTER_MONITORING`: Slave의 Heartbeat 수신 준비
- `MASTER_MONITORING` -> `MASTER_FAULT_MANAGEMENT`: 특정 Slave에 대해 Heartbeat 연속 누락(예: 3회) 발생
- `MASTER_FAULT_MANAGEMENT` -> `MASTER_OTA_UPDATE`: OTA 우선 정책일 경우 OTA 전환 가능
- `MASTER_ERROR`: 내부 오류 발생 시 전이

## Slave state

```c
typedef enum {
    SLAVE_INIT,
    SLAVE_READY,
    SLAVE_ACTIVE,
    SLAVE_WARNING,
    SLAVE_ERROR,
    SLAVE_RECOVERY,
    SLAVE_OTA
} SlaveState;
```

주요 전이 및 의미

- `SLAVE_INIT` -> `SLAVE_READY`: 시스템 초기화 완료
- `SLAVE_READY` -> `SLAVE_ACTIVE`: Master 연결 및 운영 허가 수신
- `SLAVE_ACTIVE` -> `SLAVE_WARNING`: Heartbeat 지연 또는 경고 상태
- `SLAVE_ACTIVE` -> `SLAVE_ERROR`: 치명적 오류 발생
- `SLAVE_ERROR` -> `SLAVE_RECOVERY`: 복구 작업 실행
- `SLAVE_RECOVERY` -> `SLAVE_READY`: 복구 완료
- `SLAVE_OTA`: OTA 적용 중 상태

## Main loop 예시

```c
while (1) {
    if (NodeRole_Get() == NODE_ROLE_MASTER) {
        MasterState_RunInternal();
    } else {
        SlaveState_RunInternal();
    }

    AppTask_Run();
    Heartbeat_Run();
}
```

## Heartbeat 정책

- Slave: 주기적으로 `HeartbeatPacket`을 송신
- Master: 각 Slave의 Heartbeat를 모니터링
- Master가 동일 Slave에 대해 연속으로 3회 Heartbeat를 수신하지 못하면 해당 Slave는 Fault로 간주되고 `MASTER_FAULT_MANAGEMENT`로 전이합니다. 이후 `RecoveryPacket` 전송 및 장애 처리 플로우가 실행됩니다.

## 파일 위치

- 상태 정의 및 API: `Middleware/Node/node_state.h`, `Middleware/Node/node_state.c`
- Node 역할 정의: `Middleware/Node/node_role.h`
- Heartbeat: `Middleware/Heartbeat/heartbeat.h`, `Middleware/Heartbeat/heartbeat.c`
- Fault 관리: `Middleware/FaultManager/fault_manager.h`, `Middleware/FaultManager/fault_manager.c`

## SlaveTable (마스터의 Slave 상태 저장소)

Master는 `SlaveTable`을 사용하여 다수의 Slave 정보를 관리합니다. 주요 API는 다음과 같습니다:

- `SlaveTable_Init()` - 테이블 초기화
- `SlaveTable_Add(nodeId)` - 새로운 Slave 등록
- `SlaveTable_MarkHeartbeat(nodeId, uptimeSec)` - 수신된 Heartbeat로 해당 Slave의 상태/타임스탬프 갱신
- `SlaveTable_CheckTimeouts(timeoutMs, maxMissed)` - 타임아웃 검사 및 missed 카운트 증가, 필요 시 `SLAVE_ERROR` 전이 및 `FaultManager_ReportTimeout()` 호출

구현 위치: `Middleware/Node/slave_table.h`, `Middleware/Node/slave_table.c`

더 상세한 상태 전이 다이어그램과 이벤트 매핑은 추후 추가 문서로 보완할 수 있습니다.

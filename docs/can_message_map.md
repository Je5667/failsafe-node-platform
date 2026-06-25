# CAN Message Map

이 문서는 플랫폼에서 사용하는 CAN 메시지 ID와 각 메시지의 페이로드 형식을 정리합니다. 모든 CAN ID는 `Middleware/Protocol/protocol_packet.h`에서 중앙 정의됩니다.

| 메시지 | CAN ID | 설명 | 페이로드 요약 |
|---|---:|---|---|
| Heartbeat | `CAN_ID_HEARTBEAT` (`CAN_ID_HEARTBEAT_BASE`) | 노드의 생존 및 상태 전송 | nodeId(1) state(1) errorCode(1) uptimeSec(4) |
| Fault Report | `CAN_ID_FAULT_REPORT` | 노드 장애 보고 | nodeId(1) faultCode(1) severity(1) (옵션)detail(<=5) |
| Recovery Command | `CAN_ID_RECOVERY` | 장애 복구/재시작 명령 | targetNodeId(1) action(1) params(<=6) |
| OTA Control | `CAN_ID_OTA_CONTROL` | 원격 펌웨어 업데이트 제어 | command(1) firmwareVersion(4) (옵션)args |
| Node Status | `CAN_ID_NODE_STATUS` | 주기적 상세 상태 | nodeId(1) state(1) cpu(1) mem(1) 기타(<=4) |

요약: 메시지의 괄호 안 숫자는 바이트 수(빅엔디안으로 해석 권장, 필요 시 필드별 명시).

## 페이로드 상세 정의 (예시 C 구조)

```c
/* Protocol-level packet (middleware) */
typedef struct {
	uint32_t id;      /* CAN identifier */
	uint8_t length;   /* DLC */
	uint8_t data[8];  /* up to 8 bytes */
} ProtocolPacket;

/* Heartbeat payload (packed into ProtocolPacket.data) */
typedef struct {
	uint8_t nodeId;
	uint8_t state;       /* NodeState value */
	uint8_t errorCode;
	uint32_t uptimeSec;  /* seconds, big-endian storage */
} HeartbeatPacket;
```

```c
/* Fault report payload */
typedef struct {
	uint8_t nodeId;
	uint8_t faultCode;
	uint8_t severity;
	uint8_t detail[5]; /* optional extra bytes */
} FaultPacket;
```

## 인코딩/전송 규칙

- 모든 수치 필드는 네트워크 바이트 오더(빅엔디안)를 권장합니다. (플랫폼 내부에서 일관되게 처리)
- CAN 프레임은 최대 8바이트(DLC)를 사용합니다. 필요시 페이로드를 여러 프레임으로 분할하는 상위 프로토콜을 설계하세요.
- `ProtocolPacket`은 미들웨어 단에서 사용하며, `CAN_Frame` (하드웨어 레벨)로 직렬화/역직렬화 함수를 제공합니다.

## 예시: Heartbeat 전송 흐름

1. 애플리케이션/미들웨어에서 `HeartbeatPacket hb`를 채움
2. `Protocol_EncodeHeartbeat(&hb, &proto)`로 `ProtocolPacket` 생성
3. `ProtocolPacket`을 `CAN_Frame`로 매핑하여 `CAN_Send()` 호출

간단 예시 코드:

```c
HeartbeatPacket hb = { .nodeId = 1, .state = NODE_ACTIVE, .errorCode = 0, .uptimeSec = 12345 };
ProtocolPacket proto;
/* 가정: Protocol_EncodeHeartbeat fills proto.id/length/data */
Protocol_EncodeHeartbeat(&hb, &proto);
CAN_Frame frame = { .id = proto.id, .extended = 0, .dlc = proto.length };
memcpy(frame.data, proto.data, proto.length);
CAN_Send(&frame);
```

## 예약 및 확장

- CAN ID 범위는 중앙 프로토콜 헤더에서 관리합니다. 새로운 메시지는 `protocol_packet.h`에 추가하고 버전 관리 하세요.
- 다중 프레임 페이로드(파일 전송 등)는 OTA 서브프로토콜을 통해 구현합니다.

## 참고

- 프로토콜 정의 파일: `Middleware/Protocol/protocol_packet.h` 
- 하드웨어 CAN 래퍼: `Hardware/CAN/can_wrapper.h`, `Hardware/CAN/can_wrapper.c`

문서에 없는 특정 필드나 추가 메시지가 필요하면 명세를 확장해 주세요.

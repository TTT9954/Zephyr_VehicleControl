# Zephyr Vehicle Control

A Zephyr RTOS educational example implementing simulated vehicle speed input,
vehicle state machine, speed-limit hysteresis, fault monitoring, and mock CAN
telemetry. **No STM32 hardware is required** for the default build.

## Design notes

- 4 threads: sensor, control, fault, CAN mock
- Latest sensor sample protected by mutex
- Fault status stored atomically
- Control -> CAN via Zephyr `k_msgq`
- Pure logic functions are independently unit-tested with Ztest
- Fault conditions: absent sensor, stale timestamp (>250 ms), speed >250 km/h
- Vehicle states: OFF -> PRE_DRIVE -> DRIVE -> POST_DRIVE
- Speed limiting flag: activate >=90 km/h, release <=87 km/h
- No real torque actuation, safety guarantees, physical CAN or real ADC

See `docs/architecture.md` and `docs/thread_design.md`.

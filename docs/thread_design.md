# Thread design

| Thread | Priority | Timing | Role |
|---|---:|---|---|
| control | 4 | 20 ms sleep | State machine / limiter |
| sensor | 5 | 10 ms sleep | Simulated measurements |
| fault | 6 | 100 ms sleep | Diagnostic checks |
| CAN | 7 | message-driven | Telemetry logging |

Lower numeric priority means higher Zephyr preemptible priority.
`k_msleep` introduces drift; use periodic timers/deadlines for hard timing.
Mutex guards the latest sensor sample, atomics guard the fault flag, and a
message queue connects control to CAN. Threads start after initialization.

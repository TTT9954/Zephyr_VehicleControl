# Architecture

Sensor thread (10 ms) -> Sensor Manager (mutex-protected latest sample)
-> Control thread (20 ms) -> Vehicle state machine + speed limiter
-> Zephyr message queue -> CAN mock thread (event-driven)

Fault thread (100 ms) checks missing/stale/implausible sensor data.

This is an educational demonstration, not a production ECU or safety-certified
system. Speed limiting is a Boolean status indication; it does not actuate torque.
CAN output is logged mock telemetry, not physical bus traffic.

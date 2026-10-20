# Zephyr Vehicle Control (medium-sized learning project)

A Zephyr RTOS educational example implementing simulated vehicle speed input,
vehicle state machine, speed-limit hysteresis, fault monitoring, and mock CAN
telemetry. **No STM32 hardware is required** for the default build.

## Prerequisites

Install Zephyr SDK, Python dependencies, CMake, Ninja and `west` following the
official Zephyr Getting Started Guide: https://docs.zephyrproject.org/latest/develop/getting_started/index.html

Use a properly initialized Zephyr workspace (`west init`, `west update`) and
activate its Python environment before running these commands.

## Build and run (native simulator)

From this project directory:

```sh
west build -b native_sim -d build . -p always
west build -d build -t run
```

If your Zephyr version uses a board qualifier, consult `west boards`.
The app logs mock CAN status periodically. Wait about 20 seconds to observe the
speed limiter turn on as the simulated speed increases.

## Unit tests

```sh
west twister -T tests -p native_sim --inline-logs
```

Alternatively, build a test directly:

```sh
west build -b native_sim -d build_test tests/vehicle_control -p always
west build -d build_test -t run
```

## STM32

For an STM32 board supported by your Zephyr checkout, e.g. `nucleo_f446re`:

```sh
west build -b nucleo_f446re -d build_stm32 . -p always
west flash -d build_stm32
```

This build continues to use **simulated** sensor, GPIO and CAN data. It is not a
hardware driver demonstration until the three files in `src/drivers/` are
adapted to the target board's Devicetree and peripherals. Flash only when the
board is correctly connected and configured.

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

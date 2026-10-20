cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(zephyr_vehicle_control)
target_include_directories(app PRIVATE include)
target_sources(app PRIVATE
 src/main.c src/app/vehicle_control.c src/app/vehicle_state.c src/app/speed_monitor.c
 src/drivers/adc_sensor.c src/drivers/gpio_control.c src/drivers/can_interface.c
 src/services/sensor_manager.c src/services/can_manager.c src/services/fault_manager.c
 src/utils/ring_buffer.c src/utils/data_filter.c)

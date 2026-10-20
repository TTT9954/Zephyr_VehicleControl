Board-specific overlays go here. The default native_sim build needs none.
For STM32, choose an installed Zephyr board target and create an overlay using its
actual DTS node labels. Hardware GPIO/ADC/CAN implementations must then replace
simulation stubs in src/drivers/. Do not enable CAN unless a controller and
transceiver are available and configured.

#include "can_interface.h"
#include "vehicle_state.h"
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(can_iface, LOG_LEVEL_INF);
/* Mock CAN transport for native_sim. Replace with Zephyr CAN API on a board
 * with an enabled CAN controller/transceiver. No physical CAN frames sent. */
void can_interface_send_status(vehicle_status_t s)
{
    LOG_INF("CAN MOCK ID=0x321 state=%s speed=%u limit=%u fault=%u",
            vehicle_state_name(s.state), (unsigned)s.speed_kph,
            (unsigned)s.speed_limited, (unsigned)s.fault_active);
}

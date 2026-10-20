#include "can_manager.h"
#include "can_interface.h"
#include <zephyr/kernel.h>
/* Only the newest status is needed; older telemetry may be discarded. */
K_MSGQ_DEFINE(status_msgq, sizeof(vehicle_status_t), 8, 4);
void can_manager_publish(vehicle_status_t s)
{
    (void)k_msgq_put(&status_msgq, &s, K_NO_WAIT);
}
void can_manager_process(void)
{
    vehicle_status_t s;
    if (k_msgq_get(&status_msgq, &s, K_MSEC(100)) == 0) {
        /* Coalesce queued updates to the most recent status. */
        vehicle_status_t newer;
        while (k_msgq_get(&status_msgq, &newer, K_NO_WAIT) == 0) s = newer;
        can_interface_send_status(s);
    }
}

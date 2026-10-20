#include "vehicle_state.h"
vehicle_state_t vehicle_state_next(vehicle_state_t s, bool ignition, bool ready, bool fault)
{
    switch (s) {
    case VEH_OFF: return ignition ? VEH_PRE_DRIVE : VEH_OFF;
    case VEH_PRE_DRIVE:
        if (!ignition) return VEH_OFF;
        return (ready && !fault) ? VEH_DRIVE : VEH_PRE_DRIVE;
    case VEH_DRIVE:
        return (!ignition || !ready || fault) ? VEH_POST_DRIVE : VEH_DRIVE;
    case VEH_POST_DRIVE:
        return !ignition ? VEH_OFF : VEH_PRE_DRIVE;
    default: return VEH_OFF;
    }
}
const char *vehicle_state_name(vehicle_state_t s)
{
    switch (s) {
    case VEH_OFF: return "OFF";
    case VEH_PRE_DRIVE: return "PRE_DRIVE";
    case VEH_DRIVE: return "DRIVE";
    case VEH_POST_DRIVE: return "POST_DRIVE";
    default: return "UNKNOWN";
    }
}

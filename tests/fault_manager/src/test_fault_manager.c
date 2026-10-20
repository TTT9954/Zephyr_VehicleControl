#include <zephyr/ztest.h>
#include "fault_manager.h"
ZTEST(fault_logic, test_fault_conditions)
{
    fault_manager_update(true, 0, 80);
    zassert_false(fault_manager_active());
    fault_manager_update(true, 251, 80);
    zassert_true(fault_manager_active());
    fault_manager_update(false, 0, 0);
    zassert_true(fault_manager_active());
    fault_manager_update(true, 0, 251);
    zassert_true(fault_manager_active());
    fault_manager_update(true, 0, 80);
    zassert_false(fault_manager_active());
}
ZTEST_SUITE(fault_logic, NULL, NULL, NULL, NULL, NULL);

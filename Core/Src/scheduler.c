#include "scheduler.h"

static sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint32_t SCH_count = 0;
static uint32_t next_task_id = 1;

void SCH_Init(void) {
    SCH_count = 0;
    next_task_id = 1;
    for (uint32_t i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = NO_TASK_ID;
    }
}

void SCH_Update(void) {
    if (SCH_count == 0) return;
    if (SCH_tasks_G[0].Delay > 0) {
        SCH_tasks_G[0].Delay--;
    }
    if (SCH_tasks_G[0].Delay == 0) {
        SCH_tasks_G[0].RunMe = 1;
    }
}

static uint32_t SCH_Add_Task_Internal(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD, uint32_t id) {
    if (SCH_count >= SCH_MAX_TASKS || pFunction == 0) {
        return NO_TASK_ID;
    }

    uint32_t idx = 0;
    uint32_t sum = 0;

    while (idx < SCH_count && (sum + SCH_tasks_G[idx].Delay) <= DELAY) {
        sum += SCH_tasks_G[idx].Delay;
        idx++;
    }

    for (uint32_t i = SCH_count; i > idx; i--) {
        SCH_tasks_G[i] = SCH_tasks_G[i - 1];
    }

    SCH_tasks_G[idx].pTask = pFunction;
    SCH_tasks_G[idx].Delay = DELAY - sum;
    SCH_tasks_G[idx].Period = PERIOD;
    SCH_tasks_G[idx].RunMe = (SCH_tasks_G[idx].Delay == 0) ? 1 : 0;
    SCH_tasks_G[idx].TaskID = id;

    if (idx < SCH_count) {
        SCH_tasks_G[idx + 1].Delay -= SCH_tasks_G[idx].Delay;
    }

    SCH_count++;
    return id;
}

uint32_t SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD) {
    uint32_t id = next_task_id++;
    if (next_task_id == NO_TASK_ID) next_task_id = 1;
    return SCH_Add_Task_Internal(pFunction, DELAY, PERIOD, id);
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
    if (taskID == NO_TASK_ID || SCH_count == 0) return 0;

    uint32_t idx = SCH_count;
    for (uint32_t i = 0; i < SCH_count; i++) {
        if (SCH_tasks_G[i].TaskID == taskID) {
            idx = i;
            break;
        }
    }

    if (idx == SCH_count) return 0;

    if (idx + 1 < SCH_count) {
        SCH_tasks_G[idx + 1].Delay += SCH_tasks_G[idx].Delay;
    }

    for (uint32_t i = idx; i < SCH_count - 1; i++) {
        SCH_tasks_G[i] = SCH_tasks_G[i + 1];
    }

    SCH_count--;
    SCH_tasks_G[SCH_count].pTask = 0;
    SCH_tasks_G[SCH_count].TaskID = NO_TASK_ID;
    return 1;
}

void SCH_Dispatch_Tasks(void) {
    while (SCH_count > 0 && SCH_tasks_G[0].RunMe > 0) {
        void (*pTask)(void) = SCH_tasks_G[0].pTask;
        uint32_t period = SCH_tasks_G[0].Period;
        uint32_t id = SCH_tasks_G[0].TaskID;

        for (uint32_t i = 0; i < SCH_count - 1; i++) {
            SCH_tasks_G[i] = SCH_tasks_G[i + 1];
        }
        SCH_count--;
        SCH_tasks_G[SCH_count].pTask = 0;
        SCH_tasks_G[SCH_count].TaskID = NO_TASK_ID;

        if (pTask != 0) {
            (*pTask)();
        }

        if (period > 0) {
            SCH_Add_Task_Internal(pTask, period, period, id);
        }
    }
}

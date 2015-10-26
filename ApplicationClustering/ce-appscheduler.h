#ifndef APP_SCHEDULER_H
#define APP_SCHEDULER_H

enum APP_SCHEDULE_STATES
{
    APP_STATE_NONE = 0,
    APP_STATE_CHECK,
    APP_STATE_INIT,
    APP_STATE_READY,
    APP_STATE_EXIT,
    APP_STATE_DONE,
    APP_STATE_SUSPEND,
    APP_STATE_SUSPENDED,
    APP_STATE_REMOVE,
    APP_STATE_DELETED,
    APP_STATE_RESERVED
};



#endif

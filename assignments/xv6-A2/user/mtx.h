
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include "user/uthread.h"



int mtx_create(int locked);
int mtx_lock(int lock_id);
int mtx_unlocked(int lock_id);


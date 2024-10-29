/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"


int mtx_create(int locked);
int mtx_lock(int lock_id);
int mtx_unlocked(int lock_id);


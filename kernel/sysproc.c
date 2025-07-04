#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "logger_custom.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_trigger(void)
{
    log_message(INFO, "This is a log to test a new xv6 system call");
    return 0;
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  if (myproc()->current_thread) {
    release(&tickslock);
    sleepthread(n, ticks0); // تابع جدید خواب برای نخ را صدا بزن
    return 0;
  }

  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


uint64
sys_thread(void) {
  uint64 start_thread, stack_address, arg;
  
  // خواندن آرگومان‌ها از فضای کاربر
  argaddr(0, &start_thread);
  argaddr(1, &stack_address);
  argaddr(2, &arg);

  // فراخوانی تابع اصلی برای تخصیص و ساخت نخ (این تابع را بعدا می‌نویسیم)
  struct thread *t = allocthread(start_thread, stack_address, arg);

  // اگر نخ با موفقیت ساخته شد، شناسه آن را برگردان
  return t ? t->id : 0;
}

// تابع sys_jointhread برای پیوستن به یک نخ
uint64
sys_jointhread(void) {
  int id;

  // خواندن شناسه نخ مورد نظر از فضای کاربر
  argint(0, &id);
  
  // فراخوانی تابع اصلی برای پیوستن به نخ (این تابع را بعدا می‌نویسیم)
  return jointhread(id);
}
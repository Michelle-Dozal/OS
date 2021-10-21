#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

//Change for Lab 1
int
sys_exit(void)
{
    int status; //Add Change for Lab 1
    argint(0,&status); //Add for Lab 1
    exit(status); //Change for Lab 1
    return 0;  // not reached
}

//Change for Lab 1
int
sys_wait(void)
{
    int *status; //Add for Lab 1
    argptr(0,(char**)&status,sizeof(*status)); //Add for Lab 1

  return wait(status); //Change for Lab 1
}

//Add for Lab 1
int
sys_waitpid(void)
{
    int pid, *status, options;
    argint(0,&pid);
    argptr(1,(char**)&status, sizeof(status));
    argint(2,&options);
    return waitpid(pid,status,options);

}

//Add for Lab2
void
sys_updatePriority(void)
{
   int np;
   argint(0,&np);
   updatePriority(0,np);
   return;
    /* int pid, np;
    if(argint(0,&pid) < 0)
    {return -1;}
    if(argint(0,&np) < 0)
    {return -1;}

    updatePriority(pid, np);
    return 0;*/
}

//Add for lab2
int
sys_turnaroundT(void){
    int pid;
    if(argint(0,&pid) < 0)
    { return -1;}

    return turnaroundT(pid);

}
//Add for lab2
int
sys_waitingT(void){
    int pid;
    if(argint(9,&pid) < 0){
        return -1;
    }
    return waitingT(pid);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[64];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< 64; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

//looks to see if segemnt id exists
int shm_open(int id, char **pointer) {

//you write this
int i;
int j = 64;
int k = 0;
uint sz = PGROUNDUP(myproc()->sz);
acquire(&(shm_table.lock));
    for(i = 0; i < 64; i++){
        if(j == 64 && shm_table.shm_pages[i].id == 0){
            j = i;
        }
        if(shm_table.shm_pages[i].id == id){
            k = 1;
            mappages(myproc()->pgdir, (char*)sz, PGSIZE, V2P(shm_table.shm_pages[i].frame),PTE_W|PTE_U);
            shm_table.shm_pages[i].refcnt++;
            break;
        }
    }

    if(k == 0 && j < 64){
        shm_table.shm_pages[j].id = id;
        shm_table.shm_pages[j].frame = kalloc();
        memset(shm_table.shm_pages[j].frame,0,PGSIZE);
        mappages(myproc()->pgdir, (char*)sz, PGSIZE, V2P(shm_table.shm_pages[j].frame),PTE_W|PTE_U); //map virtual & physical
        shm_table.shm_pages[j].refcnt++; //if it exists increase referenc count
    }

    myproc()->sz = sz + PGSIZE;
    *pointer = (char *)sz;
    release(&(shm_table.lock));

return 0; //added to remove compiler warning -- you should decide what to return
}

//Looking for shared memory segment in shm_table
int shm_close(int id) {
//you write this too!
int i;
acquire(&(shm_table.lock));
    for(i = 0; i < 64; i++){
        if(shm_table.shm_pages[i].id == id){ //If it fins it decremnt the refernce count
            if(shm_table.shm_pages[i].refcnt > 0){
                shm_table.shm_pages[i].refcnt--;
            }
            if(shm_table.shm_pages[i].refcnt == 0){ //if it reaches 0 then clear the table
                shm_table.shm_pages[i].id = 0;
                shm_table.shm_pages[i].frame = 0;
                break;
            }
        }
    }

release(&(shm_table.lock));

return 0; //added to remove compiler warning -- you should decide what to return
}

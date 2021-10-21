#include "types.h"
#include "user.h"
#include "stat.h"


int main(int argc, char*argv[])
{
    //int pid;
   // pid = fork();
    updatePriority(0, 20);
    int i, k;
    for(i = 0; i < 5000; i++) {
        asm("nop");
        for (k = 0; k < 1000; k++) {
            asm("nop");
        }
    }

    exit(0);
}
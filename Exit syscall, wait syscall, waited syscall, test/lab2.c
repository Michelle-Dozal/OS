#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char*argv[])
{

    //int pid;
   //pid = fork();
    updatePriority(0, 10);
    int i, k;
    for(i = 0; i < 5000; i++) {
        asm("nop");
        for (k = 0; k < 1000; k++) {
            asm("nop");
        }
    }
    printf(0,"\n Lab2 is set with priority 10, lab22 is set with priority 20, & lab 23 is set with priority 30.\n");
    exit(0);
}



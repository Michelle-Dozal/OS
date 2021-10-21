#include "types.h"
#include "user.h"
int waitPid(void); //Function declaration

int main(int argc, char*argv[])
{
    printf(1,"\nShowing Lab1 waitpid Correctness\n");
    waitPid(); //Calling to test

    exit(0);
}
int waitPid(void)
{
    int pid, exitstatus;
    int pid_test[3] = {0,0,0};
    int i;

    for(i = 0; i < 3; i++){
        pid_test[i] = fork();

        if(pid_test[i] == 0){ //Then the child has executed the code
            printf(1, "\n Child has PID# %d and will exit with status %d\n", getpid(),getpid()+4);
            exit(getpid()+4);
        }
    }

    sleep(5);
    printf(1, "\n Waiting for child with PID# %d\n", pid_test[2]);
    pid = waitpid(pid_test[2],&exitstatus,0);
    printf(1, "\n Child with PID# %d has exited with status %d\n", pid, exitstatus);
    sleep(5);
    printf(1, "\n Waiting for child with PID# %d\n", pid_test[0]);
    pid = waitpid(pid_test[0],&exitstatus,0);
    printf(1, "\n Child with PID# %d has exited with status %d\n", pid, exitstatus);
    sleep(5);
    printf(1, "\n Waiting for child with PID# %d\n", pid_test[1]);
    pid = waitpid(pid_test[1],&exitstatus,0);
    printf(1, "\n Child with PID# %d has exited with status %d\n", pid, exitstatus);

    return 0;
}

/* 
 * proc3.c - the parent program
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    printf("fork program starting\n");
    pid = fork();
    switch(pid) 
    {
    case -1:
        exit(1);
    case 0:
        execl("child", "child", (char *) 0);
        //execve("./child", (char *) 0, (char *) 0);
        exit(1);	/* should never get here */	
    default:
		printf("Process[%d]: parent in execution ...\n", getpid()); 
        sleep(2);
	    if (wait(NULL) > 0) /* waiting for child */ 
   			printf("Process[%d]: parent terminating child ...\n", getpid()); 
  	    printf("Process[%d]: parent terminating ...\n", getpid()); 
        exit(0);   
    }   
}


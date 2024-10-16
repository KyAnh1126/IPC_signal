#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

// handle signal 
void sig_handler(int signo) {
    if(signo == SIGINT) {
        printf("child: received SIGINT, but wont terminate\n");
    }
}

int main() {
    int pid = fork();

    if(pid < 0) {
        perror("create process");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        printf("this is child process, pid = %d\n", pid);
        signal(SIGINT, sig_handler); //register SIGNIT signal to perform sig_handler() function
        printf("child: registered SIGINT\n");

        for(int i = 0; i < 5; ++i) {
            printf("child doing some work, i = %d\n", i);
            sleep(1);
        }

        printf("child: finished\n");

    }

    else {
        printf("this is parent process, pid = %d\n", pid);
        
        sleep(2); //assume parent doing some work

        kill(pid, SIGINT); //send SIGNIT to child

        wait(NULL); //wait for child, program terminate if parent process terminate (even if child process not terminate yet)
        printf("parent: finished\n");
    }

    return 0;
}

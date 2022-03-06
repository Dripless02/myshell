#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>


#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

extern char** environ;
int pid, status, error;
void clear()
{
    if((pid = fork())==0){                      // child proccess
        error= execlp("clear", "clear", NULL);  // exec clear command
        if(error!=0){
            printf(" %s \n", "Cannot clear");   // error message
    }
        }else{
            wait(&status);
    }
}

void greeting()
{
    clear();
    printf("\n\n\n\n******************" // initial message
        "***************************");
    printf("\n\n\t********MY FIRST SHELL**********");
    printf("\n\n\t***********-ENJOY!**************");
    printf("\n\n\n\n*******************"
        "**************************");
    printf("\n");
}

void cd(char *d){
    
    chdir(d); // change the directory
    char cwd[1024]; // holder for current directory
    setenv("PWD", getcwd(cwd, sizeof(cwd)),1); //set new pwd
}

void prompt()
{
    char cwd[256];  // initialize the size of the cwd
    getcwd(cwd, sizeof(cwd)); 
    printf("<%s>", cwd);
}

void envir()
{
    for(int i=0;environ[i]; i++) //   for each line where the environment exists
    {
        printf("%s \n",environ[i]); // print the environment
    }
    
}

void dir(char * S_path, char ** args){
int pid, error, status;
    if((pid = fork())==0){
        if (!args[1]){                                              // if no second argument exists
            error = execlp("ls", "ls", "-al", S_path, NULL);        // excute the ls command with the path
            }
        else{
           error = execlp("ls", "ls", "-al", args[1], NULL);        // execute the ls command with the argument

        }
        if(error < 0){
            printf("error code = %d\n", errno); // error code if the directory does not exist
        }
    }
    else{
        wait(&status);
    }   
}

// Afolabi Fatogun 20409054
// I acknowledge DCU's academic integrity policy

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
            printf(" %s \n", "Cannot clear");   // if the fork fails, error message
    }
        }else{
            wait(&status);
    }
}

void greeting()
{

    sleep(1);
    clear();
    printf("\n\n\n*********************************************");
    printf("\n\n**************MY FIRST SHELL*****************");
    printf("\n\n*************AFOLABI FATOGUN*****************");
    printf("\n\n*********************************************");
    printf("\n");
}

void cd(char *d){
    
    chdir(d);                                       // change the directory
    char cwd[1024];                                 // holder for current directory
    setenv("PWD", getcwd(cwd, sizeof(cwd)),1);      //set new pwd
}

void prompt()
{
char cwd[256];                                      // initialize the size of the cwd
    getcwd(cwd, sizeof(cwd));                       // get current working directory
    printf("<%s>", cwd);                            // print
}

void envir(char ** args, int track)
{
    int k = 0;
    int status;
    switch (fork()){
        case -1:
        fprintf(stderr, "error forking");
        case 0:
        
        while(args[k]){
        if (!strcmp(args[k], "<")){                     // checks for pipe symbol
                freopen(args[k+1], "r", stdin);         //opens the file after the pipe symbol and reads from it
                args[k] = NULL;                         // make args[k] null to avoid problems

            }
            else if (!strcmp(args[k], ">")){            // checks for pipe symbol
                freopen(args[k+1], "w", stdout);        //opens the file after the pipe symbol and writes to it
                args[k] = NULL;                         // make args[k] null to avoid problems
                break;
            }
            else if (!strcmp(args[k], ">>")){           // checks for pipe symbol
                freopen(args[k+1], "a", stdout);        //opens the file after the pipe symbol and appends to it
                args[k] = NULL;                         // make args[k] null to avoid problems
                break;
            }
            k++;

        }

    for(int i=0;environ[i]; i++)                        //   for each line where the environment exists
        {
        printf("%s \n",environ[i]);                     // print the environment
        }
    freopen("/dev/tty", "a", stdout);                   // reopen and close the file after execution
    _exit(0);                                           // exit child process
        
        default:
            if(track == 0){                             // if the command has not been marked for background execution
            wait(&status);
            }
    }
}
    


void dir(char * S_path, char ** args, int track){
    int k = 0;
    int status;
    switch (fork()){
        case -1:
        fprintf(stderr, "error forking");
        case 0:
        
        while(args[k]){
            if (!strcmp(args[k], "<")){                     // checks for pipe symbol
                freopen(args[k+1], "r", stdin);             //opens the file after the pipe symbol and reads from it
                args[k] = NULL;                             // make args[k] null to avoid problems

            }
            else if (!strcmp(args[k], ">")){                // checks for pipe symbol
                freopen(args[k+1], "w", stdout);            //opens the file after the pipe symbol and writes to it
                args[k] = NULL;                             // make args[k] null to avoid problems
                break;
            }
            else if (!strcmp(args[k], ">>")){               // checks for pipe symbol
                freopen(args[k+1], "a", stdout);            //opens the file after the pipe symbol and appends to it
                args[k] = NULL;                             // make args[k] null to avoid problems
                break;
            }
            k++;

        }
        if (!args[1]){                                      // if no second argument exists
            execlp("ls", "ls", "-al", S_path, NULL);        // excute the ls -al command with the path
                }
        else if (args[1]){
            execlp("ls", "ls", "-al", args[1], NULL);        // execute the ls -al command with the argument

            }
        freopen("/dev/tty", "a", stdout);                   // reopen and close the file after execution
        _exit(0);                                           // exit child process
        
        default:
        if (track == 0){                                    // if the command has not been marked for background execution
            wait(&status);
        }
    }
}


void help(char ** args, int track)
{
    int k = 0;
    int status;
    
    switch (fork()){
        //https://man7.org/linux/man-pages/man2/fork.2.html
        case -1:
        fprintf(stderr, "error forking");               // error message
        case 0:                                         // child process
        
        while(args[k]){
            if (!strcmp(args[k], "<")){                 // checks for pipe symbol
                freopen(args[k+1], "r", stdin);         //opens the file after the pipe symbol and reads from it
                args[k] = NULL;                         //set the pipe to null

            }
            else if (!strcmp(args[k], ">")){            // checks for pipe symbol
                freopen(args[k+1], "w", stdout);        //opens the file after the pipe symbol and writes to it
                args[k] = NULL;                         //set the pipe to null
                break;
            }
            else if (!strcmp(args[k], ">>")){           // checks for pipe symbol
                freopen(args[k+1], "a", stdout);        //opens the file after the pipe symbol and appends to it
                args[k] = NULL;                         // set the pipe to null
                break;
            }
            k++;

            execlp("more", "more", strcat(getenv("STARTPWD"), "/../manual/readme.md"),  NULL);  // using the more variable 

        }


        
        default:
        if (track == 0){                                // if the command has not been marked for background execution
            wait(&status);
        }
    }
}

void echo(char ** args, int track){
    int k = 0;
    int status;
    char ** arg;
    switch (fork()){
        case -1:
        fprintf(stderr, "error forking");           // error message
        case 0:                                     // child process
        
        while(args[k]){
            if (!strcmp(args[k], "<")){             // checks for pipe symbol
                freopen(args[k+1], "r", stdin);     //opens the file after the pipe symbol and reads from it
                args[k] = NULL;

            }
            else if (!strcmp(args[k], ">")){        // checks for pipe symbol
                freopen(args[k+1], "w", stdout);    //opens the file after the pipe symbol and writes to it
                args[k] = NULL;
                break;
            }
            else if (!strcmp(args[k], ">>")){       // checks for pipe symbol
                freopen(args[k+1], "a", stdout);    //opens the file after the pipe symbol and appends to it
                args[k] = NULL;
                break;
            }
            k++;

        }
        arg = &args[1];                         // define arg as pointer to args[1]
        while(*arg)
            fprintf(stdout,"%s ",*arg++);       // while the arguments from arg[1] onwards exist, print them to stdout
        fprintf(stdout,"\n");
        freopen("/dev/tty", "a", stdout);           // reopen the last file 
        _exit(0);

        
        default:
        if (track == 0){                        // if the command has not been marked for background execution
            wait(&status);
        }
    } 
}

int backgroundExec(char ** args){
    int j = 0;                          
    int track = 0;
    while(args[j]){                             // while j
        if (!strcmp (args[j], "&")){            // if the ampersand symbol exists in the argument
            track = 1;                          // track = 1
            args[j] = NULL;             

        }

        j++;
    }
    return track;                               // return track number
}
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "myshell.h"



#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators


 /* check for internal/external command */
void Commands(char * argument, char ** args){                     
                     // pointers to arg strings
    char ** arg;
    if (argument) {                             // if there's anything there
        if (!strcmp(argument,"clear")) {        // "clear" command
            clear();

        }

        if (!strcmp(argument,"quit")){      // "quit" command
            printf("Closing Shell...\n");
            exit(0);                        // break out of 'while' loop
        }

        if (!strcmp(argument,"echo")){      // "echo" command
            arg = &args[1];
            while(*arg)
                fprintf(stdout,"%s ",*arg++);
            fprintf(stdout,"\n");

        }
        if (!strcmp(argument,"pause")){     // "pause" command
            getpass("Press Enter to continue...");

        }
        
        if (!strcmp(argument,"dir") || !strcmp(argument,"ls")){ // "dir/ls" command
            char S_path[256];
            getcwd(S_path, 256);                // get the current working directory
            dir(S_path, args);                  // run the dir command

        }

        if (!strcmp(argument, "cd")){           // "cd" command
            if (args[1] == NULL) {              // if the arg doesnt exist
                char cwd[256];
                getcwd(cwd, sizeof(cwd));
                printf("%s\n", cwd);            // print the current working directory
            }
            else{
                cd(args[1]);                    // else run the arg through the cd function
            }
        }
        
        if (!strcmp(argument, "environ")){      // "environ" command
            envir();

        }
        

}

}


void tokenize(int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;
    int len = argc;
    int k = 0;


    /*IO Redirection*/
    while(argv[k]){
        if (!strcmp(argv[k], ">>")){       // checks for pipe symbol
            freopen(argv[k+1], "w", stdout);
        }
        else if (!strcmp(argv[k], ">>")){       // checks for pipe symbol
            freopen(argv[k+1], "a", stdout);
        }
        k++;
    }

    /* Batch Mode Execution*/
    FILE * argument;
    if (len == 1){
        argument = stdin;
    }
    else{
        argument = fopen(argv[1], "r");
    }

    
    while (!feof(argument)) { // keep reading input until "quit" command or eof of redirected input
        if(len == 1){
            prompt(); //get command line from input
        }    
        if (fgets (buf, MAX_BUFFER, argument )) { // read a line
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // tokenise input

            while ((*arg++ = strtok(NULL,SEPARATORS)));
        }
        if (args[0]){
            Commands(args[0], args); // call the command function which runs through a list of commands
            continue;
            arg = args;
            

            /*Else print the command name */
        
            while (*arg) {
                fprintf(stdout,"%s ",*arg++);
                fputs ("\n", stdout);
                }
            }
        }
}
        

int main (int argc, char ** argv)
{
    greeting(); // call the greeting function
    tokenize(argc, argv);
    
    return 0;

}

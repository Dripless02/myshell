#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "myshell.h"



#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators


 /* check for internal/external command */
void Commands(char * argument, char ** args){                     
    /*IO Redirection*/
    int k = 0;
    
    while(args[k]){
        if (!strcmp(args[k], ">>")){       // checks for pipe symbol
            freopen(args[k+1], "a", stdout);
            args[k] = NULL;
        }
        else if (!strcmp(args[k], ">")){       // checks for pipe symbol
            freopen(args[k+1], "w", stdout);
            args[k] = NULL;
        }
        else if (!strcmp(args[k], "<")){       // checks for pipe symbol
            freopen(args[k+1], "r", stdin);
            args[k] = NULL;
        }
        k++;
        continue;
    }



    char ** arg;
    if (argument) {                             // if there's anything there
        if (!strcmp(argument,"clear")) {        // "clear" command
            clear();

        }

        else if (!strcmp(argument,"quit")){      // "quit" command
            printf("Closing Shell...\n");
            sleep(1);
            exit(0);                        // break out of 'while' loop
        }

        else if (!strcmp(argument,"echo")){      // "echo" command
            arg = &args[1];
            while(*arg)
                fprintf(stdout,"%s ",*arg++);
            fprintf(stdout,"\n");

        }
        else if (!strcmp(argument,"pause")){     // "pause" command
            getpass("Press Enter to continue...");

        }
        
        else if (!strcmp(argument,"dir") || !strcmp(argument,"ls")){ // "dir/ls" command
            char S_path[256];
            getcwd(S_path, 256);                // get the current working directory
            dir(S_path, args);                  // run the dir command

        }

        else if (!strcmp(argument, "cd")){           // "cd" command
            if (args[1] == NULL) {              // if the arg doesnt exist
                char cwd[256];
                getcwd(cwd, sizeof(cwd));
                printf("%s\n", cwd);            // print the current working directory
            }
            else{
                cd(args[1]);                    // else run the arg through the cd function
            }
        }
        
        else if (!strcmp(argument, "environ")){      // "environ" command
            envir();

        }
        else if (!strcmp(argument, "help")){      // "environ" command
            help();

        }
    
        else{                                      // If the command is not an internall command, procced to run the external command function
            othercommands(args[0], args);
        }
        

}

}


void tokenize(int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;
    int len = argc;


    /* Batch Mode Execution*/
    FILE * argument;
    if (len == 1){
        argument = stdin;
    }
    else{
        argument = fopen(argv[1], "r");
    }

    
    while (!feof(argument)) { // keep reading input until "quit" command or eof of redirected input
        prompt();
 
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

// Afolabi Fatogun 20409054
// I acknowledge DCU's academic integrity policy


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "myshell.h"



#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators


/* check for internal/external command */
void Commands(char * argument, char ** args, int track){                     

if (argument){                             // if there's anything there
    if (!strcmp(argument,"clear") || (!strcmp(argument, "clr"))) {        // "clear" command
        clear();

    }

    else if (!strcmp(argument,"quit")){                     // "quit" command
        printf("Closing Shell...\n");
        sleep(1);
        exit(0);                    
    }

    else if (!strcmp(argument,"echo")){                     // "echo" command
        echo(args, track);

}

    
    else if (!strcmp(argument,"pause")){                    // "pause" command
        getpass("Press Enter to continue...");              // get pass waits for the input of Enter to continue and prints the message

    }
    
    else if (!strcmp(argument,"dir")){                      // "dir/ls" command
        char S_path[256];
        getcwd(S_path, 256);                                // get the current working directory
        dir(S_path, args, track);                           // run the dir command

    }

    else if (!strcmp(argument, "cd")){                        // "cd" command
        if (args[1] == NULL) {                               // if the arg doesnt exist
            char cwd[256];                                   //set cwd variable to 256
            getcwd(cwd, sizeof(cwd));      
            printf("%s\n", cwd);                            // print the current working directory
        }
        else{
            cd(args[1]);                                    // else run the arg through the cd function
        }
    }
    
    else if (!strcmp(argument, "environ")){                 // "environ" command

        envir(args, track);

    }
    else if (!strcmp(argument, "help")){                    // "environ" command
        help(args, track);


    }
    else{
        int k = 0;
        int status;
        switch (fork()){
            case -1:
            fprintf(stderr, "error forking");               // if the forking fails an error message will be displayed
            case 0:
            
            while(args[k]){
                if (!strcmp(args[k], "<")){                 // checks for pipe symbol
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
            execvp(args[0], args);                          // execute external commands
            _exit(0);                          
            if (track == 0){                                // if the command has not been marked for background execution
                wait(&status);
            }
        }
    }


}


}

void tokenize(int argc, char ** argv)
{
    char buf[MAX_BUFFER];                           // line buffer
    char * args[MAX_ARGS];                          // pointers to arg strings
    char ** arg;
    int len = argc;


    /* Batch Mode Execution*/
    FILE * argument;                                // argument is of type file
    if (len == 1){                                  // if there is only one argument on the line
        argument = stdin;                           // set argument as stdin
    }
    else{
        argument = fopen(argv[1], "r");             // else, argument is the file at pos 2
    }

    
    while (!feof(argument)) {                       // keep reading input until "quit" command or eof of redirected input
        prompt();
 
        if (fgets (buf, MAX_BUFFER, argument )) {   // read a line
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);        // tokenise input

            while ((*arg++ = strtok(NULL,SEPARATORS)));
        }
        if (args[0]){
            int track = backgroundExec(args);       // gets the track int from the backgroundExec function
            Commands(args[0], args, track);         // call the command function which runs through a list of commands
            continue;
            }
        }
}
        

int main (int argc, char ** argv)
{
    greeting();                                     // call the greeting function
    tokenize(argc, argv);                           // calls the tokenize function
    return 0;
}

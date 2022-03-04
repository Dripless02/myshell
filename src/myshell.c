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





void commands(int len, char **argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;


    /* keep reading input until "quit" command or eof of redirected input */
    while (!feof(stdin)) {

        prompt(); //* get command line from input */

        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
            /* tokenize the input into args array */
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // tokenise input

            while ((*arg++ = strtok(NULL,SEPARATORS)));

            if (args[0]) {                   // if there's anything there
            /* check for internal/external command */
            if (!strcmp(args[0],"clear")) { // "clear" command
                clear();
                continue;
            }

            if (!strcmp(args[0],"quit")){   // "quit" command
                printf("Closing Shell...\n");
                break;                 // break out of 'while' loop
            }

            if (!strcmp(args[0],"echo")){   // "echo" command
                arg = &args[1];
                while(*arg)
                    fprintf(stdout,"%s ",*arg++);
                fprintf(stdout,"\n");
                continue;
            }
            if (!strcmp(args[0],"pause")){   // "pause" command
                getpass("Press Enter to continue...");
                continue;
            }
             // "dir/ls" command
            
            if (!strcmp(args[0],"dir") || !strcmp(args[0],"ls")){
                char S_path[256];
                getcwd(S_path, 256);
                dir(S_path, args);
                continue;
            }

            if (!strcmp(args[0], "cd")){ // "cd" command
                if (args[1] == NULL) { // if the arg doesnt exist
                    char cwd[256];
                    getcwd(cwd, sizeof(cwd));
                    printf("%s\n", cwd); // print the current working directory
                }
                else{
                    cd(args[1]); // else run the arg through the cd function
                }
                continue;
            }
            
            if (!strcmp(args[0], "environ")){ // "environ" command
                envir();
                continue;
            }
            /* else pass command onto OS (or in this instance, print them out) */
            arg = args;
            while (*arg) {
                fprintf(stdout,"%s ",*arg++);
                fputs ("\n", stdout);
            }
        }
    }
    }
}

int main (int argc, char ** argv)
{
    int len = argc; // set the length of argument
    greeting(); // call the greeting function
    commands(len, argv);
    return 0;

}

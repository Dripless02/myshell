
NAME 
        myshell
    
COPYRIGHT
        Use at your own risk!

DESCRIPTION
        myshell is a simple command line interpreter which supports basic shell processes and commands.

SUPPORTED COMMANDS
        myshell supports a list of basic internal commands and external commands.

        cd - This command changes the current working directory to directory indicated by the next
        argument after the command. It also changes the PWD environment variable.
        If the  indicated directory does not exist, an error message is reported.

        clear - The clear command removes clutter from the shell and starts the 
        prompt from the top of the shell.

        dir - This command lists the contents of a directory. When used alone, it gives the 
        contents of the CWD, otherwise it gives the contents of the target directory.

        environ - Displays a list of all environment strings.

        echo - displays the following argument(s) on a new line.

        help - displays this manual.

        pause - Temporarily halts the shell operation until the enter button is pressed.

        quit - Closes the shell.

ENVIRONMENT CONCEPT
        The shell environment is a set of name-value pairs that provide information

        on the form of your prompt, your home directory, your working directory, the

        name of your shell, files that you have opened, functions that you have defined, and more.

        The environment can be viewed in the shell by using the "environ" command.

I/O REDIRECTION
        I/O redirection allows a user to redirect commands or files to and from other files

        using a command pipeline or pipes denoted by, ">", ">>", "<". I/O redirection supports the 

        following commands; dir, environ, echo, and help.

        An example of execution of this wuould be:

                programname arg1 arg2 < inputfile > outputfile



PROCESS CONCEPT
        A process is a unit of work inputed into the shell to be executed. myshell accepts units of
        work and executes them as either foreground or background processes.

        SEE BELOW FOR INFORMATION ON FOREGROUND AND BACKGROUND PROCESSES!



FOREGROUND AND BACKGROUND PROCESSES
        A foreground process is a process run directly in the shell and wait for it to be complete.
        One foreground process has to be ended before another can begin.

        A background process on the other hand does not have to be completed before the shell can 
        run other commands. To run a command in the background process, type out the command followed 
        by and ampersand "&" symbol.

                An example of running a foreground process is, "echo hello".
                An example of running a background process is, "echo hello &"


        NOTE: the "&" symbol must be seperated from the rest of the command by a space.



SOURCES
        https://www.geeksforgeeks.org/difference-fork-exec/
        https://www.geeksforgeeks.org/io-redirection-c/
        https://linux.die.net/man/1/bash
        https://man7.org/linux/man-pages/man2/exit.2.html
        https://man7.org/linux/man-pages/man4/tty.4.html
        https://man7.org/linux/man-pages/man2/fork.2.html

AUTHOR
        Afolabi Fatogun

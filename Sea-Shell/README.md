
# THE SEA-SHELL 

### INTRODUCTION :
My shell is the implementation of a Linux shell.

----------------------------------------------------------------------------------------------------------

### RUN:
Run ‘make main’ in the terminal.
Then run ./a.out
SEA_SHELL opens up; you can run your command here.

----------------------------------------------------------------------------------------------------------

### FEATURES:
Displaying prompt with a user name and system name and current working directly.

##### pwd :

Syntax - `pwd`

Description - prints present working directory as the output.
            It is implemented in path.c file in pwd() function.

##### cd :
    
Syntax - `cd <space> or cd <path>`

Description - changes the working directory with the path specified. Handles “.” , “..” , “~”, “-” .
            `cd <space>` changes current working directory to home directory.

Error Handling - if the directory is not present for the current path.

It is implemented in path.c file in cd() function.

##### echo :
    
Syntax - `echo <text>`

Description - prints the text given as the output.

It is implemented in echo.c file in echo() function.

##### ls :
    
Syntax - `ls <space> or ls <path> or ls <flag> <path>`

Description - prints details of the directory with the path specified. Handles “.” , “..” , “~” .

Error Handling - if the directory is not present for the current path.

It is implemented in ls.c file in ls() function.

##### pinfo :

Syntax - `pinfo <space> or pinfo <pid>`

Description - prints details of the process with the pid specified or current process if pid is not specified.

Error Handling - if the pid is not present.

It is implemented in process.c file in pinfo() function.

##### System process :
    
Syntax - `<command> <space> or <command> <file>`

Description - Runs the command at foreground and background if & is specified.

Error Handling - If the process does not exist then error is displayed.

It is implemented in syscmd.c file in syscmd() function.
    
Finishing the process : 
    
On the finish of the background processes message is displayed.

##### history :
    
Syntax - `history <space> or history <no_of_lines>`.

Description - Displays the last given number of commands entered output. At max, only the last 20 commands can be traced. For history only it gives the last 10 commands.

It is implemented in history.c file in history() function.

##### setenv :
    
Syntax - `setenv <var> [value]`.

Description - It creates an environment variable if not exists or changes the value with given value. If the value is not mentioned then replace it with empty value.

Error Handling - if required number of arguments are not given then it throws error.

It is implemented in intercmd.c file in setenv() function.

##### unsetenv :
    
Syntax - `unsetenv <var>`.

Description - It deletes an environment variable. 

Error Handling - if required number of arguments are not given then it throws error. If not exists then throws the error.

It is implemented in intercmd.c file in unsetenv() function.

##### jobs :
    
Syntax - `jobs`.

Description - shows details of all the current background. 

It is implemented in process.c file in jobs() function.

##### kjob :
    
Syntax - `kjob <job number> <signal number>`.

Description - Sends the signal to job of mentioned number. 

Error Handling - if required number of arguments are not given then it throws error. If job not exists then throws the error.

It is implemented in syscmd.c file in kjob() function.

##### fg :
    
Syntax - `fg <job_number>`.

Description - Brings the running or stopped background process to foreground in running state. 

Error Handling - if required number of arguments are not given then it throws error. If job not exists then throws the error.

It is implemented in intercmd.c file in fg() function.

##### bg :
    
Syntax - `bg <job_number>`.

Description - Brings the running  background process into stopped status. 

Error Handling - if required number of arguments are not given then it throws error. If job not exists then throws the error.

It is implemented in intercmd.c file in bg() function.

##### overkill :
    
Syntax - `overkill`.

Description - Kills all background process. 

It is implemented in syscmd.c file in overkill() function.

##### quit :
    
Syntax - `quit`.

Description - quits the shell with a message.

It is in main.c inside the loop.

##### Redirection : 
    
On applying redirection symbol(<,>,>>) (with spaces) the code work same as Linux shell.

##### Piping : 
    
On applying piping symbol (|) (with spaces) the code work same as Linux shell.

The code also supports redirection with piping.

##### Ctrl + C :

Exits the current foreground process.

##### Ctrl + D :

quits the shell with a message.

----------------------------------------------------------------------------------------------------------

### Other file : 

input.h - for input.c
header.h for header files and declarations.
history.txt
prompt.c for prompt.
main.c
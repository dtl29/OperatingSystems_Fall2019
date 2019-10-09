Daniel Louis, Andrew Whelch 
Operation Sysytems Fall 2019 (8:45 section)

Lab05

For this lab we set up the shell for the user to interact with the OS  without having to call the interrupt calls directly.
 For this lab we added functionality to three command words and added stub functions to nine other commands that 
will allow the user to use the shell as if it were a linux consol.  The three that have functionality is: 
        The boot command that will restart Black Dos. 
        The clrs command that will clear the screen. 
        The echo command that will echo what was typed back on the screen. 
The stub commands are:
         copy (with two arguemnts), ddir, exec(with one argument), help, prnt(with one arugment), remv(with one arugment),
         senv, show(with one arugment), twet(with one arugment)

To test this run Black Dos using boches and then type in the commands with the coresponding arguements. The 
arguments can be any text and if there needs to be two just seperate them with white space. 
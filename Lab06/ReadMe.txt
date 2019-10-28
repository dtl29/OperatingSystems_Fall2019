Daniel Louis, Andrew Whelch 
Operation Sysytems Fall 2019 (8:45 section)

Lab06

      For this lab we added functionality to the kernel so that a file can be saved and used in memory. We do this through a directory and a map that will 
allow for new files to be loaded into the machine and be either printed to the screen or executed with the shell command exec. This is a file system that
the user can use to save and find files on the disk without needing to know the sector location. 

	We also updated our shell so the user can now interact with the files in the file system on the machine through commands in the shell. The commands we
have added to the shell are ddir (which will show the memory usage for the disk), exec(which will execute a program) help, prnt (which will print the file to 
print.out), senv (which will allow the user to change the color of the screen), and show (which will show the file to the screen). 

	Also we created a user manual that will execute Manual.c that is in memory and will give basic instructions to the user. 
Daniel Louis
Operation Sysytems Fall 2019 (8:45 section)

Lab01

For this lab I modified the preexisting c file inorder for the kernel to be able to display the black dos logo 
and print "Hello world from Dan Louis" to the printer. I also made those calls to print be interrupt calls instead of 
function calls within the c file. So now the kernel has the ability to call interrupt 33 inorder to parrellel print to both the 
screen and the printer port. 

In order to verify this please look at the c file named kernel.c  for the changes within the function printString and the handleInterrupt21 function. 
Also within the printLogo function for the change of printString calls to interrupt calls. 

Daniel Louis, Andrew Whelch 
Operation Sysytems Fall 2019 (8:45 section)

Lab03

In this lab we added functionality to the OS that can read memory off of the disk and store that into a char array that will act as the buffer. We also wrote a writeSector function that will allow things to be written to the disk. Finally we added the function clearScreen that will print blank lines to clear the screen and will change the color of the display if the user wants that too. 

to test these features call interrup33. For the readSector call interrupt(33,2,char array, int for sector number, int for sector count) this will read what is on the disk at the sector and stop when it reaches sector count, this will be stored into the char array. The next one is writeSector and can be called the same way with AX euql to 6 (so interrupt(33,6,...)). The cleanScreen will be called with  interrupt 33 with AX equal to 12 and BX equal to the number of the color form the table, this will be the background color, then the CX should equal another number for the table to be the foreground color.


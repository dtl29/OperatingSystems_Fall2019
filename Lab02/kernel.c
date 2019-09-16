/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:     Daniel Louis        Date:    09/11/2019        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.03, Fall 2019.               */

void handleInterrupt21(int,int,int,int);
void printLogo();
char* readString(char ar[]);
void testReadString();

void main()
{
   char* ar;

   makeInterrupt21();
   printLogo();
   interrupt(33,0,"Hello world from Dan Louis.\r\n\0",1,0);
   testReadString();
   while(1);
}

void printString(char* c, int d)
{
   int count = 0;
   while(*(c +count) != '\0' && d == 0)
   {
      char al = *(c+count);
      char ah = 14;
      int ax = ah * 256 + al;
      interrupt(16,ax,0,0,0);
      count++;
   }
   while(*(c +count) != '\0' && d == 1)
   {
      char al = *(c+count);
      interrupt(23,al,0,0,0);
      count++;
   }
   return;
}

void printLogo()
{

   interrupt(33,0,"       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0,0);
   interrupt(33,0,"      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0,0);
   interrupt(33,0,"     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0,0);
   interrupt(33,0,"    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0,0);
   interrupt(33,0,"   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0,0);
   interrupt(33,0,"._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0,0);
   interrupt(33,0," BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0",0,0);
   interrupt(33,0," Author(s):Dan Louis, (s) .\r\n\r\n\0",0); 
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */

char* readString(char ar[80])
{
	int counter = 0;
	char c;
	while(counter < 79 &&  ar[counter+1] != 0xD)
	{
		ar[counter] = interrupt(22,0,0,0);
		c = (char) ar[counter];
		interrupt(33,0, c,0,0);
		counter = counter + 1;
	}
	ar[counter] = 0x0;
	return ar;
}

void testReadString()
{
	char* ar;
	interrupt(33,0,"Please enter a string to print out. when done press enter",0,0);
	ar = readString(ar);
	interrupt(33,0,ar,1,0);
}

/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
   /*return;*/
   switch(ax) {  
      case 0:  
            printString(bx,cx);
/*      case 1: case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: case 13: case 14: case 15: */
      default: printString("General BlackDOS error.\r\n\0"); 
   }  
}

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
/* Signed:     Daniel Louis        Date:    09/18/2019        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.03, Fall 2019.               */

void handleInterrupt21(int,int,int,int);
void printLogo();
void runProgram(int start, int size, int segment);
void main()
{

	char buffer[512];
	makeInterrupt21();
	interrupt(33,2,buffer,258,1);
	interrupt(33,12,buffer[0]+1,buffer[1]+1,0);
	printLogo();
	runProgram(30,10,2);
	interrupt(33,0,"Bad or missing command interpreter.\r\n\0",0,0);
	while(1);
}

/*
Function printString : called with interrupt(33)
*precondition: will take an argument of a char pointer that will be
**the beginning of the string and an integer that will act as a boolean
**to set the destination of screen if set to 0 or to print if set to 1.
*postcondition: will print the input either to screen or to print depending
**on the input value.
*/
void printString(char* c, int d)
{
   int count = 0;
   char al;
   char ah;
   int ax;

   while(*(c +count) != '\0' && d == 0)
   {
      al = *(c+count);
      ah = 14;
      ax = ah * 256 + al;
      interrupt(16,ax,0,0,0);
      count++;
   }
   while(*(c +count) != '\0' && d == 1)
   {
      al = *(c+count);
      interrupt(23,al,0,0,0);
      count++;
   }
   return;
}

/*
Function printLogo
*precondition: takes no arguments
*postcondition: will print the black dos logo when called.
*/
void printLogo()
{

   interrupt(33,0,"       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0,0);
   interrupt(33,0,"      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0,0);
   interrupt(33,0,"     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0,0);
   interrupt(33,0,"    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0,0);
   interrupt(33,0,"   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0,0);
   interrupt(33,0,"._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0,0);
   interrupt(33,0," BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0",0,0);
   interrupt(33,0," Author(s):Dan Louis, Andrew Whelch \r\n\r\n\0",0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */

/*
Function readString
*Precondition: This function will take a char array of 80 characters
*Postcondition: The function will take input from the keyboard and
**store it into the char array.
*/
void readString(char ar[80])
{
	int counter = 0;

	do
	{
		ar[counter] = interrupt(22,0,0,0,0);
    		 interrupt(16,14 * 256 + ar[counter],0,0,0);
		counter = counter + 1;
		if(ar[counter-1] == 0x8 && counter > 1)
		{
			counter = counter - 2;
		}
	}while(counter < 80 &&  ar[counter -1] != 0xD);
	ar[counter-1] = 0x0;
	interrupt(33,0,"\n\r\0",0,0);
	return;
}

/*
Function readInt
*Precondition: this function takes an integer pointer as an argument
*Postcondition: The function will read in an integer from the keyboard
**and store it into the integer pointer that was passed through.
*/
void readInt(int *n)
{
	char ar[80];
	int i = 0;
 	int len = 0 ;
	int isNegative = 0;
	int num = 0;

	interrupt(33,1,ar,0,0);
	while(ar[len] != 0x0)
	{
		len += 1;
	}
	if(ar[0] == '-')
	{
		isNegative = 1;
		i = 1;
	}
	while(i < len)
	{
		num *= 10;
		num += (ar[i++] - '0');
	}
	if(isNegative == 1)
	{
		num *= -1;
	}
	*n = num;
	return;
}

/*
Function writeInt
*Precondition: this function takes two arguments, first will be an
**integer that will be the number displayed on screen and the second
**will be the destination of where to print(0 for screen, 1 for printer)
*Postcondition: this function will write the passed through integer to
**the screen if the second integer was 0 or to printer if the second
**integer was a 1
*/
void writeInt(int n, int d)
{
	char ar[80];
	int i = 0;
	int temp;
	int counter = 0;
	int bool  = 0;
	int placeDiv = 10000;

	if(n < 0)
	{
		i += 1;
		ar[0] = '-';
		n *= -1;
	}
	while (counter < 5)
	{
		temp = div(n,placeDiv);
		if(bool == 1)
		{
			ar[i++] = temp + '0';
			n -= temp * placeDiv;
		}
		if(temp != 0 && bool == 0)
		{
			ar[i++] = temp + '0';
			n -= temp * placeDiv;
			bool = 1;
		}
		placeDiv = div(placeDiv,10);
		counter++;
	}
	ar[i] = 0x0;
	if(d == 0)
	{
		interrupt(33,0,ar,0,0);
	}
	else if(d == 1)
	{
		interrupt(33,0,ar,1,0);
	}
}

/*
Function mod
*Precondition: this function takes two integers as arguments
*Postcondition: This function will find the remainder between the
**two integers divided together.
*/
int mod(int a, int b)
{
	int x = a;
	while (x >= b)
		x = x -b;
	return x;
}

/*
Function div
*Precondition: this function takes two integers as arguments
*Postcondition: this function will find the quotient of the two
**integers divided together.
*/
int div(int a, int b)
{
	int q = 0;
	while(q * b <= a)
		 q++;
	return (q-1);
}


/*lab3 VVVV*/

/*
Function readSectors
*precondition: will take 3 arguments 
**first will be the pointer of a char array that will hold the returned file
**second will be the sector at which should be read
**third will be the amount of sectors that should be read
*postcondition: will place the characters from the specified sectors 
*/
void readSectors(char *buffer, int sector, int sectorCount)
{
	int al;
	int ah;
	int ch;
	int cl;
	int dh;
	int dl;
	int ax;
	int cx;
	int dx;
	char *bx = buffer;

	ah = 2;
	al = sectorCount;
	ch = div(sector, 36);
	cl = mod(sector, 18) + 1;
	dh = mod(div(sector, 18), 2);
	dl = 0;
	ax = ah * 256 + al;
	cx = ch * 256 + cl;
	dx = dh * 256 + dl;

	interrupt(19, ax, buffer, cx, dx);
	return;
}

/*
Function writeSectors
*precondition: will take 3 arguments.
**first will be the character strings as a pointer that should be written.
**second will be the sector it should be placed into.
**third will be how many sectors the string will take to write too.
*postcondition: will write the string to the disk at the specified sector.
*/
void writeSectors(char *buffer, int sector, int sectorCount)
{
	int al;
	int ah;
	int ch;
	int cl;
	int dh;
	int dl;
	int ax;
	int cx;
	int dx;
	char *bx = buffer;

	ah = 2;
	al = sectorCount;
	ch = div(sector, 36);
	cl = mod(sector, 18) + 1;
	dh = mod(div(sector, 18), 2);
	dl = 0;
	ax = ah * 384 + al;
	cx = ch * 256 + cl;
	dx = dh * 256 + dl;

	interrupt(19, ax, buffer, cx, dx);
	return;
}

/*
Function clearScreen
*precondition: this takes two integer arguments, the first will be the background color from the standard 16-bit text
**palette and should be between 1 and 7. the next integer is the foreground color form the same table and should be
**between 1-15
*postcondition: this will clear the screen and set the foreground and background colors
*/
void clearScreen(int bx, int cx)
{
	int i = 0;
	while(i < 25)
	{
		interrupt(16,14*256+'\r',0,0,0);
		interrupt(16,14*256+'\n',0,0,0);
		i++;
	}
	interrupt(16,512,0,0,0);
	if((bx > 0) && (cx > 0) && (bx <= 8) && (cx <= 16))
	{
		interrupt(16,1536,4096 * (bx - 1) + 256 * (cx - 1), 0, 6223);
	}
	return;
}

/*
Function runProgram
*precondition: takes two arguments
**first pointer to a character string of the name of the program to run
**second is the segment which is the starting location to the program table
*postcondition: this will run the program at the sector specified when called.
**will run it from the shell
*/
void runProgram(int start, int size, int segment)
{
	char buffer[13312];
	int i = 0;
	int baseLocation = 0;

	interrupt(33,2,buffer,start,size);
	baseLocation = segment * 4096;

	while(i < 13312)
	{
		putInMemory(baseLocation, i, buffer[i]);
		i += 1;
	}
	launchProgram(baseLocation);
}

/*
Function stop
*precondition: takes no arguments and will restart the shell.
*postcondition: will run an infinite loop.
*/
void stop()
{
	while(1);
}


/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

/*
Function handleInterrupt21
*precondition: this takes 4 arguments, one that will select what function to call and the others to
**send necessary inputs to the functions
*postcondition: from selected this handler will call the proper function from the kernel
*/
void handleInterrupt21(int ax, int bx, int cx, int dx)
{
   /*return;*/
   switch(ax) {
    case 0:
    {
      printString(bx,cx);
      break;
    }
    case 1:
    {
	    readString(bx);
	    break;
	  }
	  case 2:
	  {
			readSectors(bx, cx, dx);
			break;
	  }

/*case 3: case 4: */
		case 5:
		{
			stop();
			break;
		}
	  case 6:
	  {
	  	writeSectors(bx, cx, dx);
	  	break;
	  }
/*case 7: case 8: case 9: case 10: case 11: */
	  case 12:
	  {
	  	clearScreen(bx, cx);
	  	break;
	  }
    case 13:
    {
      writeInt(bx,cx);
      break;
    }
    case 14:
    {
      readInt(bx);
      break;
    }
/*case 15: */
    default: printString("General BlackDOS error.\r\n\0");
   }
}

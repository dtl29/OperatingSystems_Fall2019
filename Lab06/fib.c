#include "blackdos.h"

void main()
{
   int i, a = 1, b = 1, c, n;
   char buffer[512];
   PRINTS("How many terms? \0");
   SCANN(n);
   if (n < 3) n = 3;
   PRINTN(n);
   PRINTS(" terms: \0");
   PRINTN(a);
   PRINTS(" \0");
   PRINTN(b);
   PRINTS(" \0");
   for (i = 0; i < n - 2; i++)
   {
      c = a + b;
      PRINTN(c);
      PRINTS(" \0");
      a = b;
      b = c;
   }
   PRINTS("\r\n\0");

   interrupt(33,0,"\r\n\0",0,0);
   interrupt(33,0,"\r\n\0",0,0);
   interrupt(33,0,"      Press [ENTER] to continue.\r\n\0",0,0);
   interrupt(33,1,buffer,0,0);
   END;
}

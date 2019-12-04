/* Disk diectory program */
/* Original c. 2019 D. Damiano, revised 7.16.2019 O'Neil */

#include "blackdos.h"

int is_capital(char*);

void main()
{
   char directory[512], filename[512];
   int sectors = 0, sectors_used = 0, i = 0, j = 0, index = 0, num_of_files = 0, noChars;

   interrupt(33,2,directory,257,1);

   PRINTS("\r\n     ----------------------\r\n\r\n\0");
   PRINTS("     FILE DIRECTORY:\r\n\r\n\0");

   while(index < 32)
   {
      if(directory[i] != 0x0 && index >= 0)
      {
         noChars = 0;
         for (j = 0; j < 8; j++)
         {
            if (directory[i + j] != 0x0) noChars++;
            filename[j] = directory[i + j];
         }

         sectors = directory[i + 9];
         sectors_used += sectors;

         if(is_capital(filename[0]))
         {
         }
         else
         {
            PRINTS("     \0");
            PRINTS(filename);
            for (j = 0; j < 8 - noChars; j++) PRINTS(" \0");
            if (sectors < 10) PRINTS(" \0");
            PRINTN(sectors);
            PRINTS(" sector(s)\r\n\0");
            num_of_files++;
         }
      }
      sectors = 0;
      i += 16;
      index++;
   }

   PRINTS("\r\n     USED STORAGE (sectors): \0");
   PRINTN(sectors_used);
   PRINTS("\r\n     FREE SPACE (sectors)  : \0");
   PRINTN(255 - sectors_used);
   PRINTS("\r\n     (You can create \0");
   PRINTN(32 - num_of_files);
   PRINTS(" more files..): \0");


   PRINTS("\r\n\r\n\0");
   PRINTS("     ----------------------\r\n\r\n\0");
   interrupt(33,0,"\r\n\0",0,0);
   interrupt(33,0,"\r\n\0",0,0);
   interrupt(33,0,"      Press [ENTER] to continue.\r\n\0",0,0);
   interrupt(33,1,filename,0,0);
   END;
}

int is_capital(char* c)
{
   if(c >= 'A' && c <= 'Z')
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

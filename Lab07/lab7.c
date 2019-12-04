void main()
{
   char buffer[12288]; int size;

   /* Step 1 - load/edit/print file */
   interrupt(33,3,"fpc02\0",buffer,&size);
   buffer[5] = '2'; buffer[6] = '0';
   buffer[7] = '1'; buffer[8] = '9';
   interrupt(33,0,buffer,0,0);
   interrupt(33,0,"\r\n\0",0,0);

   /* Step 2 - write revised file */
   interrupt(33,8,"fall19\0",buffer,size);

   /* Step 3 - delete original file */
   interrupt(33,7,"fpc02\0",0,0);

   /* Step 4 - terminate program and resume shell */
   interrupt(33,5,0,0,0);
}

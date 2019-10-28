void main()
{
  char buffer[512];

  interrupt(33,0,"The Manual: \r\n\0",0,0);
  interrupt(33,0,"\r\n\0",0,0);
  interrupt(33,0,"  DESCRIPTION\r\n\0",0,0);
  interrupt(33,0,"    This is the shell and will interpret commands.\r\n\0",0,0);
  interrupt(33,0,"  COMMANDS\r\n\0",0,0);
  interrupt(33,0,"    copy\r\n\0",0,0);
  interrupt(33,0,"          Takes two arguments and will copy one to the other.\r\n\0",0,0);
  interrupt(33,0,"    ddir\r\n\0",0,0);
  interrupt(33,0,"          Will display the files in the system.\r\n\0",0,0);
  interrupt(33,0,"\r\n\0",0,0);
  interrupt(33,0,"\r\n\0",0,0);
  interrupt(33,0,"      Press [ENTER] to continue.\r\n\0",0,0);
  interrupt(33,1,buffer,0,0);
  interrupt(33,0,"    exec\r\n\0",0,0);
  interrupt(33,0,"        Will execute a program from memory. It takes one arugment.\r\n\0",0,0);
  interrupt(33,0,"    help\r\n\0",0,0);
  interrupt(33,0,"        Will open the user Manual.\r\n\0",0,0);
  interrupt(33,0,"    prnt\r\n\0",0,0);
  interrupt(33,0,"         Will print a file to the printer.It takes one argument\r\n\0",0,0);
  interrupt(33,0,"    remv\r\n\0",0,0);
  interrupt(33,0,"          Will remove a file from memory. It takes one arguement\r\n\0",0,0);
  interrupt(33,0,"\r\n\0",0,0);
  interrupt(33,0,"\r\n\0",0,0);
  interrupt(33,0,"      Press [ENTER] to continue.\r\n\0",0,0);
  interrupt(33,1,buffer,0,0);
  interrupt(33,0,"    senv\r\n\0",0,0);
  interrupt(33,0,"        Will change the color of the screen.\r\n\0",0,0);
  interrupt(33,0,"    show\r\n\0",0,0);
  interrupt(33,0,"        Will show the containts of a file. It takes one argument.\r\n\0",0,0);
  interrupt(33,0,"    twet\r\n\0",0,0);
  interrupt(33,0,"\r\n\0",0,0);
  interrupt(33,0,"\r\n\0",0,0);
  interrupt(33,0,"      Press [ENTER] to continue.\r\n\0",0,0);
  interrupt(33,1,buffer,0,0);
  END;
}

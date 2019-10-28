void inputValidation(char ar[512] , int *boolFail);

void main()
{
  char buffer[512];
  int i = 0;
  int *boolFail;

  interrupt(33,2,buffer,258,1);
  interrupt(33,12,buffer[0]+1,buffer[1]+1,0);
  interrupt(33,0,"Welcome\r\0",0,0);
  while(1)
  {
    for(i; i < 512; i++)
    {
      buffer[i] = 0;
    }
    i = 0;
    interrupt(33,0,"\n\r^(~(oo)~)^\0",0,0);
    interrupt(33,1,buffer,0,0);
    *boolFail = 0;
    inputValidation(buffer, boolFail);
    if(*boolFail == 1)
    {
      *boolFail = 0;
      interrupt(33,0,"\n\rImproper command.\0",0,0);
    }
  }
}

void inputValidation(char ar[512], int *boolFail)
{
  char arg1[507];
  char arg2[507];
  char buffer[13312];
  int i = 0;
  int j = 5;

  if(ar[4] != ' ' && ar[4] != '\0')
  {
    interrupt(33,0,"\nnot a command.\r\0",0,0);
    return;
  }
  while(ar[j] != ' ' && ar[j] != '\0')
  {
    arg1[i] = ar[j];
    i++;
    j++;
  }
  arg1[i] = '\0';
  i = 0;
  j++;
  while(ar[j] != ' ' && ar[j] != '\0')
  {
    arg2[i] = ar[j];
    i++;
    j++;
  }
  arg2[i] = '\0';

  if(ar[0] == 'b' && ar[1] == 'o' && ar[2] == 'o' && ar[3] == 't')
  {
    interrupt(25,0,0,0,0);
    return;
  }
  else if(ar[0] == 'c' && ar[1] == 'l' && ar[2] == 'r' && ar[3] == 's')
  {
    interrupt(33,12,0,0,0);
    return;
  }
  else if(ar[0] == 'e' && ar[1] == 'c' && ar[2] == 'h' && ar[3] == 'o')
  {
    interrupt(33,0,"\n\r\0",0,0);
    interrupt(33,0,&ar[5],0,0);
    return;
  }
  else if(ar[0] == 'c' && ar[1] == 'o' && ar[2] == 'p' && ar[3] == 'y')
  {
    if(arg1[0] == '\0' || arg2[0] == '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\rcopy was read with the argument \0",0,0);
    interrupt(33,0,arg1,0,0);
    interrupt(33,0," \0",0,0);
    interrupt(33,0,arg2,0,0);
    return;
  }
  else if(ar[0] == 'd' && ar[1] == 'd' && ar[2] == 'i' && ar[3] == 'r')
  {
    if(ar[5] != '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\r\0",0,0);
    interrupt(33,4,"Ddir\0",4,0);
    return;
  }
  else if(ar[0] == 'e' && ar[1] == 'x' && ar[2] == 'e' && ar[3] == 'c')
  {
    if(arg1[0] == '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\r\0",0,0);
    interrupt(33,4,arg1,4,0);
    return;
  }
  else if(ar[0] == 'h' && ar[1] == 'e' && ar[2] == 'l' && ar[3] == 'p')
  {
    if(ar[5] != '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\r\0",0,0);
    interrupt(33,4,"Manual\0",4,0);
    return;
  }
  else if(ar[0] == 'p' && ar[1] == 'r' && ar[2] == 'n' && ar[3] == 't')
  {
    if(arg1[0] == '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\r\0",0,0);
    interrupt(33,3,arg1,buffer,1);
    interrupt(33,0,buffer,1,0);
    return;
  }
  else if(ar[0] == 'r' && ar[1] == 'e' && ar[2] == 'm' && ar[3] == 'v')
  {
    if(arg1[0] == '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\rremv was read with the argument \0",0,0);
    interrupt(33,0,arg1,0,0);
    return;
  }
  else if(ar[0] == 's' && ar[1] == 'e' && ar[2] == 'n' && ar[3] == 'v')
  {
    if(ar[5] != '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\r\0",0,0);
    interrupt(33,4,"Stenv\0",4,0);
    return;
  }
  else if(ar[0] == 's' && ar[1] == 'h' && ar[2] == 'o' && ar[3] == 'w')
  {
    if(arg1[0] == '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\r\0",0,0);
    interrupt(33,3,arg1,buffer,1);
    interrupt(33,0,buffer,0,0);
    return;
  }
  else if(ar[0] == 't' && ar[1] == 'w' && ar[2] == 'e' && ar[3] == 't')
  {
    if(arg1[0] == '\0')
    {
      *boolFail = 1;
      return;
    }
    interrupt(33,0,"\n\rtwet was read with the argument \0",0,0);
    interrupt(33,0,arg1,0,0);
    return;
  }
  else
  {
    interrupt(33,0,"\n\rnot a command.\r\0",0,0);
    return;
  }
}

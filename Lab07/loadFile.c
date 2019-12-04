//loadFile.c
//Michael Black, 2007
//Revised 7.12.2019 O'Neil
//
//Loads a file into the file system
//This should be compiled with gcc and run outside of the OS

#include <stdio.h>

int main(int argc, char* argv[])
{
	int i, j, size, noSecs, startPos;

	if (argc<2)
	{
		printf("Specify file name to load\n");
		return 0;
	}

	//open the source file
	FILE* loadFil;
	loadFil=fopen(argv[1],"r");
	if (loadFil==0)
	{
		printf("File not found\n");
		return 0;
	}

        // get file size in bytes
        fseek(loadFil, 0, SEEK_END);
        size = ftell(loadFil);
        if (fseek(loadFil, 0, SEEK_SET) != 0) {
                printf("Repositioning error\n");
        }
        else {
                printf("File found ... %d bytes or ", size);
                noSecs = size / 512; if (size % 512 != 0) noSecs++;
                printf("%d sector(s)\n", noSecs);
		if (noSecs>23)
		{
			printf("Not enough space in directory entry for file\n");
			return 0;
		}

        }

	//open the floppy image
	FILE* floppy;
	floppy=fopen("floppya.img","r+");
	if (floppy==0)
	{
		printf("floppya.img not found\n");
		return 0;
	}

	//load the disk map
	char map[512];
	fseek(floppy,512*256,SEEK_SET);
	for(i=0; i<512; i++)
		map[i]=fgetc(floppy);

	//load the directory
	char dir[512];
	fseek(floppy,512*257,SEEK_SET);
	for (i=0; i<512; i++)
		dir[i]=fgetc(floppy);

	//find a free entry in the directory
	for (i=0; i<512; i=i+0x10)
		if (dir[i]==0)
			break;
	if (i==512)
	{
		printf("Not enough room in directory\n");
		return 0;
	}
	int dirindex=i;

	//fill the name field with 00s first
	for (i=0; i<8; i++)
		dir[dirindex+i]=0x00;
	//copy the name over
	for (i=0; i<8; i++)
	{
		if(argv[1][i]==0)
			break;
		dir[dirindex+i]=argv[1][i];
	}

	dirindex=dirindex+8;

        //find enough free consecutive sectors to store file
        int flag;
        for (i=0; i<256 - noSecs; i++) {
                flag = 0;
                for (j=0; j<noSecs;j++)
                        if (map[i+j] != 0) flag = 1;
                if (flag == 0) break;
        }
        startPos = i;
	if (flag==1)
		{
			printf("Not enough room for file\n");
			return 0;
		}       
        else printf("Found %d free sectors starting at %d\n", noSecs, startPos);
        dir[dirindex]=startPos;
        dir[dirindex+1]=noSecs;

	//find free sectors and add them to the file
	for (j = startPos; j < startPos + noSecs; j++)
	{

		//mark the map entry as taken
		map[j]=0xFF;

		//mark the sector in the directory entry
		//dir[dirindex]=j;
		//dirindex++;
                printf("Writing sector at position %d\n", j);

		//move to the sector and write to it
		fseek(floppy,j*512,SEEK_SET);
		for (i=0; i<512; i++)
		{
			if (feof(loadFil))
			{
				fputc(0x0, floppy);
				break;
			}
			else
			{
				char c = fgetc(loadFil);
				fputc(c, floppy);
			}	
		}
	}

	//write the map and directory back to the floppy image
        printf("Writing updated disk map and directory ... ");
        fseek(floppy,512*256,SEEK_SET);
        for(i=0; i<512; i++)
		fputc(map[i],floppy);
        
        fseek(floppy,512*257,SEEK_SET);
        for (i=0; i<512; i++)
		fputc(dir[i],floppy);

	fclose(floppy);
	fclose(loadFil);
        printf("done.\n");
}

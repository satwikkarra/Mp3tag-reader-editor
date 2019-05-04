#include "reader.h"
#include <string.h>
#include "types.h"

int get_version(ReaderInfo *readInfo)
{
	char buff[3] = {0};
	fread(buff,1,3, readInfo->fptr_src_mp3);
	if (strcmp(buff,"ID3") == 0)
	{
		printf ("ID3 version 2\n");
		return 2;
	}
	else if (strcmp(buff,"TAG") == 0)
	{
		printf ("ID3 version 1\n");
		return 1;
	}
	else
	{
		printf ("Unsupported version\n");
	}
	
	return 0;
}

Status version2_info(ReaderInfo *readInfo)
{
	char buff = 0;
	fread(&buff,1,1,readInfo->fptr_src_mp3);
	if(buff == 0x03)
	{
		buff = 0;
		fread(&buff,1,1,readInfo->fptr_src_mp3);
		if (buff == 0x00)
		{
			printf ("version 2.3.0\n");
			return e_success;
		}
		else if (buff == 0x01)
		{
			printf ("version 2.3.1\n");
			return e_success;
		}
		else
		{
			printf ("version 2.3.2\n");
			return e_success;
		}
	}

	return e_failure;
}

uint get_size_of_tag(ReaderInfo *readInfo)
{
	uint buff = 0, res = 0;
	rewind(readInfo->fptr_src_mp3);
	fseek(readInfo->fptr_src_mp3,6,SEEK_SET);
	fread(&buff,1,4,readInfo->fptr_src_mp3);
    res = reverse_bits(&buff);
	return res;
    
}

uint reverse_bits(void *var)
{
	uint res = 0;
	int i;
	unsigned char buff[4] = {0};
	void *ptr = buff;
	uint size = sizeof(int);
	for (i = size-1; i >= 0; i--)
	{
		buff[i] = *(unsigned char *)var;
		var = (unsigned char *)var + 1;
	}
	
    res = *(unsigned int *)ptr;
	return res;
}
Status get_frame_id(char *str, ReaderInfo *readInfo, char *str1)
{
	char buff[4] = {0};
	uint size = 0;
	int flag = 1;
	FILE *fptr = readInfo->fptr_src_mp3;
	FILE *fptr1 = readInfo->fptr_src_mp3;
	while (ftell(readInfo->fptr_src_mp3) <  (readInfo->size_of_tag + 10))		
	{
		fread(buff,1,4,readInfo->fptr_src_mp3);
	//	printf ("buf : %s\n", buff);
		fread(&size,1,4,readInfo->fptr_src_mp3);
		size = reverse_bits(&size);
		//printf ("size of buff: %d\n", size);
		char buff1 = 0;
		if (strcmp(buff,str) == 0)
		{
			//printf("Title: %s\n", buff);
		    //printf ("size: %d\n", size);  
		    flag = 0;
		    fseek(readInfo->fptr_src_mp3,2,SEEK_CUR);
		    printf ("%s:  ", str1);
		    while (size--)
			{
				fread(&buff1,1,1,readInfo->fptr_src_mp3);
		    	if (buff1 >= 32 && buff1 <= 126)
			 	{
					printf ("%c", buff1);
			 	}
			 }
			 putchar('\n');
		     break;
		}
		fseek(readInfo->fptr_src_mp3,size + 2,SEEK_CUR);
		//printf ("flag inside :%d\n", flag);
	}
	memset(buff,0,5);
	rewind(readInfo->fptr_src_mp3);
	fseek(readInfo->fptr_src_mp3,10,SEEK_SET);
	if(flag)
	{
		return e_failure;
	}
	return e_success;
}

Status write_frame_id(char *str, ReaderInfo *readInfo, char *str1)
{
	char buff[4] = {0};
	uint size = 0;
	int i=0;
	int flag = 1;
	int length=strlen(str1);
	printf("length : %d",length);
	char b = '\0';
	FILE *fptr = readInfo->fptr_src_mp3;
	FILE *fptr1 = readInfo->fptr_src_mp3;
	while (ftell(readInfo->fptr_src_mp3) <  (readInfo->size_of_tag + 10))		
	{
		fread(buff,1,4,readInfo->fptr_src_mp3);
	//	printf ("buf : %s\n", buff);
		fread(&size,1,4,readInfo->fptr_src_mp3);
		size = reverse_bits(&size);
		printf("size: %d\n", size);
		//printf ("size of buff: %d\n", size);
		char buff1 = 0;
		if (strcmp(buff,str) == 0)
		{
			//printf("Title: %s\n", buff);
		    //printf ("size: %d\n", size);  
		    flag = 0;   
		    fseek(readInfo->fptr_src_mp3,3,SEEK_CUR);
		 //   printf ("%s:  ", str1);
		    while (--size)
			{
				//fread(&buff1,1,1,readInfo->fptr_src_mp3);

		    //	if (buff1 >= 32 && buff1 <= 126)
			 //	{
                   
                    if(length!=0)
					{
					fwrite(str1+(i++),1,1,readInfo->fptr_src_mp3);
					length--;
					}
					else
					{
						fwrite(&b,1,1,readInfo->fptr_src_mp3);
					}
			 //	}
                
                
			 }
			 putchar('\n');
		     break;
		}
		fseek(readInfo->fptr_src_mp3,size + 2,SEEK_CUR);
		//printf ("flag inside :%d\n", flag);
	}
	memset(buff,0,5);
	rewind(readInfo->fptr_src_mp3);
	fseek(readInfo->fptr_src_mp3,10,SEEK_SET);
	if(flag)
	{
		return e_failure;
	}
	return e_success;
}

/*
 For viewing : ./a.out -v sample.mp3
 For editing : ./a.out -e sample.mp3 (whatever u want to change)
 TAG - version 1
 ID3 - version 2
	 - 3(version) + 2(sub-version) + 1(flags) + 4(size of tag content) + tag content
	 - 4(frame_id) + 4(size of frame content) + 2(flags) + frame content
*/

#include <stdio.h>
#include <stdlib.h>
#include "open_files.c"
#include "reader.h"
#include "reader.c"
#include "types.h"


int main(int argc, char *argv[])
{
	//assigning source file name
	readInfo.src_mp3_fname = argv[2];

	int options;
	//opening files for viewing/editing
	if (open_files(&readInfo) == e_success)
	{
		printf ("Files opened\n");
	}
	else
	{
		printf ("Files not opened\n");
		return -1;
	}
	
	//calling get_version function
	int n = get_version(&readInfo);

	switch (n)
	{
		case 1:
			break;
		case 2:
			//calling version2_info function for subversion
			if (version2_info(&readInfo) == e_failure)
			{
				printf ("version not valid\n");
			}
			else
			{
				printf ("-----Version-----\n");
			}
			break;

	}
	//calling size_of_tag function for size of tag(ID3)
	readInfo.size_of_tag = get_size_of_tag(&readInfo);
	if(strcmp(argv[1], "-v") == 0)
	{
		//checking for absence of frame_ids
		if(get_frame_id("TRCK", &readInfo, "TRACK") == e_failure)
		{
			printf ("No track===\n");
		}
		if (get_frame_id("TYER", &readInfo, "YEAR") == e_failure)
		{
			printf ("No Year\n");
		}
		if (get_frame_id("TPE1", &readInfo, "ARTIST") == e_failure)
		{
			printf ("No Artist\n");
		}
		if (get_frame_id("TIT2", &readInfo, "TITLE") == e_failure)
		{
			printf ("No Title\n");
		}
		if (get_frame_id("TALB", &readInfo, "ALBUM") == e_failure)
		{
			printf ("No Album\n");
		}
		if (get_frame_id("COMM", &readInfo, "COMMENT") == e_failure)
		{
			printf ("No Comment\n");
		}
		if (get_frame_id("TCON", &readInfo,"GENRE") == e_failure)
		{
			printf ("No Genre\n");
		}
	}
	//checking for editing 
	else if(strcmp(argv[1], "-e") == 0)
	{
		printf("1.album\n2.artist\n3.Title\n4.year\n5.track\n6.comment\n7.genre\nEnter an option: ");
		scanf("%d", &options);

		switch(options)
		{
			case 1:
				//editing TALB frame content
				if (write_frame_id("TALB", &readInfo,argv[3]) == e_failure)
				{
					printf ("not written\n");
				}
				break;
			case 2:
				//editing TPE1 frame content
				if (write_frame_id("TPE1", &readInfo, argv[3]) == e_failure)
				{
					printf ("not written\n");
				}
				break;

			case 3:
				//editing TIT2 frame content
				if (write_frame_id("TIT2", &readInfo,argv[3]) == e_failure)
				{
					printf ("not written\n");
				}
				break;
			case 4:
				//editing TYER frame content
				if (write_frame_id("TYER", &readInfo, argv[3]) == e_failure)
				{
					printf ("not written\n");
				}
				break;
			case 5:
				//editing TRCK frame content
				if (write_frame_id("TRCK", &readInfo, argv[3]) == e_failure)
				{
					printf ("not written\n");
				}
				break;
			case 6:
				//editing COMM frame content
				if (write_frame_id("COMM", &readInfo,argv[3]) == e_failure)
				{
					printf ("not written\n");
				}
				break;
			default:
			    //editing TCON frame content
				if (write_frame_id("TCON", &readInfo,argv[3]) == e_failure)
				{
					printf ("not written\n");
				}		
		}
	}
}


#ifndef READER_H
#define READER_H

#include "types.h" // Contains user defined types

/* Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _READERINFO
{
    /* Source Image info */
    char *src_mp3_fname;
    FILE *fptr_src_mp3;
    char mp3_data[MAX_IMAGE_BUF_SIZE];
    uint size_of_tag;


} ReaderInfo;

ReaderInfo readInfo;

/* Encoding function prototype */
Status open_files(ReaderInfo *readInfo);

int get_version(ReaderInfo *readInfo);

Status version2_info(ReaderInfo *readInfo);

uint get_size_of_tag(ReaderInfo *readInfo);

Status get_frame_id(char *str,ReaderInfo *readInfo, char *str1);

uint reverse_bits(void *var);
#endif

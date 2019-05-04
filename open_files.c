#include "types.h"
#include "reader.h"
/* Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(ReaderInfo *readInfo)
{
    // Src Image file
    readInfo->fptr_src_mp3 = fopen(readInfo->src_mp3_fname, "rb+");
    //Do Error handling
    if (readInfo->fptr_src_mp3 == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", readInfo->src_mp3_fname);
    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

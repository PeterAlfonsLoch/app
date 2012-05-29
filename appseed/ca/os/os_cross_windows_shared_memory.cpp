#include "framework.h"


//#include <stdio.h>
//#include <stdlib.h>
#include <sys/types.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/mman.h>


HGLOBAL WINAPI GlobalAlloc(UINT uFlags, SIZE_T dwBytes)
{

   int result;


   HGLOBAL hglobal = new class hglobal();

   strcpy(hglobal->m_szFile, "/ca2/time/global_alloc/XXXXXX.mmap");

   hglobal->m_fd = mkostemps(hglobal->m_szFile, 5, O_RDWR | O_CREAT | O_TRUNC);

   /* Open a file for writing.
    *  - Creating the file if it doesn't exist.
    *  - Truncating it to 0 size if it already exists. (not really needed)
    *
    * Note: "O_WRONLY" mode is not sufficient when mmaping.
    */
//    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
   if(hglobal->m_fd == -1)
   {
      //perror("Error opening file for writing");
      //exit(EXIT_FAILURE);
      delete hglobal;
      return NULL;
   }

   /* Stretch the file size to the size of the (mmapped) array of ints
    */
   result = ftruncate(hglobal->m_fd, dwBytes);
   if(result == -1)
   {
      close(hglobal->m_fd);
      //perror("Error calling lseek() to 'stretch' the file");
      //exit(EXIT_FAILURE);
      delete hglobal;
      return NULL;
   }

    /* Something needs to be written at the end of the file to
     * have the file actually have the new size.
     * Just writing an empty string at the current file position will do.
     *
     * Note:
     *  - The current position in the file is at the end of the stretched
     *    file due to the call to lseek().
     *  - An empty string is actually a single '\0' character, so a zero-byte
     *    will be written at the last byte of the file.
     */
   /*result = write(hglobal->m_fd, "", 1);
   if(result != 1)
   {
      close(hglobal->m_fd);
  //    perror("Error writing last byte of the file");
    //  exit(EXIT_FAILURE);
      delete hglobal;
      return NULL;
   } */

   hglobal->m_map = NULL;

   return hglobal;

}


HGLOBAL WINAPI GlobalReAlloc(HGLOBAL hglobal, SIZE_T dwBytes, UINT uFlags)
{

   int result = ftruncate(hglobal->m_fd, dwBytes);
   if(result == -1)
   {
      close(hglobal->m_fd);
      //perror("Error calling lseek() to 'stretch' the file");
      //exit(EXIT_FAILURE);
      delete hglobal;
      return NULL;
   }

   return hglobal;

}


HGLOBAL WINAPI GlobalFree(HGLOBAL hglobal)
{

   fclose(hglobal->m_fd);
   unlink(hglobal->m_szFile);
   delete hglobal;

   return NULL;

}


LPVOID WINAPI GlobalLock(HGLOBAL hglobal)
{

   if(hglobal->m_map != NULL)
      return hglobal->m_map;

   /* Now the file is ready to be mmapped.
     */
   hglobal->m_map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if(hglobal->m_map == MAP_FAILED)
   {

      //perror("Error mmapping the file");
      //exit(EXIT_FAILURE);
      return NULL;
   }

   return hglobal->m_map;

}


SIZE_T WINAPI GlobalSize(HGLOBAL hglobal)
{

   struct stat st;

   fstat(hglobal->m_fd, &st);

   return st.st_size;

}


BOOL WINAPI GlobalUnlock(HGLOBAL hglobal)
{

   if(hblobal->m_map == NULL)
      return FALSE;

   if (munmap(hglobal->m_map, FILESIZE) == -1)
   {
      //perror("Error un-mmapping the file");
	/* Decide here whether to close(fd) and exit() or not. Depends... */
      return FALSE;
   }

   return TRUE;

}




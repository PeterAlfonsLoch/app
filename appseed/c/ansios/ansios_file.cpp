#include "framework.h"
#include <sys/stat.h>


void fd_ensure_file_size(int fd, int64_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      throw "fd_ensure_file_size exception";

}


int64_t fd_get_file_size(int fd)
{

   struct stat st;

   if(fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}


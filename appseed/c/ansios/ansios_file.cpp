#include "framework.h"
#include <sys/stat.h>


void ensure_file_size(int fd, size_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      throw "fd_ensure_file_size exception";

}


size_t get_file_size(int fd)
{

   struct stat st;

   if(fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}


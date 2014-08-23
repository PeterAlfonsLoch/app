#include "framework.h"


// gone to ansios_file.cpp/.h
/*

#include <sys/stat.h>


void fd_ensure_file_size(int32_t fd, int64_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      throw "fd_ensure_file_size exception";

}


int64_t fd_get_file_size(int32_t fd)
{

   struct stat st;

   if(fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}

*/


/*

CLASS_DECL_AURA void dll_processes(simple_uint_array & dwa, stra_dup & straProcesses, const char * pszDll)
{



}
*/


string get_sys_temp_path()
{

   return ::dir::path(getenv("HOME"), ".ca2", "time");

}

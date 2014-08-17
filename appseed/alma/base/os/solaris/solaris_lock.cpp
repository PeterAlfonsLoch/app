#include "ca/ca.h"


#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>


int32_t _c_lock_is_active(const char * pszName)
{

   int32_t * pfd;

   if(_c_lock(pszName, (void **) &pfd))
   {
      _c_unlock((void **) &pfd);
      return false;
   }

   return true;

}


int32_t _c_lock(const char * pszName, void ** pdata)
{

   int32_t fd;

   _ca_get_file_name(dir::path("/var/lib/ca2/", pszName), true, &fd);

   if(fd == -1)
      return 0;


   if(flock(fd, LOCK_EX | LOCK_NB) == -1)
   {
      if(errno == EWOULDBLOCK)
      {
         close(fd);
         errno = EWOULDBLOCK;
         return 0;
      }
      else
      {
         close(fd);
         return 0;
      }
   }

   int32_t * pi = new int32_t;
   *pi = fd;
   *pdata = pi;

   return 1;

}


int32_t _c_unlock(void ** pdata)
{

   int32_t * pfd = (int32_t *) *pdata;

   if(flock(*pfd, LOCK_EX | LOCK_NB | LOCK_UN) == -1)
   {
   }

   close(*pfd);


   *pfd = 0;

   delete pfd;

   *pdata = NULL;

   return 1;

}



vsstring _ca_get_file_name(const char * pszName, bool bCreate, int32_t * pfd)
{

   vsstring str(pszName);

   str.replace("\\", "/");
   str.replace("::", "_");

   dir::mk(dir::name(str));

   if(bCreate)
   {
      int32_t fd = open(str, O_CREAT | O_RDWR);
      if(fd == -1)
         return "";
      if(pfd != NULL)
      {
         *pfd = fd;
      }
   }

   return str;
}

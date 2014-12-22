#include "aura/aura/aura.h"


#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void local_memory_map::construct()
{
   
   m_strName.Empty();
   m_iFile = -1;
   m_pdata = (void *) MAP_FAILED;
   m_bRead = false;
   m_bWrite = false;
   m_bCreate = false;

}


bool local_memory_map::is_mapped()
{
   return m_pdata != (void *)MAP_FAILED;
}



bool local_memory_map::close()
{

   if(m_pdata != (void *)MAP_FAILED)
   {

      ::munmap(m_pdata,::get_file_size(m_iFile));

      m_pdata = NULL;

   }

   if(m_iFile != -1)
   {

      ::close(m_iFile);

      m_iFile = -1;

   }

   return true;

}



bool local_memory_map::open()
{

   close();

   int iOpen;

   if(m_bCreate)
   {

      iOpen = O_RDWR | O_CREAT;

   }
   else
   {

      iOpen = O_RDWR;

   }

   m_iFile = ::open(psz,iOpen,(bRead ? S_IRUSR : 0) | (bWrite ? S_IWUSR : 0));


   if(m_iFile == -1)
   {

      close();

      return false;

   }

   ensure_file_size_fd(m_iFile,size);

   m_pdata = (COLORREF *)mmap(NULL,size,(bRead ? PROT_READ : 0) | (bWrite ? PROT_WRITE : 0),MAP_SHARED,m_hfileBitmap,0);

   if(m_pdata == (void *)MAP_FAILED)
   {

      close();

      return false;

   }

   return true;

}
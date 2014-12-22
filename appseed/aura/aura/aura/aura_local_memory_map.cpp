#include "framework.h"


local_memory_map::local_memory_map()
{

   construct();

}


local_memory_map::local_memory_map(const char * psz,bool bRead,bool bWrite, bool bCreate,::primitive::memory_size size)
{

   construct();

   if(!open(psz,bRead,bWrite,bCreate,size))
   {
      
      string strFormat;

      strFormat.Format("failed to open local_memory_map : \"%s\" bRead %d bWrite %d bCreate %d size %lld ",psz,int(bRead),int(bWrite),int(bCreate),size);

      throw simple_exception(::get_thread_app(),strFormat);

   }

}



local_memory_map::~local_memory_map()
{

   if(is_mapped())
   {

      close();

   }

}


string local_memory_map::get_path()
{

   return dir::path(dir::userappdata("time"),m_strName);

}


// SALADA AND PASTA and me pig searching for food is good EAT IT!! But mama te

#ifdef WINDOWS


void local_memory_map::construct()
{

   m_strName.Empty();
   m_hfile = INVALID_HANDLE_VALUE;
   m_hfilemap = NULL;
   m_pdata = NULL;
   m_bRead = false;
   m_bWrite = false;
   m_bCreate = false;

}


bool local_memory_map::is_mapped()
{
   
   return m_pdata != NULL;

}


bool local_memory_map::open(const char * psz,bool bRead,bool bWrite,bool bCreate,::primitive::memory_size size)
{

   m_strName   = psz;

   m_bRead     = bRead;

   m_bWrite    = bWrite;

   m_bCreate   = bCreate;

   m_size      = size;

   return open();

}


bool local_memory_map::close()
{

   if(m_pdata != NULL)
   {

      UnmapViewOfFile(m_pdata);

      m_pdata = NULL;

   }

   if(m_hfile != NULL)
   {

      try
      {

         ::CloseHandle(m_hfile);

      }
      catch(...)
      {

      }

      m_hfile = NULL;

   }


   if(m_hfile != INVALID_HANDLE_VALUE)
   {

      try
      {

         ::CloseHandle(m_hfile);

      }
      catch(...)
      {

      }

      m_hfile = INVALID_HANDLE_VALUE;

   }

   return true;

}

#endif // WINDOWS
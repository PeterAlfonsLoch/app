#include "framework.h"


bool local_memory_map::open()
{


   close();

   int iOpen;

   if(m_bCreate)
   {
      iOpen = OPEN_ALWAYS;
   }
   else
   {
      iOpen = OPEN_EXISTING;
   }

   wstring wstr(get_path());

   CREATEFILE2_EXTENDED_PARAMETERS ps;
   zero(&ps,sizeof(ps));
   ps.dwSize = sizeof(ps);
   ps.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
   
   m_hfile = CreateFile2(wstr,(m_bRead ? FILE_READ_DATA : 0) | (m_bWrite ? FILE_WRITE_DATA : 0),FILE_SHARE_WRITE | FILE_SHARE_READ,iOpen,&ps);

   if(m_hfile == INVALID_HANDLE_VALUE)
   {

      close();

      return false;

   }

   ensure_file_size_handle(m_hfile,m_size);

   m_hfilemap = CreateFileMappingFromApp(m_hfile, NULL, PAGE_READWRITE, m_size, NULL);

   if(m_hfilemap == NULL)
   {
      
      close();

      return false;
      
   }

   m_pdata = MapViewOfFileFromApp(m_hfilemap, (m_bRead ? FILE_MAP_READ : 0) | (m_bWrite ? FILE_MAP_WRITE : 0), 0, 0);

   if(m_pdata == NULL)
   {

      close();

      return false;

   }

   return true;

}















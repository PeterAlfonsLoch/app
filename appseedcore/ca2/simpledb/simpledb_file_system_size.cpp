#include "StdAfx.h"


file_size_table::get_fs_size::get_fs_size()
{
}

file_size_table::get_fs_size::get_fs_size(const get_fs_size & getfssize)
{
   operator = (getfssize);
}

file_size_table::get_fs_size & file_size_table::get_fs_size::operator = (const get_fs_size & getfssize)
{
   if(this != & getfssize)
   {
      m_strPath         = getfssize.m_strPath;
      m_bPending        = getfssize.m_bPending;
      m_iSize           = getfssize.m_iSize;
      m_bRet            = getfssize.m_bRet;
      m_hwnd            = getfssize.m_hwnd;

   }
   return *this;
}


file_size_table::file_size_table(::ca::application * papp) :
   ca(papp)
{
   m_hmap = NULL;
   m_item.m_pitemParent = NULL;
   m_pwndServer = NULL;
   m_hwndServer = NULL;

   SECURITY_ATTRIBUTES MutexAttributes;
   ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
   MutexAttributes.nLength = sizeof( MutexAttributes );
   MutexAttributes.bInheritHandle = FALSE; // object uninheritable

   // declare and initialize a security descriptor
   SECURITY_DESCRIPTOR SD;
   BOOL bInitOk = InitializeSecurityDescriptor(
                     &SD,
                     SECURITY_DESCRIPTOR_REVISION );
   if ( bInitOk )
   {
      // give the security descriptor a Null Dacl
      // done using the  "TRUE, (PACL)NULL" here
      BOOL bSetOk = SetSecurityDescriptorDacl( &SD,
                                            TRUE,
                                            (PACL)NULL,
                                            FALSE );
      if ( bSetOk )
      {
         // Make the security attributes point
         // to the security descriptor
         MutexAttributes.lpSecurityDescriptor = &SD;
         m_pmutex = new mutex(FALSE, "Global\\ca2::fontopus::file_system_size::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
         m_pevExec = new CEvent(FALSE, FALSE, "Global\\ca2::fontopus::file_system_size::exec_event::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
         m_pevDone = new CEvent(FALSE, FALSE, "Global\\ca2::fontopus::file_system_size::done_event::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
      }
   }
   m_pwnd  = new FileSystemSizeWnd(papp);
   m_pwnd->CreateClient();
}

file_size_table::~file_size_table()
{
}



bool file_size_table::check_map()
{
   return true;
}

file_size_table::item::item()
{
   m_iSize = 0;
   m_iStep = 0;
   m_bPending = false;
   m_bPendingLs = true;
   m_pitemParent = NULL;
}

void file_size_table::item::ls(::ca::application * papp, int & iIteration)
{
   if(m_bDir)
   {
      stringa               straName;
      base_array < __int64, __int64 > iaSize;
      base_array < bool, bool > baIsDir;
      if(path().is_empty())
      {
         papp->m_psystem->dir().root_ones(straName);
         for(int i = 0; i < straName.get_size(); i++)
         {
            item item;
            item.m_bPending = true;
            item.m_bDir = true;
            item.m_strName = straName[i];
            item.m_pitemParent = this;
            if(item.m_strName.Right(1) == "\\")
               item.m_strName = item.m_strName.Left(item.m_strName.get_length() - 1);
            item.m_iStep = 0;
            m_itema.add(item);
         }
      }
      else
      {
         papp->m_psystem->dir().ls(path(), NULL, &straName, &baIsDir, &iaSize);
         for(int i = 0; i < straName.get_size(); i++)
         {
            item item;
            item.m_bPending = baIsDir[i];
            item.m_bPendingLs = baIsDir[i];
            item.m_bDir = baIsDir[i];
            item.m_strName = straName[i];
            item.m_pitemParent = this;
            if(baIsDir[i])
            {
               item.m_iStep = 0;
            }
            else
            {
               item.m_iSize = iaSize[i];
               item.m_iStep = -1;
            }
            m_itema.add(item);
            iIteration++;
         }
      }
      m_bPendingLs = false;

   }
}

string file_size_table::item::path()
{
   if(m_pitemParent == NULL)
      return m_strName;
   else if(m_pitemParent->m_pitemParent == NULL)
      return m_strName;
   else
      return m_pitemParent->path() + "\\" + m_strName;
}

file_size_table::item * file_size_table::item::FindItem(::ca::application * papp, const char * pszPath, int & iIteration)
{
   string strName;
   string strPath(pszPath);
   strPath.replace('/', '\\');

   while(strPath.Left(1) == "\\")
      strPath = strPath.Mid(1);
   int iFind = strPath.find('\\');
   int iFindName;
   if(iFind < 0)
   {
      iFindName = FindName(papp, strPath, iIteration);
      if(iFindName < 0)
         return NULL;
      return &m_itema[iFindName];
   }
   else
   {
      iFindName = FindName(papp, strPath.Left(iFind), iIteration);
      if(iFindName < 0)
         return NULL;
      return m_itema[iFindName].FindItem(papp, strPath.Mid(iFind + 1), iIteration);
      
   }
}
 

int file_size_table::item::FindName(::ca::application * papp, const char * pszName, int & iIteration)
{
   if(m_bPendingLs)
   {
      ls(papp, iIteration);
   }
   for(int i = 0; i < m_itema.get_size(); i++)
   {
      if(m_itema[i].m_strName == pszName)
         return i;
   }
   return -1;
}

void file_size_table::item::update_size(::ca::application * papp, int & iIteration)
{
   UNREFERENCED_PARAMETER(papp);
   UNREFERENCED_PARAMETER(iIteration);
   if(m_bDir)
   {
      m_iSize = 0;
      m_bPending = false;
      for(int i = 0; i < m_itema.get_size(); i++)
      {
         m_iSize += m_itema[i].m_iSize;
         if(m_itema[i].m_bPending || m_itema[i].m_bPendingLs)
            m_bPending = true;
      }
      if(m_pitemParent != NULL && m_bPending)
         m_pitemParent->m_bPending = true;
   }

}

void file_size_table::item::update_size_recursive(::ca::application * papp, int & iIteration)
{
   if(m_bPendingLs)
   {
      ls(papp, iIteration);
   }
   for(int i = 0; i < m_itema.get_size(); i++)
   {
      m_itema[i].update_size_recursive(papp, iIteration);
      if(iIteration > 230)
         break;
   }
   update_size(papp, iIteration);
}



DBFileSystemSizeSet::DBFileSystemSizeSet(::ca::application * papp) :
   ca(papp), m_table(papp)
{
   m_iMaxIteration = 230;
}

DBFileSystemSizeSet::~DBFileSystemSizeSet()
{
}


bool DBFileSystemSizeSet::get_cache_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending)
{
   return false;
   CSingleLock sl(m_table.m_pmutex, FALSE);
  // Wait for mutex. Once it is obtained, no other client may
  // communicate with the server
   if(!sl.Lock(0))
      return false;
   if(!m_table.check_map())
      return false;

   m_table.m_pwnd->get_fs_size(i64Size, pszPath, bPending);
   file_size_table::get_fs_size size;
   FileSystemSizeWnd::size_map::pair * ppair = m_table.m_pwnd->m_map.PLookup(pszPath);
   if(ppair != NULL)
   {
      i64Size     = ppair->m_value.m_iSize;
      bPending    = ppair->m_value.m_bPending;
      return true;
   }
   return  false;

    // Fill shared primitive::memory
    //::ZeroMemory(&m_pMsg, sizeof(TSharedMemory));
    //m_pMsg->m_dwProcessID = m_dwProcessId;
/*    _tcscpy(m_table.m_pgetfssize->m_szPath, pszPath);

    // Signal server to process this request
    m_table.m_pevExec->SetEvent();
    // Wait for server to finish
    if (m_table.m_pevDone->Lock(0))
    {
      // Server finished processing data, handle data returned by the Server
       i64Size = m_table.m_pgetfssize->m_iSize;
       bPending = m_table.m_pgetfssize->m_bPending;
       return m_table.m_pgetfssize->m_bRet;
    }
    else
    {
      // Timeout waiting for response from server
       return false;
    }*/
}

bool DBFileSystemSizeSet::get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending)
{
   int iIteration = 0;
   CSingleLock sl(m_table.m_pmutex, FALSE);
   if(!sl.Lock(0))
      return false;
   if(!get_fs_size(i64Size, pszPath, bPending, iIteration))
      return false;

   return true;
}

bool DBFileSystemSizeSet::get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending, int & iIteration)
{
   CSingleLock sl(m_table.m_pmutex, FALSE);
   if(!sl.Lock(0))
      return false;
   if(iIteration >= m_iMaxIteration)
   {
      bPending = true;
      return true;
   }
   string strTitle = System.file().name_(pszPath);
   file_size_table::item * pitem = m_table.m_item.FindItem(get_app(), pszPath, iIteration);
   if(pitem != NULL)
   {
      bPending = pitem->m_bPending;
      i64Size = pitem->m_iSize;
      if(!bPending)
      {
         return true;
      }
   }
   else
   {
      return false;
   }
   pitem->update_size_recursive(m_papp, iIteration);
   bPending = pitem->m_bPending;
   i64Size = pitem->m_iSize;
   return true;
}

FileSystemSizeWnd::FileSystemSizeWnd(::ca::application * papp) :
   ca(papp),
   ::ca::window_sp(papp)
{
}

void FileSystemSizeWnd::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   m_p->_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_COPYDATA, pinterface, this, &FileSystemSizeWnd::_001OnCopyData);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &FileSystemSizeWnd::_001OnTimer);
}

bool FileSystemSizeWnd::CreateClient()
{
   m_bServer = false;
      ::user::interaction * puiMessage = NULL;
#if !core_level_1 && !core_level_2
      puiMessage = System.window_from_os_data(HWND_MESSAGE);
#endif
   return m_p->create(NULL, "ca2::fontopus::FileSystemSizeWnd::Client", 0, rect(0, 0, 0, 0), puiMessage, id()) != FALSE;
}

bool FileSystemSizeWnd::CreateServer()
{
   m_bServer = true;
   if(!m_p->create(NULL, "Local\\ca2::fontopus::FileSystemSizeWnd::Server", 0, 
      rect(0, 0, 0, 0), System.window_from_os_data(HWND_MESSAGE), id()))
      return false;
   m_p->SetTimer(100, 100, NULL);
   return true;
}

bool FileSystemSizeWnd::get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending)
{
   db_server * pcentral = dynamic_cast < db_server * > (&System.db());
   HWND hwnd = pcentral->m_pfilesystemsizeset->m_table.m_hwndServer;
   if(hwnd == NULL || ! ::IsWindow(hwnd))
   {
      if(pcentral->m_pfilesystemsizeset->m_table.m_hwndServer == NULL)
      {
         ClientStartServer();
      }
      return false;
   }
   file_size_table::get_fs_size size;
   size.m_strPath = pszPath;
   size.m_bRet = false;


   gen::memory_file file(get_app());
   size.write(file);

   COPYDATASTRUCT data;
   data.dwData = 0;
   data.cbData = file.get_length();
   data.lpData = file.GetAllocation();
   HWND hwndWparam = (HWND) m_p->get_os_data();
   WPARAM wparam = (WPARAM) hwndWparam;
   if(::SendMessage(hwnd, WM_COPYDATA, wparam, (LPARAM) &data))
   {
      i64Size = m_size.m_iSize;
      bPending = m_size.m_bPending;

      return m_bRet;
   }
   else
   {
      return false;
   }
}


void FileSystemSizeWnd::_001OnCopyData(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);

   COPYDATASTRUCT * pstruct = (COPYDATASTRUCT *) pbase->m_lparam;
   if(pstruct->dwData == 0)
   {
      //file_size_table::get_fs_size * prec  = (file_size_table::get_fs_size *) pstruct->lpData;
      db_server * pcentral = &System.db();
      file_size_table::get_fs_size size;
      gen::memory_file file(get_app(), pstruct->lpData, pstruct->cbData);
      size.read(file);

      CSingleLock sl(&m_cs, TRUE);
      size.m_hwnd = (HWND) pbase->m_wparam;
      size.m_bRet =  pcentral->m_pfilesystemsizeset->get_fs_size(
         size.m_iSize,
         size.m_strPath,
         size.m_bPending);
      m_sizea.add(size);
      pbase->set_lresult(1);
   }
   else if(pstruct->dwData == 1)
   {
      file_size_table::get_fs_size size;
      gen::memory_file file(get_app(), pstruct->lpData, pstruct->cbData);
      size.read(file);
      m_bRet = true;
      m_map.set_at(size.m_strPath, size);
      pbase->set_lresult(1);
   }

}

void FileSystemSizeWnd::_001OnTimer(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj);
   if(ptimer->m_nIDEvent == 100)
   {
      //::PostMessage((HWND) pbase->m_wparam, WM_COPYDATA, (WPARAM) get_handle(), (LPARAM) &data);
      if(m_sizea.get_size() > 0)
      {
         COPYDATASTRUCT data;
         data.dwData = 1;
         
         
         gen::memory_file file(get_app());

         while(m_sizea.get_size() > 0)
         {
            CSingleLock sl(&m_cs, TRUE);
            file_size_table::get_fs_size & size = m_sizea[0];
            file.Truncate(0);
            size.write(file);
            data.cbData = file.get_length();
            data.lpData = file.GetAllocation();
            ::SendMessage((HWND) size.m_hwnd, WM_COPYDATA, (WPARAM) m_p->get_os_data(), (LPARAM) &data);
            m_sizea.remove_at(0);
         }
      }
   }
}

FileSystemSizeServerThread::FileSystemSizeServerThread(::ca::application * papp) :
   ca(papp), 
   thread(papp)
{
}

bool FileSystemSizeServerThread::initialize_instance()
{
   db_server * pcentral = &System.db();
   pcentral->m_pfilesystemsizeset->m_table.m_pwndServer->CreateServer();
   return true;
}

void FileSystemSizeWnd::ClientStartServer()  
{
   db_server * pcentral = &System.db();
   if(GetTickCount() - m_dwLastStartTime > 2000)
   {
      m_dwLastStartTime = GetTickCount();
      ::ShellExecute(NULL, NULL, System.dir().path(System.get_module_folder(), "winservice_filesystemsizeapp"), NULL, NULL, SW_HIDE);
   }
   pcentral->m_pfilesystemsizeset->m_table.m_hwndServer = ::FindWindowEx(HWND_MESSAGE, NULL, NULL, "Local\\ca2::fontopus::FileSystemSizeWnd::Server");
}

      
void file_size_table::get_fs_size::write(ex1::output_stream & ostream)
{
   ostream << m_strPath;
   ostream << m_bPending;
   ostream << m_iSize;
   ostream << m_bRet;
   ostream << (int) m_hwnd;
}

void file_size_table::get_fs_size::read(ex1::input_stream & istream)
{
   istream >> m_strPath;
   istream >> m_bPending;
   istream >> m_iSize;
   istream >> m_bRet;
   istream >> (int &) m_hwnd;
}

   

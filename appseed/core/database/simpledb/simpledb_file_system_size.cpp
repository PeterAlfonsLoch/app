#include "framework.h"


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
      m_oswindow            = getfssize.m_oswindow;

   }
   return *this;
}


file_size_table::file_size_table(sp(::axis::application) papp) :
   element(papp)
{
   m_hmap = NULL;
   m_item.m_pitemParent = NULL;
   m_pwndServer = NULL;
   m_oswindowServer = NULL;

/*   SECURITY_ATTRIBUTES MutexAttributes;
   ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
   MutexAttributes.nLength = sizeof( MutexAttributes );
   MutexAttributes.bInheritHandle = FALSE; // object uninheritable

   // declare and initialize a security descriptor
   SECURITY_DESCRIPTOR SD;
   bool bInitOk = InitializeSecurityDescriptor(
                     &SD,
                     SECURITY_DESCRIPTOR_REVISION );
   if ( bInitOk )
   {
      // give the security descriptor a Null Dacl
      // done using the  "TRUE, (PACL)NULL" here
      bool bSetOk = SetSecurityDescriptorDacl( &SD,
                                            TRUE,
                                            (PACL)NULL,
                                            FALSE );
      if ( bSetOk )
      {
         // Make the security attributes point
         // to the security descriptor
         MutexAttributes.lpSecurityDescriptor = &SD;*/
         //m_pmutex = new mutex(FALSE, "Global\\::draw2d::fontopus::file_system_size::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
         //m_pevExec = new event(FALSE, FALSE, "Global\\::draw2d::fontopus::file_system_size::exec_event::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
         //m_pevDone = new event(FALSE, FALSE, "Global\\::draw2d::fontopus::file_system_size::done_event::7807e510-5579-11dd-ae16-0800200c7784", &MutexAttributes);
         //m_pmutex = new mutex(FALSE, "Local\\::draw2d::fontopus::file_system_size::7807e510-5579-11dd-ae16-0800200c7784");
         //m_pevExec = new event(FALSE, FALSE, "Local\\::draw2d::fontopus::file_system_size::exec_event::7807e510-5579-11dd-ae16-0800200c7784");
         //m_pevDone = new event(FALSE, FALSE, "Local\\::draw2d::fontopus::file_system_size::done_event::7807e510-5579-11dd-ae16-0800200c7784");
/*      }
   }*/
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

void file_size_table::item::ls(sp(::axis::application) papp, index & iIteration)
{
   if(m_bDir)
   {
      stringa               straPath;
      stringa               straTitle;
      int64_array iaSize;
      bool_array baIsDir;
      if(path().is_empty())
      {
         sess(papp).dir().root_ones(straPath, straTitle);
         for(int32_t i = 0; i < straPath.get_size(); i++)
         {
            item item;
            item.m_bPending = true;
            item.m_bDir = true;
            item.m_strName = straPath[i];
            item.m_pitemParent = this;
            if(item.m_strName.Right(1) == "\\")
               item.m_strName = item.m_strName.Left(item.m_strName.get_length() - 1);
            item.m_iStep = 0;
            m_itema.add(new file_size_table::item(item));
         }
      }
      else
      {
         sess(papp).dir().ls(path(), &straPath, &straTitle, &baIsDir, &iaSize);
         for(int32_t i = 0; i < straTitle.get_size(); i++)
         {
            item item;
            item.m_bPending = baIsDir[i];
            item.m_bPendingLs = baIsDir[i];
            item.m_bDir = baIsDir[i];
            item.m_strName = straTitle[i];
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
            m_itema.add(new file_size_table::item(item));
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

file_size_table::item * file_size_table::item::FindItem(sp(::axis::application) papp, const char * pszPath, index & iIteration)
{
   string strName;
   string strPath(pszPath);
   strPath.replace('/', '\\');

   while(strPath.Left(1) == "\\")
      strPath = strPath.Mid(1);
   strsize iFind = strPath.find('\\');
   strsize iFindName;
   if(iFind < 0)
   {
      iFindName = FindName(papp, strPath, iIteration);
      if(iFindName < 0)
         return NULL;
      return m_itema(iFindName);
   }
   else
   {
      iFindName = FindName(papp, strPath.Left(iFind), iIteration);
      if(iFindName < 0)
         return NULL;
      return m_itema[iFindName].FindItem(papp, strPath.Mid(iFind + 1), iIteration);

   }
}


index file_size_table::item::FindName(sp(::axis::application) papp, const char * pszName, index & iIteration)
{
   if(m_bPendingLs)
   {
      ls(papp, iIteration);
   }
   for(index i = 0; i < m_itema.get_size(); i++)
   {
      if(m_itema[i].m_strName == pszName)
         return i;
   }
   return -1;
}

void file_size_table::item::update_size(sp(::axis::application) papp, index & iIteration)
{
   UNREFERENCED_PARAMETER(papp);
   UNREFERENCED_PARAMETER(iIteration);
   if(m_bDir)
   {
      m_iSize = 0;
      m_bPending = false;
      for(int32_t i = 0; i < m_itema.get_size(); i++)
      {
         m_iSize += m_itema[i].m_iSize;
         if(m_itema[i].m_bPending || m_itema[i].m_bPendingLs)
            m_bPending = true;
      }
      if(m_pitemParent != NULL && m_bPending)
         m_pitemParent->m_bPending = true;
   }

}

void file_size_table::item::update_size_recursive(sp(::axis::application) papp, index & iIteration)
{
   if(m_bPendingLs)
   {
      ls(papp, iIteration);
   }
   for(int32_t i = 0; i < m_itema.get_size(); i++)
   {
      m_itema[i].update_size_recursive(papp, iIteration);
      if(iIteration > 230)
         break;
   }
   update_size(papp, iIteration);
}



DBFileSystemSizeSet::DBFileSystemSizeSet(sp(::axis::application) papp) :
   element(papp), m_table(papp)
{
   m_iMaxIteration = 230;
}

DBFileSystemSizeSet::~DBFileSystemSizeSet()
{
}


bool DBFileSystemSizeSet::get_cache_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending)
{
   return false;
   single_lock sl(m_table.m_pmutex, FALSE);
  // Wait for mutex. Once it is obtained, no other client may
  // communicate with the server
   if(!sl.lock(duration::zero()))
      return false;
   if(!m_table.check_map())
      return false;

   m_table.m_pwnd->get_fs_size(i64Size, pszPath, bPending);
   file_size_table::get_fs_size size;
   FileSystemSizeWnd::size_map::pair * ppair = m_table.m_pwnd->m_map.PLookup(pszPath);
   if(ppair != NULL)
   {
      i64Size     = ppair->second.m_iSize;
      bPending    = ppair->second.m_bPending;
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
    if (m_table.m_pevDone->lock(0))
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

bool DBFileSystemSizeSet::get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending)
{
   index iIteration = 0;
   single_lock sl(m_table.m_pmutex, FALSE);
   if(!sl.lock(duration::zero()))
      return false;
   if(!get_fs_size(i64Size, pszPath, bPending, iIteration))
      return false;

   return true;
}

bool DBFileSystemSizeSet::get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending, index & iIteration)
{
   single_lock sl(m_table.m_pmutex, FALSE);
   if(!sl.lock(duration::zero()))
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
   pitem->update_size_recursive(m_paxisapp, iIteration);
   bPending = pitem->m_bPending;
   i64Size = pitem->m_iSize;
   return true;
}

FileSystemSizeWnd::FileSystemSizeWnd(sp(::axis::application) papp) :
   element(papp),
   ::window_sp(papp)
{
}

void FileSystemSizeWnd::install_message_handling(::message::dispatch * pinterface)
{
   m_p->install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_COPYDATA, pinterface, this, &FileSystemSizeWnd::_001OnCopyData);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &FileSystemSizeWnd::_001OnTimer);
}

bool FileSystemSizeWnd::CreateClient()
{

//#ifdef WINDOWS

   m_bServer = false;
   return m_p->create_message_queue("::draw2d::fontopus::FileSystemSizeWnd::Client");
/*  sp(::user::interaction) puiMessage = NULL;
   puiMessage = System.window_from_os_data(HWND_MESSAGE);
   return m_p->create(NULL, "::draw2d::fontopus::FileSystemSizeWnd::Client", 0, rect(0, 0, 0, 0), puiMessage, id()) != FALSE;*/

//#else

  // throw not_implemented(get_app());

//#endif

}

bool FileSystemSizeWnd::CreateServer()
{

#ifdef WINDOWS

   m_bServer = true;
   if(!m_p->create_window(NULL,"Local\\::draw2d::fontopus::FileSystemSizeWnd::Server",0,null_rect(),System.window_from_os_data(HWND_MESSAGE),id()))
      return false;
   m_p->SetTimer(100, 100, NULL);
   return true;

#else

   throw not_implemented(get_app());

#endif

}

bool FileSystemSizeWnd::get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending)
{

#ifdef WINDOWSEX

   db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
   oswindow oswindow = pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer;
   if(oswindow == NULL || ! ::IsWindow(oswindow))
   {
      if(pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer == NULL)
      {
         ClientStartServer();
      }
      return false;
   }
   file_size_table::get_fs_size size;
   size.m_strPath = pszPath;
   size.m_bRet = false;


   ::file::byte_stream_memory_buffer file(get_app());
   size.write(file);

   COPYDATASTRUCT data;
   data.dwData = 0;
   data.cbData = (uint32_t) file.get_length();
   data.lpData = file.get_data();
   ::oswindow oswindowWparam = (::oswindow) m_p->get_os_data();
   WPARAM wparam = (WPARAM) oswindowWparam;
   if(::SendMessage(oswindow, WM_COPYDATA, wparam, (LPARAM) &data))
   {
      i64Size = m_size.m_iSize;
      bPending = m_size.m_bPending;

      return m_bRet;
   }
   else
   {
      return false;
   }

#else

   throw not_implemented(get_app());

#endif

}


void FileSystemSizeWnd::_001OnCopyData(signal_details * pobj)
{

#ifdef WINDOWSEX

   SCAST_PTR(::message::base, pbase, pobj);

   COPYDATASTRUCT * pstruct = (COPYDATASTRUCT *) pbase->m_lparam.m_lparam;
   if(pstruct->dwData == 0)
   {
      //file_size_table::get_fs_size * prec  = (file_size_table::get_fs_size *) pstruct->lpData;
      db_server * pcentral = &System.m_simpledb.db();
      file_size_table::get_fs_size size;
      ::file::byte_stream_memory_buffer file(get_app(), pstruct->lpData, pstruct->cbData);
      size.read(file);

      single_lock sl(&m_cs, TRUE);
      size.m_oswindow = (oswindow) pbase->m_wparam;
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
      ::file::byte_stream_memory_buffer file(get_app(), pstruct->lpData, pstruct->cbData);
      size.read(file);
      m_bRet = true;
      m_map.set_at(size.m_strPath, size);
      pbase->set_lresult(1);
   }

#else

   throw not_implemented(get_app());

#endif


}

void FileSystemSizeWnd::_001OnTimer(signal_details * pobj)
{

#ifdef WINDOWSEX

    SCAST_PTR(::message::timer, ptimer, pobj);
   if(ptimer->m_nIDEvent == 100)
   {
      //::PostMessage(pbase->m_wparam, WM_COPYDATA, (WPARAM) get_handle(), (LPARAM) &data);
      if(m_sizea.get_size() > 0)
      {
         COPYDATASTRUCT data;
         data.dwData = 1;


         ::file::byte_stream_memory_buffer file(get_app());

         while(m_sizea.get_size() > 0)
         {
            single_lock sl(&m_cs, TRUE);
            file_size_table::get_fs_size & size = m_sizea[0];
            file.m_spmemorybuffer->Truncate(0);
            size.write(file);
            data.cbData = (uint32_t) file.get_length();
            data.lpData = file.get_data();
            ::SendMessage(size.m_oswindow, WM_COPYDATA, (WPARAM) m_p->get_os_data(), (LPARAM) &data);
            m_sizea.remove_at(0);
         }
      }
   }

#else

   throw not_implemented(get_app());

#endif


}

FileSystemSizeServerThread::FileSystemSizeServerThread(sp(::axis::application) papp) :
   element(papp),
   thread(papp)
{
}

bool FileSystemSizeServerThread::initialize_instance()
{
   db_server * pcentral = &System.m_simpledb.db();
   pcentral->m_pfilesystemsizeset->m_table.m_pwndServer->CreateServer();
   return true;
}

void FileSystemSizeWnd::ClientStartServer()
{

#ifdef WINDOWSEX

   db_server * pcentral = &System.m_simpledb.db();

   if(get_tick_count() - m_dwLastStartTime > 2000)
   {
      m_dwLastStartTime = get_tick_count();

      simple_shell_launcher launcher(NULL, NULL, System.dir().path(System.get_module_folder(), "winservice_filesystemsizeapp"), NULL, NULL, SW_HIDE);

      launcher.execute();


   }

   pcentral->m_pfilesystemsizeset->m_table.m_oswindowServer = ::FindWindowEx(HWND_MESSAGE, NULL, NULL, "Local\\::draw2d::fontopus::FileSystemSizeWnd::Server");

#else

   throw not_implemented(get_app());

#endif

}


void file_size_table::get_fs_size::write(::file::output_stream & ostream)
{
   ostream << m_strPath;
   ostream << m_bPending;
   ostream << m_iSize;
   ostream << m_bRet;

#ifdef WINDOWSEX

   ostream << (int32_t) m_oswindow;

#else

   throw not_implemented(get_thread_app());

#endif


}

void file_size_table::get_fs_size::read(::file::input_stream & istream)
{
   istream >> m_strPath;
   istream >> m_bPending;
   istream >> m_iSize;
   istream >> m_bRet;

#ifdef WINDOWS

   istream >> (int32_t &) m_oswindow;

#else

   throw not_implemented(get_thread_app());

#endif


}



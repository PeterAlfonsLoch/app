#include "framework.h"
#include "db_str_set.h"


int g_idbchange;


db_server::db_server(::ca::application * papp) :
   ca(papp),
   ::ca::window_sp(papp)
{
   m_pdb                = NULL;
   m_pSongsDirsSet      = NULL;
   m_pLongsSet          = NULL;
   m_pStringSet         = NULL;
   m_bWorking           = false;
   m_pimpost            = NULL;
   m_pveievpost         = NULL;
   m_pfilesystemsizeset = NULL;
   m_pdatabaseImpl      = NULL;
   m_bRemote            = true;
   m_pmysqldbUser       = NULL;
}

db_server::~db_server()
{
   close();
}

string db_server::calc_key(::database::id & idSection, ::database::id & id, ::database::id & idIndex)
{
   string str;
   str = idSection.get_id().str();
   str += ".";
   str += id.get_id().str();
   str += ".";
   str += idIndex.get_id().str();
   return str;
}

bool db_server::initialize_user(mysql::database * pmysqldbUser, const char * pszUser)
{

   if(pmysqldbUser == NULL)
      return false;

   m_bRemote         = false;

   m_pmysqldbUser    = pmysqldbUser;
   m_strUser         = pszUser;

//   m_pdb = new ::sqlite::base(get_app());

/*   string str;
   str = Application.dir().userappdata("prop.db");
   Application.dir().mk(System.dir().name(str));
   m_pdb->setDatabase(str);
   m_pdb->connect();

   m_pdatabaseImpl = new ::sqlite::base(get_app());

   str = Application.dir().userappdata("_prop002.db");
   Application.dir().mk(System.dir().name(str));
   m_pdatabaseImpl->setDatabase(str);
   m_pdatabaseImpl->connect();*/

   m_pLongsSet    = new db_long_set(this);
   m_pStringSet   = new db_str_set(this);

   if(!create_message_window())
      return false;

   m_bWorking = true;

   return true;

}


bool db_server::initialize()
{

   if(System.directrix().m_varTopicQuery["app"] == "app-core/netnodelite"
	||  System.directrix().m_varTopicQuery["app"] == "app-core/tesseract/netnodecfg")
   {
      m_bRemote = false;
   }


   m_pdb = new ::sqlite::base(get_app());

   string str;
   str = Application.dir().userappdata("prop.db");
   Application.dir().mk(System.dir().name(str));
   m_pdb->setDatabase(str);
   m_pdb->connect();

   m_pdatabaseImpl = new ::sqlite::base(get_app());

   str = Application.dir().userappdata("_prop002.db");
   Application.dir().mk(System.dir().name(str));
   m_pdatabaseImpl->setDatabase(str);
   m_pdatabaseImpl->connect();

   m_pLongsSet = new db_long_set(&Application.db());
   m_pStringSet = new db_str_set(&Application.db());

   int iBufferSize = 128 * 1024;
   gen::command_thread & commandthread = System.command();

   if(commandthread.m_varTopicQuery.has_property("filesizebuffer"))
   {
      iBufferSize = commandthread.m_varTopicQuery["filesizebuffer"] * 1024 * 1024;
   }

   m_pfilesystemsizeset = new DBFileSystemSizeSet(&System);


   //var varChange;
   //data_server_load("ca2_fontopus_votagus", "database_change", "change", varChange);
   //g_idbchange = varChange;

   if(!create_message_window())
      return false;



   m_bWorking = true;



   return true;
}

bool db_server::finalize()
{
   m_bWorking = false;

   destroy_message_window();

   if(m_pfilesystemsizeset != NULL)
   {
      delete m_pfilesystemsizeset;
      m_pfilesystemsizeset = NULL;
   }


   if(m_pStringSet != NULL)
   {
      delete m_pStringSet;
      m_pStringSet = NULL;
   }


   if(m_pLongsSet != NULL)
   {
      delete m_pLongsSet;
      m_pLongsSet = NULL;
   }


   if(m_pdatabaseImpl != NULL)
   {
      m_pdatabaseImpl->disconnect();
      delete m_pdatabaseImpl;
      m_pdatabaseImpl = NULL;
   }


   if(m_pdb != NULL)
   {
      m_pdb->disconnect();
      delete m_pdb;
      m_pdb = NULL;
   }



   return true;
}

bool db_server::create_message_window()
{

#ifdef WINDOWS

   if(!m_p->IsWindow())
   {
      string strName = "ca2::fontopus::message_wnd::simpledb::db_server";
      ::user::interaction * puiMessage = NULL;
      puiMessage = System.window_from_os_data(HWND_MESSAGE);
      if(!m_p->create(NULL, strName, 0, rect(0, 0, 0, 0), puiMessage, NULL))
      {
         return false;
      }

      m_p->SetTimer(1258477, 484, NULL);

      IGUI_WIN_MSG_LINK(WM_TIMER, m_p, this, &db_server::_001OnTimer);

   }

   return true;

#else

   throw not_implemented_exception(get_app());

#endif

}

bool db_server::destroy_message_window()
{
   if(m_p != NULL && m_p->IsWindow())
   {
      return m_p->DestroyWindow() != FALSE;
   }
   return true;
}

void db_server::_001OnTimer(gen::signal_object * pobj)
{
   SCAST_PTR(::gen::message::timer, ptimer, pobj);
   if(ptimer->m_nIDEvent == 1258477)
   {
      /*var varChange;
      var var;
      data_server_load("ca2_fontopus_votagus", "database_change", "change", varChange);
      while(g_idbchange <= (int) varChange)
      {
         if(data_server_load("ca2_fontopus_votagus", "database_change", g_idbchange, var))
         {
            if(var.stra().get_count() == 3)
            {
               try
               {
                  data_pulse_change(var.stra()[0], var.stra()[1], var.stra()[2], NULL);
               }
               catch(...)
               {
               }
            }
         }
         g_idbchange++;
      }
      */
   }
}


void db_server::close()
{
   if(m_pSongsDirsSet != NULL)
   {
      delete m_pSongsDirsSet;
      m_pSongsDirsSet = NULL;
   }
   if(m_pStringSet != NULL)
   {
      delete m_pStringSet;
      m_pStringSet = NULL;
   }
   if(m_pLongsSet != NULL)
   {
      delete m_pLongsSet;
      m_pLongsSet = NULL;
   }
    m_bWorking = false;
}


bool db_server::data_server_load(::database::id idSection, ::database::id id, ::database::id idIndex, ex1::writable & writable, ::database::update_hint * phint)
{
   UNREFERENCED_PARAMETER(phint);
//   single_lock sl(&m_csImplDatabase, TRUE);
   if(!load(calc_key(idSection, id, idIndex), writable))
      return false;
   return true;
}

bool db_server::data_server_save(::database::id idSection, ::database::id id, ::database::id idIndex, ex1::readable & readable, ::database::update_hint * phint)
{
   UNREFERENCED_PARAMETER(phint);
   single_lock sl(&m_csImplDatabase, TRUE);
   if(!save(calc_key(idSection, id, idIndex), readable))
      return false;
/*   if(idSection.m_id.str() != "ca2_fontopus_votagus" ||
      id.m_id.str() != "database_change")
   {
      try
      {
         m_pdb->start_transaction();
         var varChange;
         data_server_load("ca2_fontopus_votagus", "database_change", "change", varChange);
         varChange++;
         stringa stra;
         stra.add(idSection.m_id);
         stra.add(id.m_id);
         stra.add(idIndex.m_id);
         if(!data_save("ca2_fontopus_votagus", "database_change", varChange.get_integer(), stra))
         {
            m_pdb->rollback_transaction();
            goto end_write_change;
         }
         if(!data_server_save("ca2_fontopus_votagus", "database_change", "change", varChange))
         {
            m_pdb->rollback_transaction();
            goto end_write_change;
         }

         m_pdb->commit_transaction();
      }
      catch(...)
      {
         m_pdb->rollback_transaction();
      }
end_write_change:;
   }*/
   return true;
}

bool db_server::load(const char * lpcszKey, string & str)
{
   //single_lock sl(&m_csImplDatabase, TRUE);
   if(get_db_str_set() == NULL)
      return false;
   return get_db_str_set()->load(lpcszKey, str);
}



bool db_server::load(const char * lpKey, ::ex1::writable &  writable)
{
//   single_lock sl(&m_csImplDatabase, TRUE);
   string str;
   if(!load(lpKey, str))
   {
      return false;
   }
   writable.From(str);
   return true;
}

bool db_server::save(const char * lpcszKey, const char * lpcsz)
{
   single_lock sl(&m_csImplDatabase, TRUE);
   if(get_db_str_set() == NULL)
      return false;
   return get_db_str_set()->save(lpcszKey, lpcsz);
}


bool db_server::save(const char * lpKey, ex1::readable & readable)
{
   single_lock sl(&m_csImplDatabase, TRUE);
   string str;
   readable.To(str);
//   int iLength = str.get_length();
//   int iKeyLen = strlen(lpKey);
   if(!save(lpKey, str))
      return false;
   return true;
}

/*
bool db_server::Save(const char * lpcszSection, const char * lpcszKey, WINDOWPLACEMENT & wp)
{
   return get_db_long_set()->Save(
      lpcszSection,
      lpcszKey,
      wp);
}

void db_server::AddListener(_vmsdb::DBCentralListener *plistener)
{
   m_listenerset.add(plistener);
}

bool db_server::GetDefaultImageDirectorySet(stringa *pwstra)
{
   m_listenerset.OnEvent(
      _vmsdb::DBEventGetDefaultImageDirectorySet,
      (LPARAM) pwstra);
   return true;
}

MidiInstrumentSet * db_server::GetMidiInstrumentSet()
{
   return m_pmidiinstrumentset;
}
*/

::sqlite::base * db_server::GetImplDatabase()
{
   return m_pdatabaseImpl;
}

critical_section * db_server::GetImplCriticalSection()
{
   return &m_csImplDatabase;
}

bool db_server::data_pulse_change(::database::id idSection, ::database::id id, ::database::id idIndex, ::database::update_hint * puh)
{
   return ::database::server::data_pulse_change(
      idSection,
      id,
      idIndex,
      puh);
}

void db_server::assert_valid() const
{
   // return void HAHAHAHAHAHA
}

void db_server::dump(dump_context &) const
{
   // return void HAHAHAHAHAHA
}

im_post & db_server::im_post()
{
   if(m_pimpost == NULL)
   {
      m_pimpost = new class im_post(this);
   }
   return *m_pimpost;
}

veiev_post & db_server::veiev_post()
{
   if(m_pveievpost == NULL)
   {
      m_pveievpost = new class veiev_post(this);
   }
   return *m_pveievpost;
}

db_str_set * db_server::get_db_str_set()
{
   return m_pStringSet;
}

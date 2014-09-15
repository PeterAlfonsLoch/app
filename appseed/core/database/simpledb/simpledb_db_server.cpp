#include "framework.h"
#include "db_str_set.h"


int32_t g_idbchange;


db_server::db_server(sp(::aura::application) papp) :
   element(papp)
{
   
   m_pdb                = NULL;
   m_plongset           = NULL;
   m_pstrset            = NULL;
   m_bWorking           = false;
   m_pfilesystemsizeset = NULL;
   m_bRemote            = true;
   m_pmysqldbUser       = NULL;

}


db_server::~db_server()
{

   close();

}


string db_server::calc_key(::database::client * pclient, ::database::id & idSection, ::database::id & id, ::database::id & idIndex)
{
   if(pclient != NULL)
   {
      return pclient->calc_key(idSection, id, idIndex);
   }
   else
   {
      string str;
      str = idSection.get_id().str();
      str += ".";
      str += id.get_id().str();
      str += ".";
      str += idIndex.get_id().str();
      return str;
   }
}

bool db_server::initialize_user(mysql::database * pmysqldbUser, const char * pszUser)
{

   if(pmysqldbUser == NULL)
      return false;

   m_bRemote         = false;

   m_pmysqldbUser    = pmysqldbUser;
   m_strUser         = pszUser;

   m_plongset        = new db_long_set(this);
   m_pstrset         = new db_str_set(this);

   if(!create_message_queue())
      return false;

   m_bWorking = true;

   return true;

}


bool db_server::initialize()
{

   if(System.directrix()->m_varTopicQuery["app"] == "app-core/netnodelite"
   || System.directrix()->m_varTopicQuery["app"] == "app-core/netnode_dynamic_web_server"
   || System.directrix()->m_varTopicQuery["app"] == "app-core/netnode_dynamic_web_server_cfg"
   || System.directrix()->m_varTopicQuery["app"] == "app-core/netnodecfg"
   || System.directrix()->m_varTopicQuery["app"] == "app-core/mydns"
   || System.directrix()->m_varTopicQuery["app"] == "app-gtech/sensible_netnode"
   || System.directrix()->m_varTopicQuery["app"] == "app-gtech/sensible_service")
   {
      m_bRemote = false;
   }


   m_pdb          = new ::sqlite::base(get_app());

   m_pdb->create_long_set("integertable");
   m_pdb->create_string_set("stringtable");

   string str;
   str = Application.dir().userappdata("database.sqlite");
   Application.dir().mk(System.dir().name(str));
   m_pdb->setDatabase(str);
   m_pdb->connect();

   m_plongset     = new db_long_set(this);
   m_pstrset      = new db_str_set(this);

   int32_t iBufferSize = 128 * 1024;
   sp(::command_thread) commandthread = System.command();

   if(commandthread->m_varTopicQuery.has_property("filesizebuffer"))
   {
      iBufferSize = commandthread->m_varTopicQuery["filesizebuffer"] * 1024 * 1024;
   }


#if !defined(METROWIN) && !defined(APPLEOS)

   if(!create_message_queue())
      return false;

#endif

   m_bWorking = true;

   return true;

}


bool db_server::finalize()
{

   m_bWorking = false;

   destroy_message_queue();

   if(m_pfilesystemsizeset != NULL)
   {
      delete m_pfilesystemsizeset;
      m_pfilesystemsizeset = NULL;
   }


   if(m_pstrset != NULL)
   {
      delete m_pstrset;
      m_pstrset = NULL;
   }


   if(m_plongset != NULL)
   {
      delete m_plongset;
      m_plongset = NULL;
   }


   if(m_pdb != NULL)
   {
      m_pdb->disconnect();
      m_pdb.release();
   }

   return true;

}

bool db_server::create_message_queue()
{

   if(!IsWindow())
   {
      string strName = "::draw2d::fontopus::message_wnd::simpledb::db_server";
      if(!::user::interaction::create_message_queue(strName))
      {
         return false;
      }

      SetTimer(1258477, 484, NULL);

      IGUI_WIN_MSG_LINK(WM_TIMER, m_pimpl, this, &db_server::_001OnTimer);

   }

   return true;


}

bool db_server::destroy_message_queue()
{
   if(IsWindow())
   {
      return DestroyWindow() != FALSE;
   }
   return true;
}

void db_server::_001OnTimer(signal_details * pobj)
{
   
   SCAST_PTR(::message::timer, ptimer, pobj);
   
   if(ptimer->m_nIDEvent == 1258477)
   {

   }

}


void db_server::close()
{

   if(m_pstrset != NULL)
   {
      delete m_pstrset;
      m_pstrset = NULL;
   }

   if(m_plongset != NULL)
   {
      delete m_plongset;
      m_plongset = NULL;
   }

   m_bWorking = false;

}


bool db_server::data_server_load(::database::client * pclient, ::database::id idSection, ::database::id id, ::database::id idIndex, ::file::output_stream & writable, ::database::update_hint * phint)
{

   UNREFERENCED_PARAMETER(phint);

   if(!load(calc_key(pclient, idSection, id, idIndex), writable))
      return false;

   return true;

}


bool db_server::data_server_save(::database::client * pclient, ::database::id idSection, ::database::id id, ::database::id idIndex, ::file::input_stream & readable, ::database::update_hint * phint)
{

   UNREFERENCED_PARAMETER(phint);

   if(!save(calc_key(pclient, idSection, id, idIndex), readable))
      return false;

   return true;

}


bool db_server::load(const char * lpcszKey, string & str)
{

   if(get_db_str_set() == NULL)
      return false;

   return get_db_str_set()->load(lpcszKey, str);

}



bool db_server::load(const char * lpKey, ::file::output_stream & ostream)
{

   string str;

   if(!load(lpKey, str))
   {

      return false;

   }

   ::file::byte_output_stream os(ostream);

   os.write_from_hex(str);

   return true;

}


bool db_server::save(const char * lpcszKey, const char * lpcsz)
{

   if(get_db_str_set() == NULL)
      return false;

   return get_db_str_set()->save(lpcszKey, lpcsz);

}


bool db_server::save(const char * lpKey, ::file::input_stream & istream)
{

   string str;

   file::byte_input_stream is(istream);

   is.seek_to_begin();

   is.read_to_hex(str);

   if(!save(lpKey, str))
      return false;

   return true;

}


sp(::sqlite::base) db_server::get_database()
{
   return m_pdb;
}

critical_section * db_server::GetImplCriticalSection()
{
   return &m_csImplDatabase;
}

bool db_server::data_pulse_change(::database::client * pclient, ::database::id idSection, ::database::id id, ::database::id idIndex, ::database::update_hint * puh)
{
   return ::database::server::data_pulse_change(
      pclient,
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
   return m_pstrset;
}

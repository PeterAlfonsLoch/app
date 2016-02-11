//#include "framework.h"


command_thread::command_thread(::thread * pthread) :
   object(pthread->get_app())
{

   m_pmutex = new mutex(pthread->get_app());

   m_pthread = pthread;

   m_varTopicQuery.propset().set_app(pthread->get_app());

}

command_thread::~command_thread()
{
}


void command_thread::request_create(sp(::create) pcreate)
{

   command(pcreate);

}


void command_thread::command(::primitive::command * pcommand)
{

   m_pthread->post_thread_message(WM_APP + 1984, 49, pcommand);

}


void command_thread::command(::primitive::e_command ecommand)
{

   command(canew(::primitive::command(get_app(),ecommand)));

}


void command_thread::on_command_message(::signal_details * pobj)
{
   
   SCAST_PTR(::message::base, pbase, pobj);

   sp(::primitive::command) pcommand(pobj->m_lparam);
   
   on_command(pcommand);


}

void command_thread::on_command(::primitive::command * pcommand)
{

   {

      synch_lock sl(m_pmutex);

      m_ptraHistory.add(pcommand);

      m_straHistory.add(pcommand->get_description());

   }

   m_pthread->on_command(pcommand);

}


void command_thread::consolidate(::create * pcreatecontext)
{
   m_spcommandline = pcreatecontext->m_spCommandLine;
   if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
   {
      if(m_varTopicFile != pcreatecontext->m_spCommandLine->m_varFile)
      {
         if(m_varTopicFile.is_empty())
         {
            m_varTopicFile = pcreatecontext->m_spCommandLine->m_varFile;
         }
         else
         {
            m_varTopicFile.stra().add(pcreatecontext->m_spCommandLine->m_varFile.stra());
         }
      }
   }
   m_varTopicQuery.propset().merge(pcreatecontext->m_spCommandLine->m_varQuery.propset());
}

void command_thread::consolidate(::command_thread * pthread)
{

   if(pthread == NULL || pthread == this)
      return;

   if(!pthread->m_varTopicFile.is_empty())
   {
      m_varTopicFile.stra().add_unique(pthread->m_varTopicFile.stra());
   }
   m_varTopicQuery.propset().merge(pthread->m_varTopicQuery.propset());

}

bool command_thread::is_thread()
{
   return true;
}

var & command_thread::property(const char * pszKey)
{
   string strKey(pszKey);
   if(strKey.CompareNoCase("file") == 0)
   {
      if(m_varTopicFile.is_empty())
      {
         if(!m_varTopicQuery["file"].is_empty())
         {
            m_varTopicFile = m_varTopicQuery["file"];
         }
      }
      return m_varTopicFile;
   }
   else
   {
      return m_varTopicQuery[pszKey];
   }
}

bool command_thread::has_property(const char * pszKey)
{
   string strKey(pszKey);
   if(strKey.CompareNoCase("file") == 0)
   {
      if(m_varTopicFile.is_empty())
      {
         if(m_varTopicQuery["file"].is_empty())
         {
            return false;
         }
      }
      return true;
   }
   else
   {
      return m_varTopicQuery.has_property(pszKey);
   }

}





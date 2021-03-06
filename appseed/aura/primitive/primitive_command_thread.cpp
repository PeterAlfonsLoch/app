//#include "framework.h"


command_thread::command_thread(::thread * pthread) :
   object(pthread->get_app())
{

   defer_create_mutex();

   m_pthread = pthread;

   m_varTopicQuery.propset().set_app(pthread->get_app());

}

command_thread::~command_thread()
{
}


void command_thread::request_create(::create * pcreate)
{

   command(pcreate);

}


void command_thread::command(::primitive::command * pcommand)
{

   m_pthread->post_object(message_system, system_message_command, pcommand);

}


void command_thread::command(::primitive::e_command ecommand)
{

   command(canew(::primitive::command(get_app(),ecommand)));

}


//void command_thread::on_command_message(::signal_details * pobj)
//{
//   
//   SCAST_PTR(::message::base, pbase, pobj);
//
//   sp(::primitive::command) pcommand(pobj->m_lparam);
//   
//   on_command(pcommand);
//
//
//}

void command_thread::on_command(::primitive::command * pcommand)
{

   {

      synch_lock sl(m_pmutex);

      m_ptraHistory.add(pcommand);

      m_straHistory.add(pcommand->get_description());

   }

   m_pthread->on_command(pcommand);

}


void command_thread::consolidate(::create * pcreate)
{
   m_spcommandline = pcreate->m_spCommandLine;
   if(!pcreate->m_spCommandLine->m_varFile.is_empty())
   {
      if(m_varTopicFile != pcreate->m_spCommandLine->m_varFile)
      {
         if(m_varTopicFile.is_empty())
         {
            m_varTopicFile = pcreate->m_spCommandLine->m_varFile;
         }
         else
         {
            m_varTopicFile.stra().add(pcreate->m_spCommandLine->m_varFile.stra());
         }
      }
   }
   m_varTopicQuery.propset().merge(pcreate->m_spCommandLine->m_varQuery.propset());
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
   if(strKey.compare_ci("file") == 0)
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
   if(strKey.compare_ci("file") == 0)
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





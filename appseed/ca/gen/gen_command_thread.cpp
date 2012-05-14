#include "framework.h"


namespace gen
{


   command_thread::command_thread(::ca::application * papp) :
      ca(papp)
   {
      m_varTopicQuery.propset().set_app(papp);
   }

   command_thread::~command_thread()
   {
   }


   var command_thread::run()
   {
      single_lock sl(&m_mutex, TRUE);
      ::ca::create_context * pcreatecontext;
      while(m_ptra.get_size() > 0)
      {
         command * pcommand = m_ptra.element_at(0);

         pcreatecontext = NULL;
         try
         {
            pcreatecontext = dynamic_cast < ::ca::create_context * > (pcommand);
         }
         catch(...)
         {
            pcreatecontext = NULL;
         }

         if(pcreatecontext != NULL)
         {
            try
            {
               on_request(pcreatecontext);
            }
            catch(...)
            {
            }
         }

         m_ptraHistory.add(pcommand);
         m_straHistory.add(pcommand->get_description());
         m_ptra.remove_at(0);
         sl.unlock();
         sl.lock(); // going to query while(m_straCommandLine.get_size() <= 0) so need to lock again
      }
      return true;
   }

   void command_thread::request(::ca::create_context * pline)
   {
      single_lock sl(&m_mutex, TRUE);
      m_ptra.add(pline);
   }

   void command_thread::on_request(::ca::create_context * pline)
   {
      try
      {
         ::ex2::application * papp = dynamic_cast < ::ex2::application * > (get_app());
         if(papp != NULL)
         {
            papp->request(pline);
         }
      }
      catch(...)
      {
      }
   }

   void command_thread::consolidate(const ::ca::create_context * pcreatecontext)
   {
      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         if(m_varTopicFile.is_empty())
         {
            m_varTopicFile = pcreatecontext->m_spCommandLine->m_varFile.is_empty();
         }
         else
         {
            m_varTopicFile.stra().add(pcreatecontext->m_spCommandLine->m_varFile.stra());
         }
      }
      m_varTopicQuery.propset().merge(pcreatecontext->m_spCommandLine->m_varQuery.propset());
   }

   void command_thread::consolidate(gen::command_thread * pthread)
   {

      if(pthread == NULL || pthread == this)
         return;

      if(!pthread->m_varTopicFile.is_empty())
      {
         m_varTopicFile.stra().add(pthread->m_varTopicFile.stra());
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

} // namespace command_thread


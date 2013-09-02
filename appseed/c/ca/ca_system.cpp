#include "framework.h"


system::system(sp(::application) papp) //:
   //m_mutexDelete(this),
   //m_http(this),
   //m_net(this),
   //m_mutex(this),
#ifndef METROWIN
   //m_processsection(this),
#endif
   //m_visual(this)
{


#ifdef METROWIN
   m_window                                  = nullptr;
#endif
#ifdef WINDOWS
   //      m_pmutexDc                                = NULL;
   //    m_pdevicecontext                          = NULL;
#endif

   //m_psystem                                 = this;
   m_pcasystem                                 = this;
   set_app(this);


   if(papp == NULL)
   {

      oprop("parent_system") = (sp(element)) NULL;

   }
   else
   {

      oprop("parent_system") = papp->m_pcasystem;

   }


   //::ca::application::m_file.set_app(this);
   //::ca::application::m_dir.set_app(this);

   //      m_bDoNotExitIfNoApplications              = true;

   string strId;
   //strId = m_strAppName;
   //strId += ::str::has_char(m_strAppId, ".");
   //strId += ::str::has_char(m_strBaseSupportId, ".");


   strId = "ca2log";

   /*
   xxdebug_box("Going to start Log", "Just before initialize log", 0);

   // log starts here
   if(!initialize_log(strId))
   {
   xxdebug_box("Could not initialize log", "Failed to initialize log", 0);
   throw "failed to initialize log";
   }

   */
   /*
   if(psystemParent == NULL)
   {

   m_peengine                                = new ::exception::engine(this);

   }
   else
   {

   m_peengine                                = psystemParent->m_peengine;

   }
   */


   if(::get_heap_mutex() == NULL)
   {

      ::set_heap_mutex(new mutex(this));

   }

   use_base_ca2_allocator();


   m_pfactory = new class factory(this);
   m_pfactory->set_app(this);

   m_pfactory->cloneable_large < ::ca2::create_context > ();
   m_pfactory->cloneable_large < ::ca2::application_bias > ();
   m_pfactory->cloneable_large < ::ca2::command_line > ();
   m_pfactory->cloneable_large < ::manual_reset_event > ();
   m_pfactory->cloneable_large < ::mutex > ();
   m_pfactory->cloneable_large < ::event > ();

}

factory & system::factory()
{
   return *m_pfactory;
}


::exception::engine & system::eengine()
{

   static ::exception::engine s_eengine(NULL);

   return s_eengine;

}


bool system::initialize_instance()
{

   m_pfactory->enable_simple_factory_request();

   return true;

}


UINT system::os_post_to_all_threads(UINT uiMessage, WPARAM wparam, lparam lparam)
{

   throw interface_only_exception(this);


}

sp(element) system::clone()
{
   // by the time, it is not possible to clone a system
   return NULL;
}

sp(element) system::clone(sp(element) pobj)
{
   return System.factory().base_clone(pobj);
}


void system::discard_to_factory(sp(element) pca)
{

   if(m_pfactory == NULL)
      return;

   m_pfactory->discard(pca);

}







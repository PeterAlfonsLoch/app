//#include "framework.h"
//#include "android.h"
//#include <dlfcn.h>
//#include <link.h>
//#include <pthread.h>


//namespace android
namespace aura
{



   //application::application(::aura::application * papp) :
   //   ::object(papp)
   //{
   //   m_pthreadimpl.alloc(allocer());
   //   m_pthreadimpl->m_pthread = this;


   //   shell::theLinuxShell.Initialize();
   //}

   //application::~application()
   //{

   //}


   //void application::_001OnFileNew()
   //{
   //   //::ca2::application_base::m_p->_001OnFileNew(NULL);
   //}

   //::aura::document *  application::_001OpenDocumentFile(var varFile)
   //{
   //  // return ::ca2::application_base::m_p->_001OpenDocumentFile(varFile);
   //}

   void application::_001EnableShellOpen()
   {
// xxx       ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once

// xxx       m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
// xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
   }

   //bool application::_001OnDDECommand(const char * lpcsz)
   //{
   //   UNREFERENCED_PARAMETER(lpcsz);
   //   return FALSE;
   //}

   //HINSTANCE application::GetHinstance()
   //{
   //   return NULL;
   //}

   string application::get_version()
   {

      return "1.0.0";

   }



   bool application::impl_process_initialize()
   {

      return true;

   }


   bool application::impl_initialize1()
   {

      return true;

   }


   bool application::impl_initialize2()
   {

      return true;

   }


   bool application::impl_initialize3()
   {

      return true;

   }

   int32_t application::impl_exit_instance()
   {

      set_os_data(NULL);

      return m_iReturnCode;

   }


   void application::ShowWaitCursor(bool bShow)
   {


   }





   void application::get_time(struct timeval *p)
   {

      gettimeofday(p, NULL);

   }

   void application::set_env_var(const string & var,const string & value)
   {

      setenv(var, value, 1);

   }

   IDTHREAD application::get_thread_id()
   {
      return ::pthread_self();
   }



   bool application::set_main_init_data(::aura::main_init_data * pdata)
   {

      m_pinitmaindata =  pdata;

      string strCmdLine          = pdata->m_vssCommandLine;

      SetCurrentHandles();

      __init_thread();

      return true;

   }

   string application::draw2d_get_default_library_name()
   {

      return "draw2d_cairo";

   }


   string application::multimedia_audio_get_default_library_name()
   {

      return "audio_alsa";

   }


   string application::multimedia_audio_mixer_get_default_library_name()
   {

      return "audio_mixer_alsa";

   }


   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "music_midi_alsa";

   }


} // namespace android





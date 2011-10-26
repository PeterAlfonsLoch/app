#include "StdAfx.h"
#include "application.h"
#include "document.h"
#include "frame.h"
#include "view.h"
#include "html/html_document.h"
#include "html/html_view.h"


namespace i2com
{

   void KickNetNodeThread();

   application::application(void) //:
      //m_msnsocket(this)//,
      //m_status(this)
   {
   }

   application::~application(void)
   {
   }


   void application::construct()
   {
      m_strLicense         = "i2com";
      m_strLicense         = "";
      m_strInstallToken    = "i2com";
      m_strAppName         = "i2com";
      m_eexclusiveinstance = ::radix::ExclusiveInstanceNone;
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < document >();
      System.factory().creatable_small < view >();
      System.factory().creatable_small < frame >();
      System.factory().creatable_small < child_frame >();
      System.factory().creatable_small < i2com::contact_view >();
      
      System.factory().creatable_small < i2com::im_edit_view >();
      System.factory().creatable_small < i2com::im_stream_view >();
      System.factory().creatable_small < i2com::im_view >();

      System.factory().creatable_small < i2com::comm_form_view >();
      System.factory().creatable_small < i2com::comm_view >();

      System.factory().creatable_small < rtprx::pane_view >();
      System.factory().creatable_small < rtprx::document >();
      System.factory().creatable_small < rtprx::frame >();
      System.factory().creatable_small < rtprx::view >();

      if(!cube2::application::initialize_instance())
         return false;

      if(!midi_central_container::initialize_central_container(this))
      {
         return false;
      }


      //AfxSocketInit();

      //window_frame::FrameSchema::ButtonIdSpace idspace;
   /* xxx   SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);*/

      m_ptemplateEdge = new ::userbase::single_document_template(
         this, 
         "i2com/frame", 
         ::ca::get_type_info < document > (), 
         ::ca::get_type_info < frame > (), 
         ::ca::get_type_info < view > ());

      m_ptemplateHtml = new ::userbase::multiple_document_template(
         this, 
         "i2com/frame", 
         ::ca::get_type_info < html_document > (), 
         ::ca::get_type_info < simple_child_frame > (), 
         ::ca::get_type_info < html_view > ());

      m_ptemplateContact = new ::userbase::single_document_template(
         this, 
         "i2com/frame", 
         ::ca::get_type_info < document > (),
         ::ca::get_type_info < child_frame > (), 
         ::ca::get_type_info < contact_view > ());

      m_ptemplateCommunication = new ::userbase::multiple_document_template(
         this, 
         "i2com/frame", 
         ::ca::get_type_info < document > (), 
         ::ca::get_type_info < child_frame > (), 
         ::ca::get_type_info < comm_view > ());

      m_ptemplateRtpRx = new ::userbase::multiple_document_template(
         this,
         "i2com/frame",
         ::ca::get_type_info < rtprx::document > (), 
         ::ca::get_type_info < rtprx::frame > (), 
         ::ca::get_type_info < rtprx::view > ());


      SetRegistryKey("ca2core");


      WriteProfileString("configuration", "init", "first time ok");

      return true;
   }



   BOOL application::exit_instance()
   {
      return TRUE;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
      m_ptemplateEdge->open_document_file(pcreatecontext);
   }

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   void application::pre_translate_message(gen::signal_object * pobj)
   {
      ::status::application::pre_translate_message(pobj);
   }

   // return negative if fail
   int application::get_free_rtprx_port()
   {
      return 19847;
   }

   int application::open_rtprx(const char * pszHost, int iPort)
   {
      string strHost(pszHost);
      if(strHost.is_empty())
         strHost = "0.0.0.0";
      if(iPort < 0)
      {
         iPort = get_free_rtprx_port();
      }
      // listen/receives at the specified port
      string strUrl;
      strUrl.Format("rtp://%s:%d", strHost, iPort);
      if(!m_ptemplateRtpRx->open_document_file(strUrl, false))
         return -1;
      return iPort;
   }

} // namespace i2com

CLASS_DECL_CA2_TESSERACT ::ca::application * i2com_get_new_app()
{
   tesseract::application * papp = new tesseract::application("i2com");
   return dynamic_cast < ::ca::application * > (papp);
}

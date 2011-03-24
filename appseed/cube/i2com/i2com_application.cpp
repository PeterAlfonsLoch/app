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

      if(!ca84::application::initialize_instance())
         return false;

      //AfxSocketInit();

      //window_frame::FrameSchema::ButtonIdSpace idspace;
   /* xxx   SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);*/

      m_ptemplateEdge = new ::userbase::multiple_document_template(
         this, 
         "i2com/frame", 
         &typeid(document), 
         &typeid(frame), 
         &typeid(view));

      m_ptemplateHtml = new ::userbase::multiple_document_template(
         this, 
         "i2com/frame", 
         &typeid(html_document), 
         &typeid(simple_child_frame), 
         &typeid(html_view));

      m_ptemplateContact = new ::userbase::single_document_template(
         this, 
         "i2com/frame", 
         &typeid(document),
         &typeid(child_frame), 
         &typeid(contact_view));

      m_ptemplateCommunication = new ::userbase::multiple_document_template(
         this, 
         "i2com/frame", 
         &typeid(document), 
         &typeid(child_frame), 
         &typeid(comm_view));

      m_ptemplateRtpRx = new ::userbase::multiple_document_template(
         this,
         "i2com/frame",
         &typeid(rtprx::frame), 
         &typeid(rtprx::document), 
         &typeid(rtprx::view));


      SetRegistryKey("ca2core");


      WriteProfileString("configuration", "init", "first time ok");

      return true;
   }



   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
      m_ptemplateEdge->open_document_file(NULL, TRUE, m_puiInitialPlaceHolderContainer);
      return true;
   }



   void application::get_Votagus_folder(string &strVotagusFolder)
   {
      strVotagusFolder = get_module_folder();
      System.file().path().eat_end_level(strVotagusFolder, 7, "\\");
   }



   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   void application::pre_translate_message(gen::signal_object * pobj)
   {
      ::status::application::pre_translate_message(pobj);
   }

   ::ca::application * application::get_app() const
   {
      return m_papp;
   }


   // return negative if fail
   int application::get_free_rtprx_port()
   {
      return 19847;
   }

   int application::open_rtprx()
   {
      int iPort = get_free_rtprx_port();
      if(iPort < 0)
         return iPort;
      // listen/receives at the specified port
      string strUrl;
      strUrl.Format("rtp://0.0.0.0:%d", iPort);
      if(!m_ptemplateRtpRx->open_document_file(strUrl, false))
         return -1;
      return iPort;
   }

} // namespace i2com

CLASS_DECL_CA2_CUBE ::ca::application * i2com_get_new_app()
{
   cube::application * papp = new cube::application("i2com");
   return dynamic_cast < ::ca::application * > (papp);
}

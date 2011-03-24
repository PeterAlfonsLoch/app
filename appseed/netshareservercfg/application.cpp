#include "StdAfx.h"

namespace netshareservercfg
{

   application::application(void)
   {
      m_strAppName = "netshareservercfg";
      m_strLicense = "";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      if(!ca84::application::initialize_instance())
         return false;

	   bergedge server(this);
      server.set_configuration();

      return FALSE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

} // namespace netshareservercfg

CLASS_DECL_CA2_NETSHARESERVERCFG ::ca::application * get_new_app()
{
   return new netshareservercfg::application;
}

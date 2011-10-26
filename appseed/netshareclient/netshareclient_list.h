#pragma once

namespace netshareclient
{

   class document;

   class CLASS_DECL_CA2_NETSHARECLIENT list :
      virtual public ::userbase::view,
      virtual public list_interface
   {
   public:


      simple_list_header_control    m_headerctrl;
      simple_scroll_bar             m_scrollbarVert;
      simple_scroll_bar             m_scrollbarHorz;




      list(::ca::application * papp);
      virtual ~list();

      void open_profile(const char * pszFolder);

      document * get_document();

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)

      void _001OnClick(UINT uiFlags, point point);

      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);
      

   };

} // namespace netshareclient
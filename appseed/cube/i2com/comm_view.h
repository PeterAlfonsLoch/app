#pragma once

namespace i2com
{

   class im_view;
   class comm_form_view;

   class CLASS_DECL_CA2_CUBE comm_view :
      virtual public ::userbase::split_view
   {
   public:
      comm_view(::ca::application * papp);
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate)

      void CreateViews();

      string            m_strUrl;
      string            m_strRecipient;
      im_view *         m_pimview;
      comm_form_view *  m_pformview;

      virtual void i2com_open(const char * pszUrl);
   };

} // namespace i2com
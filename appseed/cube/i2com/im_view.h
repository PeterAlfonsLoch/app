#pragma once

namespace i2com
{

   class im_edit_view;
   class im_stream_view;
   class comm_view;

   class CLASS_DECL_CA2_CUBE im_view :
      virtual public ::userbase::split_view
   {
   public:
      im_view(::ca::application * papp);
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate)

      void CreateViews();

      string            m_strUrl;
      string            m_strRecipient;
      im_edit_view *    m_peditview;
      im_stream_view *  m_pstreamview;
      comm_view  *      m_pcommview;

      virtual void i2com_open(const char * pszUrl);
   };

} // namespace i2com
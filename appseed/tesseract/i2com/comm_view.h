#pragma once


namespace i2com
{


   class im_view;
   class comm_form_view;


   class CLASS_DECL_CA2_TESSERACT comm_view :
      virtual public ::userbase::split_view
   {
   public:
      
      
      string                  m_strUrl;
      string                  m_strRecipient;
      im_view *               m_pimview;
      comm_form_view *        m_pformview;
      bool                    m_bSentInvitation;


      comm_view(::ca::application * papp);
      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate)


      void OnBeforeNavigate2(var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);

      void CreateViews();


      virtual void i2com_open(const char * pszUrl);


   };


} // namespace i2com



#pragma once

namespace userex
{
   namespace autocomplete
   {
      class handler;

      class CLASS_DECL_CA2_CUBE interaction :
         virtual public ::user::interaction
      {
      public:

         handler *         m_phandler;

         interaction(::ca::application * papp);

         virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

         virtual void autocomplete_set_text(const char * pszText);

         DECL_GEN_SIGNAL(_001OnCreate);
      };

      class CLASS_DECL_CA2_CUBE handler :
         virtual public ::user::form_callback,
         virtual public ::user::create_view
      {
      public:

         form_document *                           m_pdocument;
         form_view *                               m_pformview;
         interaction *                             m_pinteraction;
         bool                                      m_bUpdatingForm;


         handler(interaction * pinteraction);
         virtual ~handler();

         void ensure_main_document();
         void display_main_frame();
         void pageMessage(const char * pszMatter, gen::property_set & set);

         virtual void set_text(const char * pszText);
         virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

         virtual void OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);

      };

   } // namespace autocomplete

} // namespace userex


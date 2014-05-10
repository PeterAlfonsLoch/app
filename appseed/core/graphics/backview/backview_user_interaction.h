#pragma once


namespace backview
{


   namespace user
   {


      class CLASS_DECL_CORE interaction :
         virtual public Interface,
         virtual public ::user::impact,
         virtual public ::database::user::interaction
      {
      public:


         int32_t            m_iBackgroundUpdateMillis;
         color          m_colorBackground;


         interaction(sp(::base::application) papp);
         virtual ~interaction();

         virtual void BackViewGetClientRect(LPRECT lprect);
         virtual void BackViewClientToScreen(LPRECT lprect);

         using ::backview::Interface::BackViewPostMessage;
         virtual void BackViewPostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam);
         virtual void BackViewUpdateScreen();
         virtual void BackViewGetData(InterfaceData & data);
         virtual void BackViewSetData(InterfaceData & data);
         virtual void BackViewUpdateScreen(LPCRECT lpcrect, UINT uiRedraw);
         virtual void BackViewUpdateScreen(rect_array & recta, UINT uiRedraw);

         virtual int32_t  BackViewGetBackgroundUpdateMillis();

         virtual string BackViewGetNextBackgroundImagePath();
         virtual void BackViewSetCurrentBackgroundImagePath(const char * psz);

         COLORREF GetBackgroundColor();

         virtual void initialize_user_interaction();

         virtual void install_message_handling(::message::dispatch * pdispatch);

      };


   } // namespace user


} // namespace backview










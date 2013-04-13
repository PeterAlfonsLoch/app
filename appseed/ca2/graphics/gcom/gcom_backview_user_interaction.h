#pragma once

namespace gcom
{
   namespace backview
   {
      class InterfaceData;
      class Interface;

      namespace user
      {

         class CLASS_DECL_ca2 interaction :
            virtual public Interface,
            virtual public ::user::view
         {
         public:

            int32_t            m_iBackgroundUpdateMillis;
            color          m_colorBackground;

            interaction(sp(::ca::application) papp);
            virtual ~interaction();

            virtual void BackViewGetClientRect(LPRECT lprect);
            virtual void BackViewClientToScreen(LPRECT lprect);
#if !core_level_1
            using ::gcom::backview::Interface::BackViewPostMessage;
#endif
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

         };

      } // namespace user
   
   } // namespace backview

} //namespace gcom

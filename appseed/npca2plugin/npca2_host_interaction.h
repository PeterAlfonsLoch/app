#pragma once

class nsPluginInstance;


namespace npca2
{

   enum e_check;
   class plugin;
   
   class host_interaction :
      public ::user::interaction
   {
   public:


      enum
      {
         message_check = WM_USER + 10,
      };



      bergedge::frame *       m_pframe;
      plugin *                m_pplugin;


      

      host_interaction(::ca::application * papp);
      virtual ~host_interaction();

      void _001InstallMessageHandling(::user::win::message::dispatch * pmessage);

      virtual void _000OnDraw(::ca::graphics * pgraphics);

      virtual bool defer_check(e_check echeck);
      virtual void layout();

      virtual void GetWindowRect(__rect64 * lprect);

      virtual BOOL IsWindowVisible();

      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnCheck)
      DECL_GEN_SIGNAL(_001OnCreate)

      virtual BOOL RedrawWindow(LPCRECT lpRectUpdate, ::ca::rgn* prgnUpdate, UINT flags);

      ::user::interaction * get_os_focus_uie();

   };

} // namespace npca2



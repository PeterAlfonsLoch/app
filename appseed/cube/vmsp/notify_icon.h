#pragma once

namespace vmsp
{

   class notify_icon :
      virtual public ::radix::object,
      virtual public ::userbase::notify_icon_listener
   {
   public:
      
      
      userbase::notify_icon *    m_pnotifyicon;
      base_array < ::ca::window *, ::ca::window *> m_wndptraHidden;   

      
      notify_icon(::ca::application * papp);
      virtual ~notify_icon();


      void Start();
      void AddHiddenWindow(::ca::window * pwnd);

      virtual void OnNotifyIconContextMenu(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDblClk(UINT uiNotifyIcon);

      static notify_icon * AppGetNotifyIcon(::ca::application * papp);
   };

} // namespace vmsp

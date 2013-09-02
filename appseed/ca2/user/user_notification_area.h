#pragma once



namespace user
{

#ifdef WINDOWSEX

   struct CLASS_DECL_ca2 TRAYDATA
   {
      HWND    m_oswindow;
      UINT        uID;
      UINT        uCallbackMessage;
      uint32_t       Reserved[2];
      HICON       hIcon;
   };


   struct CLASS_DECL_ca2 TrayItemInfo :
      virtual public element
   {
      oswindow    m_oswindow;
      UINT        uID;
      UINT        uCallbackMessage;
      string      sTip;
      string      sProcessPath;
      bool        bVisible;
   };

#endif

   CLASS_DECL_ca2 char GetDriveLetter(const char * lpDevicePath);
   CLASS_DECL_ca2 oswindow FindTrayToolbarWindow();
   CLASS_DECL_ca2 string GetFilenameFromPid(uint32_t pid);


   class CLASS_DECL_ca2 notification_area :
      virtual public object
   {
   public:


      oswindow             m_oswindowTray;
      sp(image_list)         m_pil16;
#ifdef WINDOWSEX
      spa(TrayItemInfo)    m_infoa;
#endif
      HFONT                m_hfontHidden;
      HFONT                m_hfontRegular;


      notification_area();
      virtual ~notification_area();

      virtual void Initialize(sp(::application) papp);

      void ListTrayIcons(int32_t defindex = 0);
      void EditCopy(int32_t iItem);
      void DoubleClick(int32_t iItem);
      void RightClick(int32_t iItem);
      void LeftClick(int32_t iItem);
      void MoveLeft(int32_t iItem);
      void MoveRight(int32_t iItem);
      void Refresh();
      void PostMessageToTrayIcon(int32_t iItem, LPARAM lParam);


   };


} // namespace user





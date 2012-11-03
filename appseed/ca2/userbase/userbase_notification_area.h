#pragma once



namespace userbase
{


   struct CLASS_DECL_ca2 TRAYDATA
   {
      oswindow_ hwnd;            
      UINT uID;            
      UINT uCallbackMessage;   
      DWORD Reserved[2];      
      HICON hIcon;            
   };

   struct CLASS_DECL_ca2 TrayItemInfo
   {
      oswindow_ hwnd;            
      UINT uID;            
      UINT uCallbackMessage;
      string sTip;
      string sProcessPath;
      bool bVisible;
   };

   CLASS_DECL_ca2 char GetDriveLetter(const char * lpDevicePath);
   CLASS_DECL_ca2 oswindow_ FindTrayToolbarWindow();
   CLASS_DECL_ca2 string GetFilenameFromPid(DWORD pid);

   class CLASS_DECL_ca2 notification_area :
      virtual public ::radix::object
   {
   public:
      notification_area();

   // Attributes
   public:
      oswindow_ m_hwndTray;   
      image_list * m_pil16;
      array_ptr_alloc < TrayItemInfo, TrayItemInfo & > m_infoa;
      HFONT m_hfontHidden;
      HFONT m_hfontRegular;

      public:
      virtual void Initialize(::ca::application * papp);

   public:
      virtual ~notification_area();
   public:
      void ListTrayIcons(int defindex = 0);
      void EditCopy(int iItem);
      void DoubleClick(int iItem);
      void RightClick(int iItem);
      void LeftClick(int iItem);
      void MoveLeft(int iItem);
      void MoveRight(int iItem);
      void Refresh();
      void PostMessageToTrayIcon(int iItem, LPARAM lParam);
   };


} // namespace userbase
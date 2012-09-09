#pragma once


namespace ca
{


   class window;


} // namespace ca


namespace user
{


   class CLASS_DECL_ca HWNDArray :
      public comparable_array < void *, void * >
   {
   public:
      void SortByZOrder();
      void SortSiblingsByZOrder();
      void top_windows_by_z_order();
   };


   class CLASS_DECL_ca LPWndArray :
      virtual public pha(::user::interaction)
   {
   public:
//      using pha(::user::interaction)::find_first;
      ::user::interaction * find_first(::ca::type_info info);
      ::user::interaction * find_first(void * hwnd);
      void get_wnda(user::HWNDArray & hwnda);
      void send_message(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0);
      void send_message_to_descendants(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0, bool bRecursive = true);
   };


   class CLASS_DECL_ca HwndTree
   {
   public:

      class CLASS_DECL_ca Array :
         public array_ptr_alloc < HwndTree, const HwndTree &>
      {
      public:
         bool remove(void * hwnd);
         int_ptr find(void * hwnd);
         void EnumDescendants();
         Array & operator = (HWNDArray & hwnda);

      };

      HwndTree();
      HwndTree(const HwndTree & tree);

      void *   m_hwnd;
      DWORD m_dwUser;
      void * m_pvoidUser;
      Array m_hwndtreea;
      public:
         void EnumDescendants();
      static int CompareHwnd(HwndTree & tree1,  HwndTree & tree2);
      public:
      HwndTree & operator = (const HwndTree & tree);
   };


   class CLASS_DECL_ca WndUtil
   {
   public:
      static void ContraintPosToParent(void * hwnd);
      //static void EnumChildren(::ca::window * pwnd, LPWndArray & wndpa);
      static void EnumChildren(void * hwnd, HWNDArray & hwnda);
      /*static void ExcludeChild(LPWndArray & wndpa);*/
      /*static void SortByZOrder(LPWndArray & wndpa);*/
      static void SortByZOrder(HWNDArray & hwnda);
      static HRGN GetAClipRgn(void * hwnd, POINT ptOffset, bool bExludeChilren);
      static void ExcludeChildren(void * hwnd, HRGN hrgn, POINT ptOffset);
      WndUtil();
      virtual ~WndUtil();
      /*static void SendMessageToDescendants(void * hWnd, UINT message,
         WPARAM wParam, LPARAM lParam, bool bDeep, bool bOnlyPerm);*/
      static void SendMessageToDescendants(void * hWnd, UINT message,
         WPARAM wParam, LPARAM lParam, bool bDeep);
      static bool IsAscendant(void * hwndAscendant, void * hwndDescendant);

      static int GetZOrder(void * hwnd);
      static void GetZOrder(void * hwnd, int_array & ia);

//      static HRGN GetAClipRgn(void * hwnd, POINT ptOffset, bool bExludeChilren);
//      static void ExcludeChildren(void * hwnd, HRGN hrgn, POINT ptOffset);

      //static void SortByZOrder(comparable_array < ::ca::window *, ::ca::window * > & wndpa);
      //static void SortByZOrder(comparable_array < void *, void * > & hwnda);
      //static void EnumChildren(void * hwnd, comparable_array < void *, void * > & hwnda);

   };




}


#pragma once

class ::ca::window;

namespace user
{
   class CLASS_DECL_ca HWNDArray : 
      public comparable_array < HWND, HWND >
   {
   public:
      void SortByZOrder();
      void SortSiblingsByZOrder();
      void top_windows_by_z_order();
   };

   class CLASS_DECL_ca LPWndArray : 
      virtual public comparable_array < ::user::interaction *, ::user::interaction * >
   {
   public:
      using comparable_array < ::user::interaction *, ::user::interaction * >::find_first;
      ::user::interaction * find_first(::ca::type_info info);
      ::user::interaction * find_first(HWND hwnd);
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
         bool remove(HWND hwnd);
			INT_PTR find(HWND hwnd);
			void EnumDescendants();
			Array & operator = (HWNDArray & hwnda);

		};

		HwndTree();
		HwndTree(const HwndTree & tree);

		HWND	m_hwnd;
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
	   static void ContraintPosToParent(HWND hwnd);
	   //static void EnumChildren(::ca::window * pwnd, LPWndArray & wndpa);
	   static void EnumChildren(HWND hwnd, HWNDArray & hwnda);
	   /*static void ExcludeChild(LPWndArray & wndpa);*/
	   /*static void SortByZOrder(LPWndArray & wndpa);*/
	   static void SortByZOrder(HWNDArray & hwnda);
	   static HRGN GetAClipRgn(HWND hwnd, POINT ptOffset, bool bExludeChilren);
	   static void ExcludeChildren(HWND hwnd, HRGN hrgn, POINT ptOffset);
	   WndUtil();
	   virtual ~WndUtil();
	   /*static void SendMessageToDescendants(HWND hWnd, UINT message,
		   WPARAM wParam, LPARAM lParam, BOOL bDeep, BOOL bOnlyPerm);*/
	   static void SendMessageToDescendants(HWND hWnd, UINT message,
		   WPARAM wParam, LPARAM lParam, BOOL bDeep);
	   static bool IsAscendant(HWND hwndAscendant, HWND hwndDescendant);

      static int GetZOrder(HWND hwnd);
      static void GetZOrder(HWND hwnd, int_array & ia);

//	   static HRGN GetAClipRgn(HWND hwnd, POINT ptOffset, bool bExludeChilren);
//	   static void ExcludeChildren(HWND hwnd, HRGN hrgn, POINT ptOffset);

      //static void SortByZOrder(comparable_array < ::ca::window *, ::ca::window * > & wndpa);
	   //static void SortByZOrder(comparable_array < HWND, HWND > & hwnda);
	   //static void EnumChildren(HWND hwnd, comparable_array < HWND, HWND > & hwnda);
   	
   };
   



}


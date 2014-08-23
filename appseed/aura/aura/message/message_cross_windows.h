#ifdef METROWIN

#if defined(__cplusplus_winrt)
#include <agile.h>
#endif

typedef struct tagCREATESTRUCTA {
   LPVOID      lpCreateParams;
   HINSTANCE   hInstance;
   HMENU       hMenu;
   oswindow        oswindowParent;
   int32_t         cy;
   int32_t         cx;
   int32_t         y;
   int32_t         x;
   LONG        style;
   LPCSTR      lpszName;
   LPCSTR      lpszClass;
   uint32_t       dwExStyle;
} CREATESTRUCTA,*LPCREATESTRUCTA;
typedef struct tagCREATESTRUCTW {
   LPVOID      lpCreateParams;
   HINSTANCE   hInstance;
   HMENU       hMenu;
   oswindow    hwndParent;
   int32_t         cy;
   int32_t         cx;
   int32_t         y;
   int32_t         x;
   LONG        style;
   LPCWSTR     lpszName;
   LPCWSTR     lpszClass;
   uint32_t       dwExStyle;
} CREATESTRUCTW,*LPCREATESTRUCTW;
#ifdef UNICODE
typedef CREATESTRUCTW ::user::create_struct;
typedef LPCREATESTRUCTW ::user::create_struct *;
#else
typedef CREATESTRUCTA ::user::create_struct;
typedef LPCREATESTRUCTA ::user::create_struct *;
#endif // UNICODE

#endif




#if defined(LINUX) || defined(APPLEOS)
#define WM_APP 0x8000
#define WM_USER                         0x0400
#endif


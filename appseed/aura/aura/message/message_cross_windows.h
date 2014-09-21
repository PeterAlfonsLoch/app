#ifdef METROWIN


typedef struct tagCREATESTRUCTA
{
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

typedef struct tagCREATESTRUCTW
{
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
typedef CREATESTRUCTW CREATESTRUCT;
typedef LPCREATESTRUCTW LPCREATESTRUCT ;
#else
typedef CREATESTRUCTA CREATESTRUCT;
typedef LPCREATESTRUCTA LPCREATESTRUCT ;
#endif // UNICODE

#endif




#if defined(LINUX) || defined(APPLEOS)
#define WM_APP 0x8000
#define WM_USER                         0x0400
#endif


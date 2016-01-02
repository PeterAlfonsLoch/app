#include "spa.h"
#include "compress/bsdiff/bsdiff.h"
#include <WinSvc.h>

#define ID_CONTROL_BOX_CLOSE 31000
#define ID_CONTROL_BOX_MINIMIZE 31001


bool g_bForceUpdatedBuild = false;

int g_cx;
int g_cy;

int run_file(const char * pszFile, int nCmdShow);

bool g_bInstalling = false;
int g_iHealingSurface = 0;
vsstring g_strHost;
DWORD g_dwInstallStartTime;
vsstring g_strBuild;
vsstring g_strBuildResource;
HINSTANCE g_hinstance;
bool g_bShowPercentage;
extern MSG g_msg;
#ifdef WIN32
//void config_session_proxy(HINTERNET hSession, WCHAR * pwzUrl);


HBRUSH g_hbrushBk = NULL;
HBITMAP g_hbmAlpha;
HDC g_hdcAlpha;

void DragMainWindow();

BOOL AfxInternalPumpMessage()
{
	if (!::GetMessage(&g_msg, NULL, NULL, NULL))
	{
#ifdef _DEBUG
/*		TRACE(traceAppMsg, 1, "CWinThread::PumpMessage - Received WM_QUIT.\n");
			pState->m_nDisablePumpCount++; // application must die*/
#endif
		// Note: prevents calling message loop things in 'ExitInstance'
		// will never be decremented
		return FALSE;
	}

  // process this message

///*	if (!AfxPreTranslateMessage(&(pState->m_msgCur)))
//	{
		::TranslateMessage(&g_msg);
		::DispatchMessage(&g_msg);
//	}*/
  return TRUE;
}


#endif


machine_event g_machineevent;

bool machine_unsignalize_close_application();
bool machine_check_close_application(bool bDefault);
bool g_NeedRestartBecauseOfReservedFile;
bool g_NeedRestartFatalError;
bool g_bLoginStartup;
bool g_bMsDownload = false;
vsstring g_strTitle;
DWORD g_dwCurFileLen;
bool m_reboot();
bool ignit_phase2();
int run_uninstall(const char * lpCmdLine, int nCmdShow);
int run_uninstall_run(const char * lpCmdLine, int nCmdShow);
int run_install(const char * lpCmdLine, int nCmdShow);
int run_file(const char * lpFile, int nCmdShow);
bool spa_exec(const char * psz);
vsstring load_string(const char * pszId, const char * pszDefault);
vsstring str_replace(const char * psz, const char * pszFind, const char * pszReplace);
bool is_there_application_opened();
bool is_application_opened(const char * psz);
void machine_signalize_close_application();
vsstring read_resource_as_string(
   HINSTANCE hinst,
   UINT nID, 
   LPCTSTR lpcszType);



wchar_t * wfy(const char * pszUtf8)
{
   int iSize = MultiByteToWideChar(CP_UTF8, 0, pszUtf8, strlen_dup(pszUtf8), NULL, NULL);
   wchar_t * push = new wchar_t[iSize + 1];
   MultiByteToWideChar(CP_UTF8, 0, pszUtf8, strlen_dup(pszUtf8), push, iSize + 1);
   push[iSize] = L'\0';
   return push;
}

void wfree(wchar_t * push)
{
   delete [] push;
}



#define MAX_LOADSTRING 100

stra_dup g_strSpa;
stra_dup g_straHost;





bool Get(const vsstring& url_in, vsstring & doc);
bool Get(const vsstring& url_in, bool bExist, int iLength, const char * pszMd5, int iGzLen);
bool DownloadFile(const vsstring& url_in, bool bExist, int iLength, const char * pszMd5, int iGzLen);
int GetFileList(stra_dup & stra, LPCTSTR lpcszUrl, simple_string_to_intptr & mapLen, simple_string_to_intptr & mapGzLen, simple_string_to_string & mapMd5);
int GetLocalFileList(stra_dup & stra, LPCTSTR lpcszUrl);
int DownloadFileList(stra_dup & stra, simple_string_to_intptr & mapLen, simple_string_to_string & mapMd5, simple_string_to_intptr & mapGzLen);
void ParseIndexFile(const char * psz, simple_string_to_intptr & mapLen, simple_string_to_string & mapMd5, simple_string_to_intptr & mapGzLen);
int UncompressFileList(stra_dup & stra, simple_string_to_string & strmapMd5);
void ParseSpaIndex(XNode & node);
void CommandLang(int iLang);
//vsstring Login();



/*class SpaHttpGet : public HttpGetSocket
{
public:

	SpaHttpGet(ISocketHandler& handler,const vsstring& url,const vsstring& to_file = "")
   : HttpGetSocket(handler, url, to_file)
   {
   };
   SpaHttpGet(ISocketHandler& handler,const vsstring& host,port_t port,const vsstring& url,const vsstring& to_file = "")
      : HttpGetSocket(handler, host, port, url, to_file)
   {

   };

   
   virtual void OnDataArrived(const char *, size_t len);

	/** Implement this to return your own User-agent string. */
	/*virtual vsstring MyUseragent()
   {
      return "ccvotagus_ca2_fontopus";
   }*/

//};*/

/*class SpaHttpPost : public HttpPostSocket
{
public:

	SpaHttpPost(ISocketHandler& handler,const vsstring& url)
   : HttpPostSocket(handler, url)
   {
   };

   

	/** Implement this to return your own User-agent string. */
	/*virtual vsstring MyUseragent()
   {
      return "ccvotagus_ca2_fontopus";
   }

};*/


#define ID_START 100
#define ID_FINISH 101
#define ID_STEP_BACKWARD 102

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void CommandRegister();
//void CommandLogin();
void CommandFinish();
DWORD WINAPI ThreadProcCommandStart(LPVOID lpParam);
DWORD WINAPI ThreadProcAppListInitialize(LPVOID lpParam);

double g_dAnime = 0.0;
double g_dPi = asin(1.0) * 4;

bool g_bShow = true;

bool g_bDrag = false;
POINT g_ptDragStart;
RECT g_rectWindowDragStart;
int g_iScreen;
int g_iProgressMode;
int g_iTotalGzLen;
int g_iGzLen;
int g_iStyle;
vsstring g_strLogin;
vsstring g_strSessid;
vsstring g_strStart;
vsstring g_strInstallFilter;
vsstring g_strLocale;
//vsstring g_strStatus1;
//vsstring g_strStatus2;
vsstring g_strLoginFailed;
HWND g_hwnd = NULL;

vsstring g_strFile;

double g_dProgress = -1.0;
double g_dProgress1 = -1.0;
double g_dProgress2 = -1.0;
XNode g_nodeStringTable;
int g_iStart;
simple_double_array g_daDownloadRate;
DWORD g_dwDownloadTick;
DWORD g_dwDownload;
int g_iDownloadRate;
double g_dDownloadRate;
DWORD g_dwDownloadZeroRateTick;
DWORD g_dwDownloadZeroRateRemain;
DWORD g_dwDownloadRemain;

bool g_bOfflineInstall = false;
bool g_bInternetInstall = true;
vsstring g_strIndex;
vsstring g_strIndexGz;
vsstring g_strInstall;
vsstring g_strInstallGz;

bool g_bInstallSet = false;



int run_spa(int nCmdShow)
{

   vsstring strName = "spa ignition";

   

	// Initialize global strings
	strcpy(szTitle, strName);
	strcpy(szWindowClass, strName);
	MyRegisterClass(g_hinstance);

	// Perform application initialization:
	if (!InitInstance (g_hinstance, nCmdShow))
	{
		return FALSE;
	}

//	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CCVOTAGUS_CA2_SPA));

	// Main message loop:
	while (GetMessage(&g_msg, NULL, 0, 0))
	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);
//		}
	}

	return (int) g_msg.wParam;
}




//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			   = 0;
	wcex.lpfnWndProc	   = WndProc;
	wcex.cbClsExtra	   = 0;
	wcex.cbWndExtra	   = 0;
	wcex.hInstance		   = hInstance;
	wcex.hIcon			   = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CCVOTAGUS_CA2_SPA));
	wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CCVOTAGUS_CA2_SPA);
   wcex.lpszMenuName	   = NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		   = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
   


   g_strInstallGz = dir::module_folder("ca2\\bz\\stage\\");
   g_strInstall = dir::module_folder("ca2\\stage\\");

   g_strIndexGz = dir::path(g_strInstallGz, ("app\\stage\\metastage\\" + g_strStart + ".spa.bz"));
   g_strIndex = dir::path(g_strInstallGz, ("app\\stage\\metastage\\" + g_strStart + ".spa"));

   bool bOfflineInstall1 = dir::exists(dir::module_folder("ca2\\bz"));
   //bool bOfflineInstall2 = file_exists_dup(g_strIndexGz);
   //g_bOfflineInstall = bOfflineInstall1 && bOfflineInstall2;
   g_bOfflineInstall = bOfflineInstall1;

   // Default stage.bz folder not present, would default to internet install
   // since the spa.xml is not present and contains turning information.
   if(!g_bOfflineInstall && (g_strStart.length() == 0 || (!g_bForceUpdatedBuild && g_strBuildResource.length() == 0)))
   {
      vsstring str = file_get_contents_dup(dir::module_folder("spa.xml"));
      XNode node;
      node.Load(str);
      ParseSpaIndex(node);
   }

   // Default stage.bz folder not present, would default to internet install
   // since the spa.xml is not present and contains turning information.
   if(!g_bOfflineInstall && !g_bInstallSet && (g_strStart.length() == 0 || (!g_bForceUpdatedBuild && g_strBuildResource.length() == 0)))
   {
      vsstring str = read_resource_as_string(NULL, 1984, "CA2SP");
      XNode node;
      node.Load(str);
      ParseSpaIndex(node);
   }


   if(g_strStart == "***parse_file_name")
   {

   }


int Width = 800;
   int Height = 584;

   BITMAPINFO m_Info;

   ZeroMemory(&m_Info, sizeof (BITMAPINFO));

	m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
	m_Info.bmiHeader.biWidth=Width;
	m_Info.bmiHeader.biHeight=-Height;
	m_Info.bmiHeader.biPlanes=1;
	m_Info.bmiHeader.biBitCount=32; 
	m_Info.bmiHeader.biCompression=BI_RGB;
	m_Info.bmiHeader.biSizeImage=Width*Height*4;

   LPDWORD lpdata;
	
	g_hbmAlpha=CreateDIBSection ( NULL, &m_Info, DIB_RGB_COLORS, (void **)&lpdata, NULL, NULL ); 
   for(int y = 0; y < 584; y++)
   {
      for(int x = 0; x < 800; x++)
      {
         lpdata++;
/*         if(x < 23 || x > 777 || y < 23 || y > 561)
         {
            //*lpdata = (*lpdata & 0xffffff) | 0x7f888888;
            *lpdata = (*lpdata & 0xffffff) | 0x1fffffff;
            *lpdata = 0xCA888888;
         }
         else*/
         {
            *lpdata = 0x88888888;
         }
      }
   }


   g_hdcAlpha = ::CreateCompatibleDC(NULL);
   ::SelectObject(g_hdcAlpha, g_hbmAlpha);


   g_strIndexGz = dir::path(g_strInstallGz, ("app\\stage\\metastage\\" + g_strStart + ".spa.bz"));
   g_strIndex = dir::path(g_strInstallGz, ("app\\stage\\metastage\\" + g_strStart + ".spa"));

   //read_resource

   g_bInternetInstall = !g_bOfflineInstall;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   g_iStyle = 0;

g_hbrushBk = ::CreateSolidBrush(RGB(255, 255, 255));

   if (!hWnd)
   {
      return FALSE;
   }
   if(g_iStyle == 0)
   {
   }
   else
   {
      ::SetWindowLong(hWnd, GWL_EXSTYLE, ::GetWindowLong(hWnd, GWL_EXSTYLE)
         | WS_EX_LAYERED);
   }
   ::SetWindowLong(hWnd, GWL_STYLE, ::GetWindowLong(hWnd, GWL_EXSTYLE)
      & ~(WS_BORDER | WS_CAPTION));
   
   g_hwnd = hWnd;




   if(g_iStart == 4)
   {
      StarterStart();
   }
   else if(g_strLocale.length() > 0)
   {
      if(g_strStart.length() > 0)
      {
         StarterStart();
      }
   }
   int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);
   int cyScreen = ::GetSystemMetrics(SM_CYSCREEN);

   g_cx = 800;
   g_cy = 400;

   int x = (cxScreen - g_cx) / 2;
   int y = (cyScreen - g_cy) / 2;

   SetWindowPos(hWnd, NULL, x, y, g_cx, g_cy, SWP_NOCOPYBITS);
   UpdateWindow(hWnd);
   SetTimer(hWnd, 184, 25, NULL);
   if(g_bShow)
   {
      ShowWindow(hWnd, SW_SHOW);
   }
   else
   {
      ShowWindow(hWnd, SW_HIDE);
   }

   return TRUE;
}


void PaintOpaqueBk(HDC hdc)
{
   RECT rectClient;

   ::GetClientRect(g_hwnd, &rectClient);

/*   ::FillRect(hdc, &rectClient, g_hbrushBkBorder1);

   rectClient.left += 1;
   rectClient.top += 1;
   rectClient.bottom -= 1;
   rectClient.right -= 1;
   ::FillRect(hdc, &rectClient, g_hbrushBkBorder2);
   rectClient.left += 22;
   rectClient.top += 22;
   rectClient.bottom -= 22;
   rectClient.right -= 22;*/
   ::FillRect(hdc, &rectClient, g_hbrushBk);
}

void PaintTransparentBk(HDC hdc)
{
   RECT rectWindow;

   ::GetWindowRect(g_hwnd, &rectWindow);

   HDC hdcScreen = ::GetDC(NULL);

   ::BitBlt(hdc, 0, 0, 800, 584, hdcScreen, rectWindow.left, rectWindow.top, SRCCOPY);

   BLENDFUNCTION bf;

	bf.BlendOp             = AC_SRC_OVER;						// Only works with a 32bpp bitmap
	bf.BlendFlags          = 0;											// Always 0
	bf.SourceConstantAlpha = 255;										// Set to 255 for per-pixel alpha values
	bf.AlphaFormat         = AC_SRC_ALPHA;						// Only works when the bitmap contains an alpha channel
   ::AlphaBlend(hdc, 0, 0, 800, 584, g_hdcAlpha, 0, 0, 800, 584, bf);

   ::ReleaseDC(NULL, hdcScreen);
}



void PaintBk(HDC hdc)
{
   if(g_iStyle == 0)
   {
      PaintOpaqueBk(hdc);
   }
   else
   {
      PaintTransparentBk(hdc);
   }
}


void OnPaint(HWND hwnd, HDC hdcWindow, LPRECT lprect = NULL)
{
   RECT rectWindow;
   ::GetWindowRect(hwnd, &rectWindow);


   int cx = rectWindow.right - rectWindow.left;
   int cy = rectWindow.bottom - rectWindow.top;

   RECT rect;
   rect.left         = 0;
   rect.top          = 0;
   rect.right        = cx;
   rect.bottom       = cy;

   if(lprect == NULL)
   {
      lprect = &rect;
   }

   BITMAPINFO m_Info;

	m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
	m_Info.bmiHeader.biWidth=cx;
	m_Info.bmiHeader.biHeight=cy;
	m_Info.bmiHeader.biPlanes=1;
	m_Info.bmiHeader.biBitCount=32; 
	m_Info.bmiHeader.biCompression=BI_RGB;
	m_Info.bmiHeader.biSizeImage=cx*cy*4;

   LPDWORD lpdata;
	
	HBITMAP hbmp = CreateDIBSection ( NULL, &m_Info, DIB_RGB_COLORS, (void **)&lpdata, NULL, NULL ); 

   //HBITMAP hbmp      = ::CreateCompatibleBitmap(hdcWindow, cx, cy);
   HDC hdc           = ::CreateCompatibleDC(NULL);
   HBITMAP hbmpOld   =  (HBITMAP) ::SelectObject(hdc, (HGDIOBJ) hbmp);
   
   //::BitBlt(hdc, 0, 0, cx, cy, hdcWindow, 0, 0, SRCCOPY);

   PaintBk(hdc);

   HFONT hfontOld = NULL;
   HFONT hfont = NULL;

   ca2_install_canvas_on_paint(hdc, &rect, g_iHealingSurface);


   POINT pointViewport;
   ::SetViewportOrgEx(hdc, 0, 0, &pointViewport);
   ::BitBlt(hdcWindow, lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top, 
            hdc,       lprect->left, lprect->top, SRCCOPY);
   ::SelectObject(hdc, (HGDIOBJ) hbmpOld);
   if(hfontOld != NULL)
   {
      ::SelectObject(hdc,(HGDIOBJ)  hfontOld);
   }
   if(hfont != NULL)
   {
      ::DeleteObject(hfont);
   }
   ::DeleteObject(hbmp);
   ::DeleteDC(hdc);
}


void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdcWindow;
	hdcWindow = BeginPaint(hwnd, &ps);
   OnPaint(hwnd, hdcWindow, &ps.rcPaint);
	EndPaint(hwnd, &ps);

}

void OnTimer(HWND hwnd, UINT nIDEvent)
{
   if(nIDEvent == 184)
   {
      HDC hdc = ::GetWindowDC(hwnd);
      OnPaint(hwnd, hdc, NULL);
      ::ReleaseDC(hwnd, hdc);
   }
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
   case WM_CREATE:
      {
         ::SetTimer(hWnd, TIMER_CARET, 100, NULL);
         ::SetTimer(hWnd, TIMER_ANIMATION, 33, NULL);
      }
      break;
	case WM_PAINT:
      OnPaint(hWnd);
		break;
	case WM_ERASEBKGND:
      return TRUE;
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
      g_iHealingSurface++;
      return TRUE;
   case WM_LBUTTONDOWN:
      {
         g_iHealingSurface++;
         g_bDrag = true;
         ::GetCursorPos(&g_ptDragStart);
         ::GetWindowRect(g_hwnd, &g_rectWindowDragStart);
      };
      break;
   case WM_MOUSEMOVE:
      {
         if(g_bDrag)
         {
            DragMainWindow();
         }
      };
      break;
   case WM_LBUTTONUP:
      {
         if(g_bDrag)
         {
            DragMainWindow();
            g_bDrag = false;
         }
      };
      break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
   case WM_TIMER:
      OnTimer(hWnd, wParam);
      break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}








vsstring CommandToLang(int iLang)
{
   for(int i = 0; g_langa[i].m_iCommand != -1; i++)
   {
      if(g_langa[i].m_iCommand == iLang)
         return g_langa[i].m_strCode;
   }
   return "sv"; // default "Sverige"
}

int LangToCommand(const char * pszLocale)
{
   for(int i = 0; g_langa[i].m_iCommand != -1; i++)
   {
      if(g_langa[i].m_strCode == pszLocale)
         return g_langa[i].m_iCommand;
   }
   return ID_LANG_SV; // default "Sverige"
}

void CommandLang(int iLang)
{
   g_strLocale = CommandToLang(iLang);
   g_nodeStringTable.Load(read_resource_as_string(NULL, iLang, "XML"));
}


/*
vsstring Login()
{
   if(_stricmp(g_pedit->m_str, "ca") == 0
      && _stricmp(g_pedit->m_pnext->m_str, "ca") == 0)
   {
      return "OK";
   }
   vsstring document;
   vsstring strPost;
   strPost = "entered_login=";
   strPost += g_pedit->m_str;
   strPost += "&entered_password=";
   strPost += g_pedit->m_pnext->m_str;
   document = ms_post("https://votagus.net/ca2api/auth", strPost);
	return document;
}
*/





/*bool Get(const vsstring& url_in,vsstring & document)
{
   bool https = !strcasecmp(url.substr(0,8), "https://");
	int port = https ? 443 : 80;
	vsstring url = url_in;
	vsstring file; // get filename at end of url
	vsstring dir; // get filename at end of url
	{
		Parse pa(url,"/");
		vsstring tmp = pa.getword();
      vsstring lastfile;
		while (tmp.size())
		{
			file = tmp;
         dir = "/" + lastfile;
         lastfile = file;
			tmp = pa.getword();
		}
	}
	SocketHandler h;
	bool complete = false;
	
	if (!strcasecmp(protocol,"http") || https)
	{
		HttpGetSocket s(h, host, port, dir, file);
		unsigned char *p = new unsigned char[32000]; // max doc size
		memset(p, 0, 32000);
		s.SetDataPtr(p, 31999); // preserve zero at end of document
/*		if (https)
		{
			s.EnableSSL();
		}*/
/*		h.Add(&s);
		h.Select(1,0);
		while (h.GetCount())
		{
			h.Select(1,0);
		}
		complete = s.Complete();
		if (complete)
		{
			document = static_cast<vsstring>( (char *)s.GetDataPtr());
		}
		delete[] s.GetDataPtr();
	}
	else
	{
		printf("Unknown protocol: '%s'\n",protocol);
	}
	if (complete)
	{
		printf("%s\n", document);
	}
	return complete;
}*/



bool Get(const vsstring& url_in, bool bExist, int iLength, const char * pszMd5, int iGzLen)
{
   if(g_bOfflineInstall)
      return true;
	vsstring url = url_in;
	vsstring file;
   vsstring file2;
   vsstring dir;
   vsstring dir2;
   dir = dir::beforeca2();
   if(dir.substr(dir.size() - 2, 1) != "\\")
   {
      dir += "\\";
   }
   dir2 = dir + "ca2\\";
   dir += "ca2\\time\\bz\\";
   int oldpos = -1;
	{
      int pos = url_in.find(g_strInstall);
      if(pos == 0)
      {
         url = url_in.substr(g_strInstall.length());
      }
      int oldpos = -1;
      pos = url.find("/");
      vsstring lastfile;
		while (pos >=0)
		{
			file = url.substr(oldpos + 1, pos - oldpos -1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
         lastfile = file;
         oldpos = pos;
         pos = url.find("/", oldpos + 1);
		}
		file = url.substr(oldpos + 1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
	}
   if(_stricmp(file.substr(file.length() - 3, 3), ".bz") == 0)
   {
      file2 = file.substr(0, file.length() - 3);
   }
   else
   {
      file2 = file;
   }
   dir::mk(dir);
   
   if(bExist)
   {
      DWORD dwFileAttributes = ::GetFileAttributes((dir2 + file2));
      if(dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
      (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      {
         if(iLength != -1 && iLength == file_length_dup((dir2 + file2)))
         {
            if(pszMd5 != NULL && strlen_dup(pszMd5) > 0 && _stricmp(get_file_md5((dir2 + file2)), pszMd5) == 0)
            {
               return true;
            }
         }
      }
   }
#ifdef WIN32
   dir::mk(dir::name((dir + file)));
   g_dwCurFileLen = iGzLen;
   g_dwDownloadLen = 0;
   keep_true keepDownloadTrue(g_bMsDownload);
   return ms_download_dup(url_in, (dir + file), true, false, NULL, &::ms_download_callback, (void *) true);
#else
	if (!strcasecmp(protocol,"http") || !strcasecmp(protocol,"https"))
	{
		SpaHttpGet s(h, url_in, "");
//      s.SetLineProtocol(false);
      s.SetFilename(dir + file);
      dir::mk(dir::name((dir + file)));
		h.Add(&s);
		h.Select(31,0);
		while (h.GetCount())
		{
			h.Select(31,0);
		}
		return s.Complete();
	}
	else
	{
		printf("Unknown protocol: '%s'\n",protocol);
	}
	return false;
#endif
}


bool DownloadFile(const vsstring& url_in, bool bExist, int iLength, const char * pszMd5, int iGzLen)
{
   if(g_bOfflineInstall)
      return true;
	vsstring url = url_in;
	vsstring file;
   vsstring file2;
   vsstring dir;
   vsstring dir2;
   vsstring dir3;
   dir = dir::beforeca2();
   if(dir.substr(dir.size() - 2, 1) != "\\")
   {
      dir += "\\";
   }
   dir3 = dir + "ca2\\time\\patchwork\\";
   dir2 = dir + "ca2\\time\\unbz\\";
   dir += "ca2\\time\\bz\\";
   int oldpos = -1;
	{
      int pos = url_in.find(g_strInstall);
      if(pos == 0)
      {
         url = url_in.substr(g_strInstall.length());
      }
      int oldpos = -1;
      pos = url.find("/");
      vsstring lastfile;
		while (pos >=0)
		{
			file = url.substr(oldpos + 1, pos - oldpos -1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
         lastfile = file;
         oldpos = pos;
         pos = url.find("/", oldpos + 1);
		}
		file = url.substr(oldpos + 1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
	}
   if(_stricmp(file.substr(file.length() - 3, 3), ".bz") == 0)
   {
      file2 = file.substr(0, file.length() - 3);
   }
   else
   {
      file2 = file;
   }
   dir::mk(dir);
   
   // first check if the exiting (old file) is already up-to-date (the current one)
   if(bExist)
   {
      DWORD dwFileAttributes = ::GetFileAttributes((dir2 + file2));
      if(dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
      (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      {
         if(iLength != -1 && iLength == file_length_dup((dir2 + file2)))
         {
            if(pszMd5 != NULL && strlen_dup(pszMd5) > 0 && _stricmp(get_file_md5((dir2 + file2)), pszMd5) == 0)
            {
               trace_add(_unitext(" up-to-date ✓"));
               return true;
            }
         }
      }
   }
#ifdef WIN32
   bool bOk = false;
   int iRetry = 0;
   int iMaxRetry = 3;
   char sz[1024];
   int iStatus;
   if(file_exists_dup((dir2 + file2)))
   {
      // then first try to download and apply patch
      vsstring strOldMd5 = get_file_md5((dir2 + file2));
      vsstring strNewMd5 = pszMd5;
      dir::mk(dir::name((dir + file)));
      g_dwCurFileLen = iGzLen;
      g_dwDownloadLen = 0;
      keep_true keepDownloadTrue(g_bMsDownload);
      int iBsLen = 0;
      bool bPossible = false;
      while(true)
      {
         vsstring strUrl;
         strUrl = "http://saintlouis.us.spa.api.veriterse.net/bspatch?file=";
         strUrl += url_encode_dup(file2);
         strUrl += "&old_hash=";
         strUrl += strOldMd5;
         strUrl += "&new_hash=";
         strUrl += strNewMd5;
         vsstring strBsPatch = dir + file + "." + strOldMd5 + "." + strNewMd5 + ".bspatch";
         bOk = ms_download_dup(strUrl, strBsPatch, false, &iStatus);
         if(iStatus == 404)
            break;
         if(!bPossible)
         {
            bPossible = true;
            ///trace_add(" patching may be possible");
         }
         if(bOk)
         {
            int iResult = 0;
            if(iLength != -1)
            {
               dir::mk(dir::name((dir3 + file2)));
               iResult = bspatch((dir2 + file2), (dir3 + file2), strBsPatch);
               if(iResult != 0)
               {
               //   trace("");
                 // trace("Patch failed : files may be corrupted):");
/*                  trace("old   file : ");
                  trace_add((dir2 + file2));
                  trace("new   file :");
                  trace_add((dir3 + file2));
                  trace("patch file :");
                  trace_add(strBsPatch);*/
                  bOk = false;
               }
            }
         }
         if(bOk)
         {
            if(iLength == -1)
            {
             //  trace("Patch Length Check : There is no length information to check.");
            }
            else
            {
               int iActualLength = file_length_dup((dir3 + file2));
               bOk = iLength == iActualLength;
               //trace("Patch Length Verification : ");
               /*sprintf(sz, "correct length : %d bytes", iLength);
               trace(sz);
               sprintf(sz, "actual  length : %d bytes", iActualLength);
               trace(sz);*/
               if(bOk)
               {
               //   trace_add("Length match!");
               }
               else
               {
                 // trace_add(_unitext("Length mismatch ¡X!"));
               }
            }
         }
         if(bOk)
         {
            if(pszMd5 == NULL || strlen_dup(pszMd5) == 0)
            {
               //trace("Patch MD5 Hash Verification : there is no MD5 Hash information to verify.");
            }
            else
            {
               vsstring strMd5;
               strMd5 = get_file_md5((dir3 + file2));
               bOk = _stricmp(strMd5, pszMd5) == 0;
               //trace("Patch MD5 Hash Verification");
               /*sprintf(sz, "correct MD5 Hash : %s", pszMd5);
               trace(sz);
               sprintf(sz, "actual  MD5 Hash : %s", strMd5);
               trace(sz);*/
               if(bOk)
               {
                 // trace_add("MD5 Hash match!");
               }
               else
               {
                  //trace_add(_unitext("MD5 Hash mismatch ¡X!"));
               }
            }
         }
         if(bOk)
         {
            if(!::CopyFile((dir3 + file2), (dir2 + file2), FALSE))
            {
               trace("Failed to copy patched file: Need Restart Because Of Reserved File");
               g_NeedRestartBecauseOfReservedFile = true;
            }
            iBsLen = file_length_dup(strBsPatch);
            break;
         }
         iRetry++;
         //sprintf(sz, "An error ocurred. Retrying... Attempt %d of %d.", iRetry, iMaxRetry);
         //trace(sz);
         //trace("Patch may fail due timeout if the patched file is large and it is the first");
         //trace("time the patch is requested for the older-newer-pair patch combination.");
         //trace("Other users later requesting the same older-newer-pair patch combination will");
         //trace("benefit from the cached patch.");
         Sleep((1984 + 1977) * 5);
         if(iRetry >= iMaxRetry)
            break;
      }
      if(bOk)
      {
         if(iRetry > 0)
         {
           // sprintf(sz, _unitext("Patch succeeded with %d retries %0.2fkbytes compressed ✓"), (iBsLen / 1000.0), iRetry);
            trace_add(_unitext(" ✓"));
         }
         else
         {
            // this trace is added and signalized like that because it
            // should be one of the most common cases and one of the most
            // normal cases.
            //sprintf(sz, _unitext(" patched %0.2fkbytes compressed ✓"), (iBsLen / 1000.0));
            //trace_add(sz);
            trace_add(_unitext(" ✓"));
         }
      }
      else
      {
         //trace(_unitext("Patch failed ¡X!"));
      }
   }
   // then finally try to download the entire file
   if(!bOk)
   {
      dir::mk(dir::name((dir + file)));
      g_dwCurFileLen = iGzLen;
      g_dwDownloadLen = 0;
      keep_true keepDownloadTrue(g_bMsDownload);
      if(iRetry > 0)
      {
         //trace(("Going to download " + file_title_dup(file2) + " entirely"));
      }
      trace(file2);
      iRetry = 0;
      while(true)
      {
         bOk = ms_download_dup((url_in + "." + pszMd5), (dir + file + "." + pszMd5), true, true, &iStatus, &::ms_download_callback, (void *) true);
         if(iStatus == 404)
            break;
         if(bOk)
         {
            if(iLength != -1)
            {
               int iResult = bzuncompress((dir2 + file2), (dir + file + "." + pszMd5));
               if(iResult == -1)
               {
                  g_NeedRestartBecauseOfReservedFile = true;
               }
               else if(iResult == -2)
               {
                  g_NeedRestartFatalError = true;
               }
            }
            bOk = iLength == -1 || iLength == file_length_dup((dir2 + file2));
            if(bOk)
            {
               bOk = pszMd5 == NULL || strlen_dup(pszMd5) == 0 || _stricmp(get_file_md5((dir2 + file2)), pszMd5) == 0;
               if(bOk)
               {
                  break;
               }
            }
         }
         iRetry++;
         //sprintf(sz, "An error ocurred. Retrying... Attempt %d of %d.", iRetry, iMaxRetry);
         //trace(sz);
         if(iRetry >= iMaxRetry)
            break;
      }
      if(bOk)
      {
         sprintf(sz, _unitext("%0.2fkbytes compressed ✓"), (iGzLen / 1000.0));
         trace(sz);
      }
      else
      {
         //trace((_unitext("Failed to download file ") + file2 + _unitext("¡X!")));
      }
   }
   if(!bOk)
   {
      //sprintf(sz, _unitext("General failure to retrieve file \"%s\" ¡X!"), file2);
      //trace(sz);
   }
   return bOk;
#else
	if (!strcasecmp(protocol,"http") || !strcasecmp(protocol,"https"))
	{
		SpaHttpGet s(h, url_in, "");
//      s.SetLineProtocol(false);
      s.SetFilename(dir + file);
      dir::mk(dir::name((dir + file)));
		h.Add(&s);
		h.Select(31,0);
		while (h.GetCount())
		{
			h.Select(31,0);
		}
		return s.Complete();
	}
	else
	{
		printf("Unknown protocol: '%s'\n",protocol);
	}
	return false;
#endif
}



vsstring ca2_get_dir(LPCTSTR lpcszUrl)
{
   vsstring url_in(lpcszUrl);
   vsstring dir;
   vsstring url;
   vsstring file;
   dir = dir::beforeca2();
   if(dir.substr(dir.size() - 2, 1) != "\\")
   {
      dir += "\\";
   }
   dir += "ca2\\";
   vsstring strFind;
   int pos = url_in.find(g_strInstall);
   if(pos == 0)
   {
      url = url_in.substr(g_strInstall.length());
   }
   else
   {
      url = url_in;
   }
   int oldpos = -1;
   pos = url.find("/");
   vsstring lastfile;
	while (pos >=0)
	{
		file = url.substr(oldpos + 1, pos - oldpos -1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      lastfile = file;
      oldpos = pos;
      pos = url.find("/", oldpos + 1);
	}
	file = url.substr(oldpos + 1);
   if(lastfile.size() > 0)
      dir +=  lastfile + "\\";
   return dir;
}

vsstring ca2bz_get_dir(LPCTSTR lpcszUrl)
{
   vsstring url_in(lpcszUrl);
   vsstring dir;
   vsstring url;
   vsstring file;
   if(g_bInternetInstall)
   {
      dir = dir::path(dir::afterca2(), "time\\bz\\");
   }
   else
   {
      dir = g_strInstallGz;
   }
   int pos = url_in.find(g_strInstall);
   if(pos == 0)
   {
      url = url_in.substr(g_strInstall.length());
   }
   else
   {
      url = url_in;
   }
   int oldpos = -1;
   pos = url.find("/");
   vsstring lastfile;
	while (pos >=0)
	{
		file = url.substr(oldpos + 1, pos - oldpos -1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      lastfile = file;
      oldpos = pos;
      pos = url.find("/", oldpos + 1);
	}
	file = url.substr(oldpos + 1);
   if(lastfile.size() > 0)
      dir +=  lastfile + "\\";
   return dir;
}
vsstring ca2unbz_get_dir(LPCTSTR lpcszUrl)
{
   vsstring url_in(lpcszUrl);
   vsstring dir;
   vsstring url;
   vsstring file;
   if(g_bInternetInstall)
   {
      dir = dir::path(dir::afterca2(), "time\\unbz\\");
   }
   else
   {
      dir = g_strInstallGz;
   }
   int pos = url_in.find(g_strInstall);
   if(pos == 0)
   {
      url = url_in.substr(g_strInstall.length());
   }
   else
   {
      url = url_in;
   }
   int oldpos = -1;
   pos = url.find("/");
   vsstring lastfile;
	while (pos >=0)
	{
		file = url.substr(oldpos + 1, pos - oldpos -1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      lastfile = file;
      oldpos = pos;
      pos = url.find("/", oldpos + 1);
	}
	file = url.substr(oldpos + 1);
   if(lastfile.size() > 0)
      dir +=  lastfile + "\\";
   return dir;
}
vsstring ca2_get_file(LPCTSTR lpcszUrl)
{
   vsstring url_in(lpcszUrl);
   vsstring dir;
   vsstring url;
   vsstring file;
   dir = dir::beforeca2();
   if(dir.substr(dir.size() - 2, 1) != "\\")
   {
      dir += "\\";
   }
   dir += "ca2\\";
   vsstring strFind;
   int pos = url_in.find(g_strInstall);
   if(pos == 0)
   {
      url = url_in.substr(g_strInstall.length());
   }
   else
   {
      url = url_in;
   }
   int oldpos = -1;
   pos = url.find("/");
   vsstring lastfile;
	while (pos >=0)
	{
		file = url.substr(oldpos + 1, pos - oldpos -1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      lastfile = file;
      oldpos = pos;
      pos = url.find("/", oldpos + 1);
	}
	file = url.substr(oldpos + 1);
   if(lastfile.size() > 0)
      dir +=  lastfile + "\\";
   if(file.substr(file.size() - 3, 3) == ".bz")
      return file.substr(0, file.size() - 3);
   else
      return file;
}
vsstring ca2bz_get_file(LPCTSTR lpcszUrl, const char * pszMd5)
{
   vsstring url_in(lpcszUrl);
   vsstring dir;
   vsstring url;
   vsstring file;
   dir = dir::path(dir::afterca2(), "time\\bz\\");
   vsstring strFind;
   int pos = url_in.find(g_strInstall);
   if(pos == 0)
   {
      url = url_in.substr(g_strInstall.length());
   }
   else
   {
      url = url_in;
   }
   int oldpos = -1;
   pos = url.find("/");
   vsstring lastfile;
   while (pos >=0)
   {
	   file = url.substr(oldpos + 1, pos - oldpos -1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      lastfile = file;
      oldpos = pos;
      pos = url.find("/", oldpos + 1);
   }
   file = url.substr(oldpos + 1);
   if(lastfile.size() > 0)
      dir +=  lastfile + "\\";
   if(pszMd5 != NULL)
   {
      if(file.substr(file.size() - 3, 3) == ".bz")
         return file + "." + pszMd5;
      else
         return file + ".bz." + pszMd5;
   }
   else
   {
      if(file.substr(file.size() - 3, 3) == ".bz")
         return file;
      else
         return file + ".bz";
   }
}

vsstring ca2unbz_get_file(LPCTSTR lpcszUrl)
{
   vsstring url_in(lpcszUrl);
   vsstring dir;
   vsstring url;
   vsstring file;
   dir = dir::path(dir::afterca2(), "time\\unbz\\");
   vsstring strFind;
   int pos = url_in.find(g_strInstall);
   if(pos == 0)
   {
      url = url_in.substr(g_strInstall.length());
   }
   else
   {
      url = url_in;
   }
   int oldpos = -1;
   pos = url.find("/");
   vsstring lastfile;
   while (pos >=0)
   {
	   file = url.substr(oldpos + 1, pos - oldpos -1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      lastfile = file;
      oldpos = pos;
      pos = url.find("/", oldpos + 1);
   }
   file = url.substr(oldpos + 1);
   if(lastfile.size() > 0)
      dir +=  lastfile + "\\";
   if(file.substr(file.size() - 3, 3) == ".bz")
      return file.substr(0, file.size() - 3);
   else
      return file;
}

bool ca2_fy_url(vsstring & str, LPCTSTR lpcszPath, bool bExist, int iLength, const char * pszMd5, int iGzLen, bool bIndex)
{
   vsstring strStage;
   vsstring strStageGz;
   vsstring strUrl;
   strUrl = lpcszPath;
   if(bIndex)
   {
	   if (!Get(g_strInstall + lpcszPath, bExist, iLength, pszMd5, iGzLen))
	   {
		   printf("Failed: %s\n",strUrl);
         return false;
	   }
      if(g_bOfflineInstall)
      {
         strStageGz = strUrl;
         strStageGz = ca2bz_get_dir(strUrl) + ca2bz_get_file(strUrl, NULL);
      }
      else
      {
         strStageGz = ca2bz_get_dir(strUrl) + ca2bz_get_file(strUrl, NULL);
      }
   }
   else
   {
	   if (!Get(g_strInstall + lpcszPath + "." + pszMd5, bExist, iLength, pszMd5, iGzLen))
	   {
		   printf("Failed: %s\n",strUrl);
         return false;
	   }
      if(g_bOfflineInstall)
      {
         strStageGz = strUrl;
         strStageGz = ca2bz_get_dir(strUrl) + ca2bz_get_file(strUrl, pszMd5);
      }
      else
      {
         strStageGz = ca2bz_get_dir(strUrl) + ca2bz_get_file(strUrl, pszMd5);
      }
   }
   strStage = ca2_get_dir(strUrl) + ca2_get_file(strUrl);
   dir::mk(dir::name(strStage));
   bzuncompress(strStage, strStageGz);
   str = strStage;
   return true;
}






int GetFileList(stra_dup & stra, LPCTSTR lpcszPath, simple_string_to_intptr & mapLen, simple_string_to_intptr & mapGzLen, simple_string_to_string & mapMd5)
{
   vsstring strPath(lpcszPath);
   strPath = str_replace(strPath, "/", "\\");
   strPath = strPath;
   vsstring strUrl(lpcszPath);
   if(strUrl.length() == 0)
      return -1;
   if(str_ends_ci_dup(strUrl, ".spa"))
   {
      if(!g_strSpa.spa_insert(strUrl))
      {
         return -1;
      }
   }
   else
   {
      return -1;
   }
   trace(str_replace(strUrl, "\\", "/"));
   char buf[2048];
   int iCount = 0;
   int iCurrent;
   strUrl += ".bz";
   vsstring str;
   vsstring strMd5 = mapMd5[strPath];
   if(!ca2_fy_url(str, strUrl, false, -1, strMd5, -1))
      return -2;
   FILE * f = fopen(str, "rb");
   vsstring strPlatform = spa_get_platform();
   while(fgets(buf, sizeof(buf), f))
   {
      buf[sizeof(buf) - 1] = '\0';
      while(buf[strlen_dup(buf) - 1] == '\r' || buf[strlen_dup(buf) - 1] == '\n')
      {
         buf[strlen_dup(buf) - 1] = '\0';
      }
      vsstring str2;
      vsstring strPathParam(buf);
      if(str_begins_ci_dup(strPathParam, "stage\\basis\\"))
      {
         strPathParam = "stage\\" + strPlatform + strPathParam.substr(11);
      }
      iCurrent = GetFileList(stra, strPathParam, mapLen, mapGzLen, mapMd5);
      if(iCurrent == -2)
      {
         return -2;
      }
      else if(iCurrent == -1)
      {
         if(stra.spa_insert(strPathParam))
         {
            g_iTotalGzLen += mapGzLen[strPathParam];
         }
      }
      else 
      {
         iCount += iCurrent;
      }
   }
   fclose(f);
   return 1;
}

int GetLocalFileList(stra_dup & stra, LPCTSTR lpcszUrl)
{

   vsstring strUrl(lpcszUrl);
   trace(strUrl);
   //MainWindowRedraw();
   if(strUrl.substr(strUrl.size() - 4, 4) != ".spa")
   {
      return -1;
   }
   char buf[2048];
   int iCount = 0;
   int iCurrent;
   strUrl += ".bz";
   vsstring str;
   if(!ca2_fy_url(str, strUrl, false, -1, NULL, -1))
      return -2;
   FILE * f = fopen(str, "rb");
   char * pszFind1;
   char * pszFind2;
   while(fgets(buf, sizeof(buf), f))
   {
      while(buf[strlen_dup(buf) - 1] == '\r' || buf[strlen_dup(buf) - 1] == '\n')
      {
         buf[strlen_dup(buf) - 1] = '\0';
      }
      pszFind1 = strstr(buf, ",");
      pszFind2 = NULL;
      if(pszFind1 != NULL)
      {
         pszFind2 = strstr(pszFind2 + 1, ",");
      }
      if(pszFind1 != NULL)
      {
         *pszFind1 = '\0';
         pszFind1++;
      }
      if(pszFind2 != NULL)
      {
         *pszFind2 = '\0';
         pszFind2++;
      }
      vsstring strSpa;
      vsstring str2;
      iCurrent = GetLocalFileList(stra, buf);
      if(iCurrent == -1)
      {
         stra.spa_insert(buf);
      }
      else
      {
         iCount += iCurrent;
      }
   }
   fclose(f);
   return iCount;
}

void MainWindowRedraw()
{
   if(!::IsIconic(g_hwnd) && IsWindowVisible(g_hwnd))
   {
      ::RedrawWindow(g_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
   }
}


int DownloadFileList(stra_dup & stra, simple_string_to_intptr & mapLen, simple_string_to_string & mapMd5, simple_string_to_intptr & mapGzLen)
{
restart_download:
   g_dwDownloadTick = ::GetTickCount();
   g_dwDownload = 0;
   g_iDownloadRate = 0;
   g_bShowPercentage = true;
   g_iGzLen = 0;
   
   vsstring str;
   double d = 0.0;
   g_dProgress = 0.0;
   bool bDownload;
   
   for(int i = 0; i < stra.get_count(); i++)
   {
      vsstring * it = &stra[i];
      if(g_iTotalGzLen > 0)
      {
         g_dProgress1 = (double) g_iGzLen / (double) g_iTotalGzLen;
         g_dProgress2 = (double) (g_iGzLen + mapGzLen[*it]) / (double) g_iTotalGzLen;
      }
      else
      {
         g_dProgress1 = d / ((double) stra.get_count());
         d += 1.0;
         g_dProgress2 = d / ((double) stra.get_count());
      }
      str = g_strInstall;
      str += *it;
      vsstring str1 = *it;
      vsstring str2 = dir::name(str);
      if(str2.substr(0, g_strInstall.length()) == g_strInstall)
      {
         str2 = str2.substr(21);
         str2 = str_replace(str2, "\\", "/");
      }
      trace(str_replace(file_title_dup((str2 + str)), "\\", "/"));
      str += ".bz";
      vsstring str3 = str;
      str += ".";
      str += mapMd5[*it];
      vsstring strStageGz = ca2bz_get_dir(str1) + ca2bz_get_file(str1, mapMd5[*it]);
      vsstring strStageUnbz = ca2unbz_get_dir(str1) + ca2unbz_get_file(str1);
      dir::mk(dir::name(strStageUnbz));
      // uncompress, may have downloaded .bz correctly in previous install
      // and Get will later check if decompressed file is already the correct one
      bzuncompress(strStageUnbz, strStageGz);
      bDownload = true;
      if(str_ends_ci_dup(strStageUnbz, ".expand_fileset") && file_exists_dup(strStageGz) && file_length_dup(strStageGz)>0)
      {
         vsstring strExpand = *it;
         vsstring strCurrent = *it;
         strExpand += ".spa";
         strExpand = str_replace(str_replace(strExpand, "\\", "_"), "/", "_");
         strExpand = "app\\stage\\metastage\\" + strExpand;
         if(GetFileList(stra, strExpand , mapLen, mapGzLen, mapMd5) > 0)
         {
            stra.remove(strCurrent);
            g_iTotalGzLen -= mapGzLen[strCurrent];
            goto restart_download;
         }
      }
      if(bDownload
         && DownloadFile(str3, true, mapLen[*it], mapMd5[*it], mapGzLen[*it]))
      {
         g_dProgress = g_dProgress2;
         if(str_ends_ci_dup(strStageUnbz, ".expand_fileset"))
         {
            str = *it;
            vsstring strExpand = *it;
            vsstring strCurrent = *it;
            vsstring strRelative = dir::path(dir::name(str), file_name_dup(str));
            vsstring strStageUnbz1 = ca2unbz_get_dir(str) + ca2unbz_get_file(str);
            vsstring strStageUnbz2 = ca2unbz_get_dir(strRelative) + ca2unbz_get_file(strRelative);
            file_ftd_dup(strStageUnbz2, strStageUnbz);
            strExpand += ".spa";
            strExpand = str_replace(str_replace(strExpand, "\\", "_"), "/", "_");
            strExpand = "app\\stage\\metastage\\" + strExpand;
            if(GetFileList(stra, strExpand , mapLen, mapGzLen, mapMd5) > 0)
            {
               stra.remove(strCurrent);
               g_iTotalGzLen -= mapGzLen[strCurrent];
               goto restart_download;
            }
         }
      }
      else
      {
         if(bDownload)
         {
            /*vsstring strError;
            strError = "could not get file ";
            strError += str;
            trace(strError);*/
            //::MessageBox(g_hwnd, strError, "ca2 votagus spa",  MB_ICONINFORMATION);
         }
      }
      g_iGzLen += mapGzLen[*it];
      dlr(g_iGzLen);

   }
   MainWindowRedraw();
   return stra.get_count();
}



int UncompressFileList(stra_dup & stra, simple_string_to_string & strmapMd5)
{
   vsstring strStage;
   vsstring strStageGz;
   
   vsstring str;
   double d = 0.0;
   g_dProgress = 0.0;
   for(int i = 0; i < stra.get_count(); i++)
   {
      vsstring * it = &stra[i];
      //g_dProgress1 = d / ((double) stra.size());
      //d += 1.0;
      //g_dProgress2 = d / ((double) stra.size());
      str = *it;
      str += ".bz";
      trace(str);
      strStageGz = dir::path(g_strInstallGz, ca2bz_get_file(str, strmapMd5[*it]));
      strStage = ca2_get_dir(str) + ca2_get_file(str);
      dir::mk(dir::name(strStage));
      bzuncompress(strStage, strStageGz);
      d += 1.0;
      g_dProgress = d / ((double) stra.get_count());
   }
   g_dProgress = 1.0;
   MainWindowRedraw();
   return stra.get_count();
}

int CopyFileList(stra_dup & stra)
{
   vsstring strStage;
   vsstring strStageUnbz;
   vsstring str;
   double d = 0.0;
   g_dProgress = 0.0;
   for(int i = 0; i < stra.get_count(); i++)
   {
      vsstring * it = &stra[i];
      //g_dProgress1 = d / ((double) stra.size());
      //d += 1.0;
      //g_dProgress2 = d / ((double) stra.size());
      str = *it;
      str += ".bz";
      trace(str);
      strStageUnbz = ca2unbz_get_dir(str) + ca2unbz_get_file(str);
      strStage = ca2_get_dir(str) + ca2_get_file(str);
      if(strStage.length() > strlen_dup(".expand_fileset")
         && _stricmp(strStage.substr(strStage.length() - strlen_dup(".expand_fileset"), strlen_dup(".expand_fileset")), ".expand_fileset") ==
0)
      {
//         file_ftd_dup(strStage.substr(0, strStage.length() - strlen_dup(".expand_fileset")), strStageUnbz);
      }
      else
      {
         dir::mk(dir::name(strStage));
         ::CopyFile(strStageUnbz, strStage, FALSE);
      }
      d += 1.0;
      g_dProgress = d / ((double) stra.get_count());
   }
   g_dProgress = 1.0;
   MainWindowRedraw();
   return stra.get_count();
}




void ParseSpaIndex(XNode & node)
{
   if(node.name == "spa" && node.childs.get_count() > 0)
   {
      LPXNode lpnode = &node;
      for(unsigned int ui = 0; ui < lpnode->childs.get_count(); ui++)
      {
         if(lpnode->childs[ui]->name == "index")
         {
            if(lpnode->childs[ui]->GetAttr("start") != NULL)
            {
               if(vsstring(lpnode->childs[ui]->GetAttrValue("start")).length() > 0)
               {
                  g_iStart = 4;
                  g_strStart = vsstring(lpnode->childs[ui]->GetAttrValue("start"));
               }
            }
            if(lpnode->childs[ui]->GetAttr("build") != NULL)
            {
               if(vsstring(lpnode->childs[ui]->GetAttrValue("build")).length() > 0)
               {
                  g_iStart = 4;
                  g_strBuildResource = vsstring(lpnode->childs[ui]->GetAttrValue("build"));
               }
            }
            if(lpnode->childs[ui]->GetAttr("type") != NULL)
            {
               if(vsstring(lpnode->childs[ui]->GetAttrValue("type")) == "parse_file_name")
               {
                  g_iStart = 4;
                  char buf[2048];
                  ::GetModuleFileName(NULL, buf, sizeof(buf));
                  const char * psz = strrchr(buf, '\\');
                  vsstring str;
                  if(psz == NULL)
                  {
                     str = buf;
                  }
                  else
                  {
                     str = psz;
                  }
                  if(!_stricmp(str.substr(str.length()  - 4, 4), ".exe"))
                  {
                     str = str.substr(str.length() - 4);
                     if(str.length() > 19)
                     {
                        g_strStart = str.substr(0, str.length() - 19);
                        g_strBuildResource = str.substr(str.length() - 19);
                     }
                  }
               }
               else if(vsstring(lpnode->childs[ui]->GetAttrValue("type")) == "online_default")
               {
                  g_bOfflineInstall = false;
                  g_strInstallGz = "http://ccvotagus.net/stage/";
                  g_strInstall = "http://ccvotagus.net/stage/";
               }
               else if(vsstring(lpnode->childs[ui]->GetAttrValue("type")) == "offline")
               {
                  g_bOfflineInstall = true;
                  g_strInstallGz = dir::path(lpnode->childs[ui]->GetAttrValue("src"), "stage.bz\\");
                  g_strInstall = dir::path(lpnode->childs[ui]->GetAttrValue("src"), "stage\\");
               }
               else if(vsstring(lpnode->childs[ui]->GetAttrValue("type")) == "online")
               {
                  g_bOfflineInstall = false;
                  g_bInstallSet = true;
                  g_strInstallGz = lpnode->childs[ui]->GetAttrValue("src");
                  g_strInstall = lpnode->childs[ui]->GetAttrValue("src");
               }
            }
         }
      }
   }
}



vsstring load_string(const char * pszId, const char * pszDefault)
{
   LPXNode lpnode = &g_nodeStringTable;
   for(unsigned int ui = 0; ui < lpnode->childs.get_count(); ui++)
   {
      if(vsstring(lpnode->childs[ui]->GetAttrValue("id")) == pszId)
      {
         return lpnode->childs[ui]->value;
      }
   }
   return pszDefault;
}

void ParseIndexFile(const char * psz, simple_string_to_intptr & mapLen, simple_string_to_string & mapMd5, simple_string_to_intptr & mapGzLen)
{
   FILE * f = fopen(psz, "rb");
   char * pszFind1;
   char * pszFind2;
   char * pszFind3;
   char buf[16 * 1024];
   while(fgets(buf, sizeof(buf), f))
   {
      while(buf[strlen_dup(buf) - 1] == '\r' || buf[strlen_dup(buf) - 1] == '\n')
      {
         buf[strlen_dup(buf) - 1] = '\0';
      }
      pszFind1 = strstr(buf, ",");
      pszFind2 = NULL;
      pszFind3 = NULL;
      if(pszFind1 != NULL)
      {
         pszFind2 = strstr(pszFind1 + 1, ",");
         if(pszFind2 != NULL)
         {
            pszFind3 = strstr(pszFind2 + 1, ",");
         }
      }
      if(pszFind1 != NULL)
      {
         *pszFind1 = '\0';
         pszFind1++;
      }
      if(pszFind2 != NULL)
      {
         *pszFind2 = '\0';
         pszFind2++;
      }
      if(pszFind3 != NULL)
      {
         *pszFind3 = '\0';
         pszFind3++;
      }
      vsstring strSpa;
      vsstring str2;
      strSpa = g_strInstall;
      strSpa += buf;
      if(pszFind1 != NULL)
      {
         g_iProgressMode = 0;
         mapLen[(vsstring)(const char *) buf] = atoi(pszFind1);
      }
      else
         mapLen[(vsstring)(const char *) buf] = -1;
      if(pszFind2 != NULL)
      {
         mapMd5[(vsstring)(const char *) buf] = pszFind2;
      }
      else
         mapMd5[(vsstring)(const char *) buf] = "";
      if(pszFind3 != NULL)
      {
         mapGzLen[(vsstring)(const char *) buf] = atoi(pszFind3);
      }
      else
         mapGzLen[(vsstring)(const char *) buf] = -1;
   }
   fclose(f);
}




bool spa_exec(const char * psz)
{
   vsstring strExec(psz);
   if(strExec.substr(0, 15) == "install_service")
   {
      vsstring strStage;
      strStage = dir::path(dir::beforeca2(),strExec.substr(16));
      ::ShellExecute(g_hwnd, "open", strStage, " : remove usehostlogin", dir::name(strStage), SW_SHOWNORMAL);
      ::ShellExecute(g_hwnd, "open", strStage, " : install usehostlogin", dir::name(strStage), SW_SHOWNORMAL);
   }
   else if(strExec.substr(0, 10) == "install_ex")
   {
      vsstring strStage;
      vsstring str2 = strExec.substr(11);
      int iPos = str2.find(" ");
      vsstring str3 = str2.substr(iPos + 1);
      strStage = dir::path(dir::beforeca2(), "ca2");
      strStage = dir::path(strStage, str3);
      ::ShellExecute(g_hwnd, "open", strStage, (" : " + str2.substr(0, iPos) + " usehostlogin"), dir::name(strStage), SW_SHOWNORMAL);
   }
   return true;
}




bool is_application_opened(const char * psz)
{

/*   SECURITY_ATTRIBUTES MutexAttributes;
   ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
   MutexAttributes.nLength = sizeof( MutexAttributes );
   MutexAttributes.bInheritHandle = FALSE; // object uninheritable
   // declare and initialize a security descriptor
   SECURITY_DESCRIPTOR SD;
   BOOL bInitOk = InitializeSecurityDescriptor(
                     &SD,
                     SECURITY_DESCRIPTOR_REVISION );
   if ( bInitOk )
   {
      // give the security descriptor a Null Dacl
      // done using the  "TRUE, (PACL)NULL" here
      BOOL bSetOk = SetSecurityDescriptorDacl( &SD,
                                            TRUE,
                                            (PACL)NULL,
                                            FALSE );
      if ( bSetOk )
      {*/
         // Make the security attributes point
         // to the security descriptor
         //MutexAttributes.lpSecurityDescriptor = &SD;
         vsstring strMutex;
         strMutex = "Global\\ca2_fontopus_votagus_application_global_mutex:";
         strMutex += psz;
         //HANDLE hmutex = ::CreateMutex(&MutexAttributes, FALSE, strMutex);
         HANDLE hmutex = ::CreateMutex(NULL, FALSE, strMutex);
         bool bOpened = ::GetLastError() == ERROR_ALREADY_EXISTS;
         if(bOpened)
         {
            vsstring strMessage;
            strMessage = psz;
            strMessage += "app.exe is still opened!";
            trace(strMessage);
            trace("You may finalize the process by:");
            trace("   1. Pressing CTRL+ALT+DEL;");
            trace("   2. Opening Task Manager, and;");
     strMessage = "   4. Closing the process ";
            strMessage += psz;
            strMessage += "app.exe.";
            trace(strMessage);
            trace(".");
         }
         ::CloseHandle(hmutex);
         return bOpened;
/*      }
      else
      {
         return false;
      }
   }
   else
   {
      return false;
   }
   */
}

bool is_there_application_opened()
{
   return 
      is_application_opened("winactionarea")
   || is_application_opened("winservice_1")
   || is_application_opened("winutil")
   || is_application_opened("winshelllink")
   || is_application_opened("command")
   || is_application_opened("winservice_filesystemsize")
   || is_application_opened("filemanager")
   || is_application_opened("mplite");
}

void machine_signalize_close_application()
{
   mutex_lock lockMachineEvent(&g_machineevent.m_mutex);
   machine_event_data data;
   g_machineevent.read(&data);
   data.m_fixed.m_bRequestCloseApplication = true;
   g_machineevent.write(&data);
}

bool machine_unsignalize_close_application()
{
   mutex_lock lockMachineEvent(&g_machineevent.m_mutex);
   machine_event_data data;
   g_machineevent.read(&data);
   data.m_fixed.m_bRequestCloseApplication = false;
   bool bOk = g_machineevent.write(&data);
   return bOk;
}

bool machine_check_close_application(bool bDefault)
{
   mutex_lock lockMachineEvent(&g_machineevent.m_mutex);
   machine_event_data data;
   if(!g_machineevent.read(&data))
      return false;
   return data.m_fixed.m_bRequestCloseApplication;
}

int stop_service()
{
   SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

	if (hdlSCM == 0) return ::GetLastError();
 
   SC_HANDLE hdlServ = ::OpenService(
		hdlSCM,                    // SCManager database 
		"core_WinService_Spa_stage",               // name of service 
		SC_MANAGER_ALL_ACCESS);                     // no password 
 
   DWORD Ret = 0;
   if (!hdlServ) 
   {
      Ret = ::GetLastError();
      return Ret;
   }
   SERVICE_STATUS ss;
   memset(&ss, 0, sizeof(ss));
   ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss);

   CloseServiceHandle(hdlServ);

   return Ret;
}


int remove_service()
{
	SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

	if (hdlSCM == 0) return ::GetLastError();
 
   SC_HANDLE hdlServ = ::OpenService(
		hdlSCM,                    // SCManager database 
		"core_WinService_Spa_stage",               // name of service 
		SC_MANAGER_ALL_ACCESS);                     // no password 
 
   DWORD Ret = 0;
   if (!hdlServ)
   {
      Ret = ::GetLastError();
      return Ret;
   }

   ::DeleteService(hdlServ);

   CloseServiceHandle(hdlServ);

/*   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   LPSTR lpsz = _strdup(("sc delete core_WinService_Spa_" + g_strVersionShift));
   if(!::CreateProcess(NULL, lpsz, 
      NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
      return 1;
   free(lpsz);*/

   return Ret;
}




bool m_reboot()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
	if (ExitWindowsEx(EWX_REBOOT, 0) == 0)
		return false;
	//reset the previlages
	tkp.Privileges[0].Attributes = 0;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
   return true;
}


int ca2_app_install_run(const char * psz, const char * pszParam1, const char * pszParam2, DWORD & dwStartError, bool bSynch)
{
   vsstring strStage;
   vsstring strApp;
   vsstring strUrl;

   vsstring strParam1;
   vsstring strParam2;
   
   if(pszParam1 != NULL)
   {
      strParam1 = pszParam1;
      strParam1.trim();
   }

   if(pszParam2 != NULL)
   {
      strParam2 = pszParam2;
      strParam2.trim();
   }

   vsstring strPlatform = spa_get_platform();
   if(vsstring(psz) == "_set_windesk")
   {
      strStage = dir::path(dir::beforeca2(), ("ca2\\stage\\" + strPlatform + "\\cubeapp.exe"));
      if(strParam1.length() > 0)
      {
         strStage += " " + strParam1;
      }
      strStage += " : app=winservice_1";
      strStage += psz;
      if(strParam2.length() > 0)
      {
         strStage += " ";
         strStage += strParam2;
      }
   }
   else
   {

      strStage = dir::path(dir::beforeca2(), ("ca2\\stage\\" + strPlatform + "\\cubeapp.exe"));

      if(strParam1.length() > 0)
      {
         strStage += " " + strParam1;
      }
      strStage += " : app=bergedge bergedge_start=";
      strStage += psz;
      if(strParam2.length() > 0)
      {
         strStage += " " + strParam2;
      }
   }
//   vsstring strParam;
//   strParam = "start=" + file_name_dup(strUrl);

   STARTUPINFO si;
   memset(&si, 0, sizeof(si));
   si.cb = sizeof(si);
   si.dwFlags = STARTF_USESHOWWINDOW;
   si.wShowWindow = SW_SHOWNORMAL;
   PROCESS_INFORMATION pi;
   memset(&pi, 0, sizeof(pi));
//   DWORD dwError;
   LPSTR lpCommand = _strdup(strStage);
   
   if(!::CreateProcess(NULL, lpCommand, 
                      NULL, NULL, FALSE, 0, NULL, NULL,
                      &si, &pi))
                      return 1;
   dwStartError = ::GetLastError();
   free(lpCommand);
   if(bSynch)
   {
      trace(".");
      DWORD dwExitCode;
      int iRetry = 0;
      while(true)
      {
         if(!GetExitCodeProcess(pi.hProcess, &dwExitCode))
            break;
         if(dwExitCode != STILL_ACTIVE)
            break;
         iRetry++;
         Sleep(484);
         if((iRetry % 33) == 0)
         {
            trace(".");
         }
         else
         {
            trace_add(".");
         }
      }
   }
   return 0;
}

bool ignit_phase2()
{

   

   char szFormat[256];
   vsstring strUrl;
   strUrl = "http://spaignition.api.veriterse.net/query?node=install_application&id=";
   strUrl += g_strStart;
   strUrl += "&key=post_install_count";
   vsstring strCount = ms_get_dup(strUrl);
   int iCount = atoi(strCount);
   for(int i = 0; i < iCount; i++)
   {
      strUrl = "http://spaignition.api.veriterse.net/query?node=install_application&id=";
      strUrl += g_strStart;
      strUrl += "&key=post_install";
      sprintf(szFormat, "[%d]", i);
      strUrl += szFormat;
      vsstring strExec = ms_get_dup(strUrl);
      if(!spa_exec(strExec))
      {
         ::MessageBox(g_hwnd, "Error", "Error", MB_OK);
      }
   }

   DWORD dwStartError;
   trace("starting app-install...");
   int i = ca2_app_install_run(g_strStart, "", "install", dwStartError, true);
   if(g_strStart != "_set_windesk" && is_installed("_set_windesk"))
   {
      DWORD dwStartError2;
      trace("starting windeskPackage...");
      int i2 = ca2_app_install_run("_set_windesk", "", "", dwStartError2, false);
      trace("started windeskPackage");
   }
   trace(".");
   
   vsstring strPlatform = spa_get_platform();
   if(i == 0)
   {
      file_put_contents_dup((dir::ca2() + "\\appdata\\" + strPlatform + "\\build.txt"), g_strBuild);
      ::PostMessage(g_hwnd, WM_CLOSE, 0, 0);
      return true;
   }
   else
   {
      DWORD dwError = dwStartError;
      trace("");
      trace("");
      trace("");
      trace("");
      trace("");
      trace("Failed to install");
      trace("Manually contact mailto:support.veriwell@ca2mail.com");
      trace("or Manually go to http://votagus.com/");
      trace("");
      trace("In votagus.com you can try to");
      trace("download the most recent release version for installation");
      trace("(Automatic links not availabe by now)");
      trace("");
      trace("");
      trace("");
      trace("");
      trace("");
      return false;
   }
}


int run_uninstall(const char * lpCmdLine, int nCmdShow)
{
   return run_install(lpCmdLine, nCmdShow);
}

int run_uninstall_run(const char * lpCmdLine, int nCmdShow)
{
   DWORD dwStartError = 0;
   return ca2_app_install_run(lpCmdLine, "", "uninstall", dwStartError, true);
}

int run_install(const char * lpCmdLine, int nCmdShow)
{
   vsstring str = lpCmdLine;
   vsstring strFile = lpCmdLine;

   int i1 = str.find("\"");
   if(i1 >= 0)
   {
      int i2 =str.find("\"", i1 +1);
      strFile = str.substr(i1 + 1, i2 - i1 - 1);
   }
   else
   {
      strFile = str;
   }

   if(strFile.is_empty())
   {
      strFile = dir::path(dir::module_folder(), "spa.xml");
   }

	return run_file(strFile, nCmdShow);
}

int run_file(const char * pszFile, int nCmdShow)
{

   g_strFile = pszFile;

//	MSG msg;
//	HACCEL hAccelTable;
  


   XNode node;

   //MessageBox(NULL, "BegInstall", "Caption", MB_OK);
   if(g_iStart != 4)
   {
      vsstring strCa2sp = file_get_contents_dup(g_strFile);
      if(strCa2sp.length() == 0)
      {
         strCa2sp = read_resource_as_string(NULL, 1984, "CA2SP");
      }
      if(strCa2sp.length() > 0)
      {
         node.Load(strCa2sp);
         ParseSpaIndex(node);
      }
      else
      {
         g_strStart = "bergedge";
      }
   }



/*
   char * pszStart = strstr(lpCmdLine, "start=");
   char * pszEnd = NULL;
   if(pszStart != NULL)
   {
      pszStart += strlen_dup("start=");
      pszEnd = pszStart;
      while(isdigit(*pszEnd) || isalpha(*pszEnd))
      {
         pszEnd++;
      }
      g_strStart = vsstring(pszStart, pszEnd - pszStart);
   }
   else
   {
      g_strStart = "bergedge";
   }*/

//   char * pszStart;
   char * pszEnd = NULL;
   char * lpCmdLine = ::GetCommandLine();
   char * pszLocale = strstr((char *) lpCmdLine, "locale=");
   if(pszLocale != NULL)
   {
      pszLocale += strlen_dup("locale=");
      pszEnd = pszLocale;
      while(isdigit(*pszEnd) || isalpha(*pszEnd))
      {
         pszEnd++;
      }
      g_strLocale = vsstring(pszLocale, pszEnd - pszLocale);
   }
   else
   {
      g_strLocale = "";
   }

   return run_spa(nCmdShow);
}

int starter_start(const char * pszId)
{

   g_strStart  = pszId;

   g_bOfflineInstall = false;

   g_strInstallGz = "http://ccvotagus.net/stage/";

   g_strInstall = "http://ccvotagus.net/stage/";

   g_bForceUpdatedBuild = true;

   g_bStarterStart = true;

   return run_spa(SW_HIDE);

}

vsstring url_query_param(int & iParam, const char * pszParam)
{
   vsstring str;
   if(iParam == 0)
   {
      iParam++;
      str = "?";
      return str + pszParam;
   }
   else
   {
      iParam++;
      str = "&";
      return str + pszParam;
   }
}

Lang g_langa[] =
{ 
   { ID_LANG_SV, "sv" },
   { ID_LANG_PTBR, "pt-br" },
   { ID_LANG_ENINTL, "pt-enintl" },
   { ID_LANG_JA, "ja" },
   { -1, ""},
};


int LangFromOS()
{
   LANGID id = GetUserDefaultUILanguage();
   if(id == MAKELANGID(LANG_SWEDISH, SUBLANG_SWEDISH))
   {
      return ID_LANG_SV;
   }
   else if(id == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
   {
      return ID_LANG_PTBR;
   }
   else if(id == MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN))
   {
      return ID_LANG_JA;
   }
   else
   {
      return ID_LANG_ENINTL;
   }

}



void add_spa_start(const char * pszId)
{
	vsstring strPath = dir::appdata("spa_start.xml");
	vsstring strContents = file_get_contents_dup(strPath);
   XNode node;
   node.Load(strContents);
   node.name = "spa";
   LPXNode lpnode = node.GetChildByAttr("start", "id", pszId);
   if(lpnode == NULL)
   {
	   lpnode = node.AppendChild("start");
	   lpnode->AppendAttr("id", pszId);
	   file_put_contents_dup(strPath, node.GetXML());
   }
}

void remove_spa_start(const char * pszId)
{
	vsstring strPath = dir::appdata("spa_start.xml");
	vsstring strContents = file_get_contents_dup(strPath);
   XNode node;
   node.Load(strContents);
   node.name = "spa";
   LPXNode lpnode = node.GetChildByAttr("start", "id", pszId);
   if(lpnode != NULL)
   {
	   node.RemoveChild(lpnode);
	   file_put_contents_dup(strPath, node.GetXML());
   }
}



vsstring install(const char * psz)
{
   return g_strInstall + psz;
}





SPALIB_API void reg_delete_tree(HKEY hkey, const char * name)
{
   HKEY hkeySub = NULL;
   if(ERROR_SUCCESS == ::RegOpenKey(
      hkey,
      name,
      &hkeySub))
   {
      DWORD dwAlloc = 1026 * 64;
      char * szKey = new char[dwAlloc];
      DWORD dwIndex = 0;
      while(ERROR_SUCCESS == ::RegEnumKey(hkeySub, dwIndex, szKey, dwAlloc))
      {
         reg_delete_tree(hkeySub, szKey);
         dwIndex++;
      }
      delete szKey;
      ::RegCloseKey(hkeySub);
   }
   ::RegDeleteKey(hkey, name);
}




SPALIB_API vsstring spalib_get_build()
{
   return read_resource_as_string(::GetModuleHandleA("spalib.dll"), ID_CGCL, "CA2SP");
}



void DragMainWindow()
{
   POINT ptCursor;
   ::GetCursorPos(&ptCursor);
   ::SetWindowPos(g_hwnd, NULL, 
      ptCursor.x - g_ptDragStart.x + g_rectWindowDragStart.left,
      ptCursor.y - g_ptDragStart.y + g_rectWindowDragStart.top,
      0, 
      0,
      SWP_NOSIZE | SWP_SHOWWINDOW);
   if(g_iStyle == 0)
   {
   }
   else
   {
      ::SetLayeredWindowAttributes(g_hwnd, 0, (255 * 100) / 100, LWA_ALPHA);
   }
   ::RedrawWindow(g_hwnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
}


void spa_file_transfer()
{
   Spa();
}


void spa()
{
   spa_file_transfer();
}
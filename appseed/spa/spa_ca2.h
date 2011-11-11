#pragma once


#include "spares/resource.h"






SPALIB_API vsstring spalib_get_build();

extern int g_cx;
extern int g_cy;
extern HWND g_hwnd;



#define TIMER_CARET 123454
#define TIMER_ANIMATION 1234508
#define CARET_TIME 1000

extern HINSTANCE hInst;								// current instance
extern vsstring g_strStart;
extern vsstring g_strInstallFilter;
extern stra_dup g_straTerminateProcesses;
extern stra_dup g_straRestartCommandLine;
extern bool g_bSpaUpdate;


vsstring url_query_param(int & iParam, const char * pszParam);


vsstring load_string(const char * pszId, const char * pszDefault);

void CommandStart();

//SPALIB_API bool is_installed(const char * psz);

int LangFromOS();

class Lang
{
public:
   int            m_iCommand;
   vsstring    m_strCode;
};


extern Lang g_langa[];

void add_spa_start(const char * pszId);
void remove_spa_start(const char * pszId);

extern bool g_bInstalling;

//extern HINTERNET  g_hSession;
extern vsstring g_strHost;
extern DWORD g_dwInstallStartTime;
extern vsstring g_strBuild;
extern vsstring g_strBuildResource;
extern HINSTANCE g_hinstance;
extern bool g_bShowPercentage;
extern MSG g_msg;
extern bool g_bShow;







#ifdef WIN32
//void config_session_proxy(HINTERNET hSession, WCHAR * pwzUrl);



BOOL AfxInternalPumpMessage();

//SPALIB_API WCHAR * utf8_to_16(const char * psz);
vsstring ms_post(const char * pszUrl, const char * pszPost);
#endif


extern machine_event g_machineevent;

extern bool machine_unsignalize_close_application();
extern bool machine_check_close_application(bool bDefault);
extern bool g_NeedRestartBecauseOfReservedFile;
extern bool g_NeedRestartFatalError;
extern bool g_bLoginStartup;
extern bool g_bMsDownload;
extern vsstring g_strTitle;
extern DWORD g_dwDownloadLen;
extern DWORD g_dwCurFileLen;
bool m_reboot();
bool ignit_phase2();
int run_uninstall(const char * lpCmdLine, int nCmdShow);
int run_install(const char * lpCmdLine, int nCmdShow);
bool spa_exec(const char * psz);
vsstring load_string(const char * pszId, const char * pszDefault);
SPALIB_API vsstring str_replace(const char * psz, const char * pszFind, const char * pszReplace);
bool is_there_application_opened();
bool is_application_opened(const char * psz);
void machine_signalize_close_application();
SPALIB_API vsstring read_resource_as_string(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);


wchar_t * wfy(const char * pszUtf8);


void wfree(wchar_t * push);

//SPALIB_API int bzuncompress(LPCTSTR lpcszUncompressed, LPCTSTR lpcszGzFileCompressed);

int CopyFileList(stra_dup & stra);

vsstring ca2_get_dir(LPCTSTR lpcszUrl);
vsstring ca2bz_get_dir(LPCTSTR lpcszUrl);
vsstring ca2unbz_get_dir(LPCTSTR lpcszUrl);
vsstring ca2_get_file(LPCTSTR lpcszUrl);
vsstring ca2bz_get_file(LPCTSTR lpcszUrl, const char * pszMd5);
vsstring ca2unbz_get_file(LPCTSTR lpcszUrl);
//bool ca2_fy_url(vsstring & str, LPCTSTR lpcszUrl, bool bExist, int iLength, const char * pszMd5, int iGzLen, bool bIndex = false);


extern int g_iScreen;
extern int g_iProgressMode;
extern int g_iTotalGzLen;
extern int g_iGzLen;
extern int g_iStyle;

extern simple_mutex g_mutexTrace;
extern stra_dup g_strSpa;
extern stra_dup g_straHost;

extern bool g_bOfflineInstall;
extern bool g_bInternetInstall;
extern vsstring g_strIndex;
extern vsstring g_strIndexGz;
extern vsstring g_strInstall;
extern vsstring g_strInstallGz;

extern bool g_bInstallSet;
extern _FILE * g_ftrace;


extern bool Get(const vsstring& url_in, vsstring & doc);
extern bool Get(const vsstring& url_in, bool bExist, int iLength, const char * pszMd5, int iGzLen);
extern bool DownloadFile(const vsstring& url_in, bool bExist, int iLength, const char * pszMd5, int iGzLen);
extern int GetFileList(stra_dup & stra, LPCTSTR lpcszUrl, simple_string_to_intptr & mapLen, simple_string_to_intptr & mapGzLen, simple_string_to_string & mapMd5);
extern int GetLocalFileList(stra_dup & stra, LPCTSTR lpcszUrl);
extern int DownloadFileList(stra_dup & stra, simple_string_to_intptr & mapLen, simple_string_to_string & mapMd5, simple_string_to_intptr & mapGzLen);
extern void ParseIndexFile(const char * psz, simple_string_to_intptr & mapLen, simple_string_to_string & mapMd5, simple_string_to_intptr & mapGzLen);
extern int UncompressFileList(stra_dup & stra, simple_string_to_string & strmapMd5);
extern void ParseSpaIndex(XNode & node);
extern void CommandLang(int iLang);
extern vsstring Login();


extern double g_dProgress;
extern double g_dProgress1;
extern double g_dProgress2;
extern XNode g_nodeStringTable;
extern int g_iStart;
extern simple_double_array g_daDownloadRate;
extern DWORD g_dwDownloadTick;
extern DWORD g_dwDownload;
extern int g_iDownloadRate;
extern double g_dDownloadRate;
extern DWORD g_dwDownloadZeroRateTick;
extern DWORD g_dwDownloadZeroRateRemain;
extern DWORD g_dwDownloadRemain;




void trace(const char * psz);



vsstring install(const char * psz);

SPALIB_API  vsstring get_temp_file_name(const char * pszName, const char * pszExtension);

void trace_add(const char * psz);

SPALIB_API  int spalib_main(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow);


extern simple_mutex g_mutexTrace;
extern stra_dup g_straTrace;
extern stra_dup g_strSpa;
extern stra_dup g_straHost;
extern int g_iTrace;
extern _FILE * g_ftrace;
extern bool g_bForceUpdatedBuild;
extern bool g_bStarterStart;
extern int g_iHealingSurface;

/*SPALIB_API void prepare_small_bell();
SPALIB_API void play_small_bell();
SPALIB_API void defer_play_small_bell();

SPALIB_API void reg_delete_tree(HKEY hkey, const char * name);*/

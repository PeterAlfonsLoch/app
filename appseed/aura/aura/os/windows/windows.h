#pragma once


#include <shellapi.h>
#include <wincrypt.h>



#include "windows_base_file.h"
#include "windows_multithreading.h"
#include "windows_utils.h"

char get_drive_letter(const char * lpDevicePath);

CLASS_DECL_AURA void set_main_thread(HANDLE hThread);
CLASS_DECL_AURA void set_main_thread_id(UINT uiThread);


CLASS_DECL_AURA HANDLE get_main_thread();
CLASS_DECL_AURA UINT   get_main_thread_id();

#ifdef __cplusplus

CLASS_DECL_AURA string get_command_line(HANDLE handleProcess);

CLASS_DECL_AURA string get_display_error(uint32_t NTStatusMessage);

CLASS_DECL_AURA void attach_thread_input_to_main_thread(bool bAttach = true);

#endif


#ifdef __cplusplus

CLASS_DECL_AURA string key_to_char(WPARAM wparam, LPARAM lparam);
CLASS_DECL_AURA string read_resource_as_string_dup(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);

#endif

#define MESSAGE MSG
#define LPMESSAGE LPMSG


CLASS_DECL_AURA int WinRegGetValueW(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);

#ifdef __cplusplus

#include "windows_comptr.h"

#endif

#include "windows.inl"









CLASS_DECL_AURA HFONT wingdi_CreatePointFont(int nPointSize, const char * lpszFaceName, HDC hdc, LOGFONTW* lpLogFont = NULL);

CLASS_DECL_AURA HFONT wingdi_CreatePointFontIndirect(LOGFONTW* lpLogFont, HDC hdc);



#ifdef cplusplus

#define LOG_THIS_TAG (typeid(*this).name())
#define LOG_MEMBER_PREFIX __FUNCTION__

#endif


CLASS_DECL_AURA int node_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow);
CLASS_DECL_AURA int node_main(int argc, char *argv[]);





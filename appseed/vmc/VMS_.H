#pragma once

typedef long VMSRESULT;

typedef struct tagVMSNMHDR {
    HWND hwndFrom;
    UINT idFrom;
    UINT code;
} VMSNMHDR;

typedef struct tagE17_KEYDOWN {
    VMSNMHDR hdr;   
    WORD wVKey;  
    UINT flags;  
} E17_KEYDOWN;

typedef struct tagE17_SYSKEYDOWN {
    VMSNMHDR hdr;   
    WORD wVKey;  
    UINT flags;  
} E17_SYSKEYDOWN;


#define VMSM_NOTIFY WM_USER + 1117
#define VMSM_TIMER WM_USER + 1119

#define E17N_KEYDOWN 17
#define E17N_SYSKEYDOWN 19
#define E17N_ESCAPE 1
#define E17N_RETURN 0

#define VMS_FAILED(Status) ((VMSRESULT)(Status)<0)
#define VMS_SUCCEEDED(Status) ((VMSRESULT)(Status)>=0)

#define VMSR_SUCCESS          0
#define VMSR_S_NOTFOUND       2000
#define VMSR_S_ENDOFFILE     3000
#define VMSR_S_SKIP         4000
#define VMSR_E_FAIL          -1
#define VMSR_E_NOMEMORY    -13
#define VMSR_E_INVALIDFILE    -15

#define VMS_DOC_VERSION_1    1

#define VMS_EVENT_NULL 0
#define VMS_EVENT_MIDI 1
#define VMS_EVENT_MIDI_DELETED 2
#define VMS_EVENT_SYMBOL 3
#define VMS_EVENT_SYMBOL_DELETED 4


#define FOURCC_MShd     mmioFOURCC('M','S','h','d')
#define FOURCC_MStk     mmioFOURCC('M','S','t','k')

#define APP_MAX_STRING_ERROR_CHARS      512
#define APP_MAX_STRING_ERROR_BYTES      (APP_MAX_STRING_ERROR_CHARS * sizeof(TCHAR))

#define VMSM_EXCEPTION WM_USER + 1000
#define EXCEPTION_OLEDB 1000

#define VMSM_RENDER_RECT    WM_USER + 2000
#define VMSM_RENDER_RGN     WM_USER + 2001

#define VMSM_ECONOMODECHANGE WM_USER + 2002

#define VMSM_V001 WM_USER + 1001
#define NOTIFY_BUILDALBUMPROGRESSUPDATE 1000
#define NOTIFY_BUILDALBUMSTATUSUPDATE 1001
#define NOTIFY_BUILDALBUMTASKSUPDATE 1002
#define NOTIFY_BUILDALBUMDELETE 1003
#define NOTIFY_BUILDALBUMFINISHED 1010
#define NOTIFY_TIMERCALLBACKCREATETIMER 1104
#define NOTIFY_TIMERCALLBACKDELETETIMER 1105
#define NOTIFY_CLOSE 1106
#define NOTIFY_BUILDALBUMONHIDETASKDIALOG 120

#define VMSC_BRINGTOTOP 1000

class CTimerCallback;





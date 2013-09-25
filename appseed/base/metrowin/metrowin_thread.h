#pragma once







/*
 * Message structure
 */
typedef struct tagMESSAGE {
    oswindow    oswindow;
    UINT        message;
    WPARAM      wParam;
    LPARAM      lParam;
    DWORD       time;
    POINT       pt;
#ifdef _MAC
    DWORD       lPrivate;
#endif
} MESSAGE, *PMESSAGE, NEAR *NPMESSAGE, FAR *LPMESSAGE;




CLASS_DECL_c WINBOOL WINAPI GetMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);

#define GetMessage GetMessageW

CLASS_DECL_c WINBOOL WINAPI PeekMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax,UINT wRemoveMsg);

#define PeekMessage PeekMessageW

CLASS_DECL_c DWORD WINAPI get_thread_id(HTHREAD Thread);

#define PostThreadMessage  PostThreadMessageW

CLASS_DECL_c WINBOOL WINAPI PostThreadMessageW(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam);

#define PostMessage  PostMessageW

CLASS_DECL_c WINBOOL WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam);

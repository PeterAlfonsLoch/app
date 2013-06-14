#pragma once


class CLASS_DECL_c message_array :
   public simple_array < MESSAGE >
{
};

class CLASS_DECL_c mq
{
public:


   simple_mutex               m_mutex;
   message_array              ma;
   simple_event               m_eventNewMessage;
   HTHREAD                    m_hthread;
   uint32_t                   m_uiId;


   mq() : m_eventNewMessage(false, true) {}



};

CLASS_DECL_c mq * get_mq(HTHREAD h);

CLASS_DECL_c WINBOOL WINAPI GetMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);

#define GetMessage GetMessageW

CLASS_DECL_c WINBOOL WINAPI PeekMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax,UINT wRemoveMsg);

#define PeekMessage PeekMessageW

CLASS_DECL_c DWORD WINAPI GetThreadId(HTHREAD Thread);

#define PostThreadMessage  PostThreadMessageW

CLASS_DECL_c WINBOOL WINAPI PostThreadMessageW(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam);

#define PostMessage  PostMessageW

CLASS_DECL_c WINBOOL WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam);


CLASS_DECL_c HTHREAD GetCurrentThread();

CLASS_DECL_c UINT GetCurrentThreadId();


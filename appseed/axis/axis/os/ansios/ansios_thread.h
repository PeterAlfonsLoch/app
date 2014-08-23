#ifndef AXIS_ANSIOS_THREAD_H
#define AXIS_ANSIOS_THREAD_H


#pragma once


/*class hthread :
    virtual public root
{
public:


   event               * m_pevent;
   ::thread          * m_pthread;
   os_thread                  * m_posthread;


   hthread();
   virtual ~hthread();


   void wait();


};
 */




class thread;

class CLASS_DECL_AURA message_array :
public array < MESSAGE > {
};

class CLASS_DECL_AURA mq {
public:


    mutex m_mutex;
    message_array ma;
    manual_reset_event m_eventNewMessage;
    HTHREAD m_hthread;
    uint32_t m_uiId;


    mq();



};

CLASS_DECL_AURA mq * get_mq(HTHREAD h);

CLASS_DECL_AURA int_bool WINAPI GetMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);

#define GetMessage GetMessageW

CLASS_DECL_AURA int_bool WINAPI PeekMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

#define PeekMessage PeekMessageW

CLASS_DECL_AURA DWORD WINAPI GetThreadId(HTHREAD Thread);

#define PostThreadMessage  PostThreadMessageW

CLASS_DECL_AURA int_bool WINAPI PostThreadMessageW(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam);

#define PostMessage  PostMessageW

CLASS_DECL_AURA int_bool WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam);


CLASS_DECL_AURA HTHREAD GetCurrentThread();

CLASS_DECL_AURA UINT GetCurrentThreadId();

CLASS_DECL_AURA void thread_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);

CLASS_DECL_AURA int32_t thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);

CLASS_DECL_AURA void process_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);

CLASS_DECL_AURA int32_t process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);



// Stored data for CREATE_SUSPENDED and ResumeThread.

struct PendingThreadInfo {
    DWORD(WINAPI * lpStartAddress)(LPVOID);
    LPVOID lpParameter;
    HTHREAD m_hthread;
    event * suspensionEvent;
    int32_t nPriority;
    int32_t cbStack;

    PendingThreadInfo() {
    }

};


#endif // AXIS_ANSIOS_THREAD_H











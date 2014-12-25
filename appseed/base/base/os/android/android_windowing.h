#pragma once


namespace boot
{


   class thread_base;
   class interaction_impl;


} // namespace boot




typedef ptr_array < oswindow_data > oswindow_dataptra;










// define portable types for 32-bit / 64-bit OS
//typedef int32_t WINBOOL;
typedef uint8_t BYTE;
//typedef uint16_t WORD;
typedef uint32_t DWORD;
//typedef int32_t LONG;


#undef FAR
#undef  NEAR
#define FAR
#define NEAR
#ifndef CONST
#define CONST               const
#endif


#ifdef __cplusplus



struct hthread;

namespace ca2
{


   class thread_base;


} // namespace ca2


//class oswindow_data;


//typedef oswindow_data * oswindow;





//class oswindow_dataptra;


class event;


class mutex;


//typedef hthread * HTHREAD;


class oswindow_data;






bool IsChild(oswindow oswindowParent,::oswindow oswindowcandidateChildOrDescendant);
oswindow GetParent(::oswindow oswindow);
oswindow SetParent(::oswindow oswindow,::oswindow oswindowNewParent);
bool ShowWindow(::oswindow oswindow,int32_t nCmdShow);
LONG GetWindowLongA(::oswindow oswindow,int32_t nIndex);
LONG SetWindowLongA(::oswindow oswindow,int32_t nIndex,LONG l);
bool ClientToScreen(::oswindow oswindow,LPPOINT lppoint);
bool ScreenToClient(::oswindow oswindow,LPPOINT lppoint);
int32_t IsIconic(::oswindow oswindow);
int32_t IsWindowVisible(::oswindow oswindow);
void on_post_nc_destroy(::oswindow oswindow);
bool is_message_only_window(::oswindow oswindow);

#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA



CLASS_DECL_AURA bool IsWindow(oswindow oswindow);


#endif

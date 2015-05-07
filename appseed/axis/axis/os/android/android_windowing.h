#pragma once


namespace boot
{


   class thread_base;
   class interaction_impl;


} // namespace boot


struct oswindow_data;


typedef ptr_array < oswindow_data > oswindow_dataptra;





namespace boot
{


   class thread_axis;
   class interaction_impl;


} // namespace boot


namespace user
{


   class interaction_axis;
   class interaction;


} // namespace user


typedef ptr_array < oswindow_data > oswindow_dataptra;

/*
* Copyright (C) 2010 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

struct CLASS_DECL_AXIS oswindow_data
{

#ifdef VSNORD

   engine                        m_engine;

#endif

   bool                          m_bMessageOnlyWindow;
   ::user::interaction *         m_pui;
   HTHREAD                       m_hthread;
   COLORREF *                    m_pcolorref;
   RECT                          m_rect;
   int_map < LONG > *            m_plongmap;
   bool                          m_bDestroying;
   bool                          m_bIconic;
   bool                          m_bVisible;


   static oswindow_dataptra * s_pdataptra;
   static mutex * s_pmutex;


   oswindow_data();
   oswindow_data(::user::interaction_axis * puiaxisMessageOnlyWindow);
   oswindow_data(const void * p);
   oswindow_data(const LPARAM & lparam);
   oswindow_data(const WPARAM & wparam);


   ~oswindow_data();



   operator void * ()
   {
      return this;
   }

   operator void * () const
   {
      return (void *) this;
   }

   oswindow_data & operator = (const oswindow_data & interaction_impl);

   bool operator == (const void * p) const
   {
      return this == p;
   }

   bool operator != (const void * p) const
   {
      return this != p;
   }


   int32_t store_name(const char * psz);
   int32_t select_input(int32_t iInput);
   int32_t select_all_input();
   int32_t map_window();

   void set_user_interaction(::user::interaction * pui);
   ::user::interaction * get_user_interaction();
   ::user::interaction * get_user_interaction() const;


   void post_nc_destroy();


   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow GetParent();
   oswindow SetParent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool ShowWindow(int nCmdShow);
   LONG get_window_long(int32_t nIndex);
   LONG set_window_long(int32_t nIndex, LONG l);
   bool ClientToScreen(LPPOINT lppoint);
   bool ScreenToClient(LPPOINT lppoint);



   bool is_null() const
   {
      return this == NULL;
   }


   bool is_destroying();


};













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


struct oswindow_data;






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

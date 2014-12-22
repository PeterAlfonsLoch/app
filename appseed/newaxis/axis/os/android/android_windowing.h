#pragma once


namespace boot
{


   class thread_base;
   class interaction_impl;


} // namespace boot


namespace user
{


   class interaction_base;
   class interaction;


} // namespace user


typedef ptr_array < oswindow_data > oswindow_dataptra;



struct CLASS_DECL_AXIS oswindow_data
{


   bool                          m_bMessageOnlyWindow;
   ::user::interaction *         m_pui;
   HTHREAD                       m_hthread;
   COLORREF *                    m_pcolorref;
   RECT                          m_rect;
   int_map < LONG > *            m_plongmap;
   bool                          m_bDestroying;
   bool                          m_bVisible;
   bool                          m_bIconic;


   static oswindow_dataptra * s_pdataptra;
   static mutex * s_pmutex;


   oswindow_data();
   oswindow_data(::user::interaction_base * puibaseMessageOnlyWindow);
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







#pragma once


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



namespace user
{


   class interaction;
   class interaction;


} // namespace user


//class oswindow_dataptra;


class event;


class mutex;


//typedef hthread * HTHREAD;


class oswindow_data;


CLASS_DECL_AURA int32_t oswindow_find_message_only_window(::user::interaction * puibaseMessageWindow);
//CLASS_DECL_AURA int32_t oswindow_find(Display * pdisplay,Window window);
//CLASS_DECL_AURA int32_t oswindow_find(Window window);
CLASS_DECL_AURA oswindow_data * oswindow_get_message_only_window(::user::interaction * puibaseMessageWindow);
//CLASS_DECL_AURA oswindow_data * oswindow_get(Display * pdisplay,Window window,Visual * pvisual = NULL,int iDepth = -1,int iScreen = -1,Colormap colormap = None);
//CLASS_DECL_AURA oswindow_data * oswindow_get(Window window);
//CLASS_DECL_AURA oswindow oswindow_defer_get(Window w);
//CLASS_DECL_AURA bool oswindow_remove(Display * pdisplay,Window window);
CLASS_DECL_AURA bool oswindow_remove_message_only_window(::user::interaction * puibaseMessageOnlyWindow);




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


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA



CLASS_DECL_AURA bool IsWindow(oswindow oswindow);


#endif

//
//  macos_window.h
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once


#ifndef __MM

struct NSWindow;

#endif


typedef NSWindow * nswindow;


namespace user
{
   
   
   class base_interaction;
   class interaction;
   
   
} // namespace user


class CLASS_DECL_c oswindow_data
{
public:
   
   
   nswindow                      m_nswindow;
   ::user::base_interaction *    m_pui;
   
   
   static oswindow_dataptra *    s_pdataptra;
   simple_long_map *             m_plongmap;
   
   
   oswindow_data();
   oswindow_data(nswindow window);
   oswindow_data(const oswindow_data & oswindow);
   ~oswindow_data();
   
   
   operator void * ()
   {
      
      return this;
      
   }
   
   operator void * () const
   {
      
      return (void *) this;
      
   }
   
#ifdef __MM
   
   operator ::nswindow ()
   {
      return window();
   }
   
#endif
   
   oswindow_data & operator = (const oswindow_data & window);
   
   bool operator == (const void * p) const
   {
      return this == p;
   }
   bool operator != (const void * p) const
   {
      return this != p;
   }
   
   nswindow window()
   {
      return this == NULL ? NULL : m_nswindow;
   }
   
   
   void set_user_interaction(::user::base_interaction * pui);
   ::user::base_interaction * get_user_interaction_base();
   ::user::base_interaction * get_user_interaction_base() const;
   ::user::interaction * get_user_interaction();
   ::user::interaction * get_user_interaction() const;
   
   
   void post_nc_destroy();
   
   
   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(int32_t nCmdShow);
   int32_t get_window_long(int32_t nIndex);
   int32_t set_window_long(int32_t nIndex, int32_t l);
   bool client_to_screen(POINT * lppoint);
   bool screen_to_client(POINT * lppoint);
   
   
   
   bool is_null() const
   {
      return this == NULL;
   }
   
};





int oswindow_find(nswindow window);
oswindow_data * oswindow_get(nswindow window);
bool oswindow_remove(nswindow window);


inline int IsWindow(oswindow oswindow)
{
   return oswindow->get_user_interaction() != NULL;
}

inline int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant)
{
   return oswindowParent->is_child(oswindowCandidateChildOrDescendant);
}

inline oswindow GetParent(::oswindow oswindow)
{
   return oswindow->get_parent();
}

inline oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent)
{
   return oswindow->set_parent(oswindowNewParent);
}

inline int ShowWindow(::oswindow oswindow, int32_t nCmdShow)
{
   return oswindow->show_window(nCmdShow);
}

inline int32_t GetWindowLongA(::oswindow oswindow, int32_t nIndex)
{
   return oswindow->get_window_long(nIndex);
}

inline int32_t SetWindowLongA(::oswindow oswindow, int32_t nIndex, int32_t l)
{
   return oswindow->set_window_long(nIndex, l);
}

inline int ClientToScreen(::oswindow oswindow, POINT * lppoint)
{
   return oswindow->client_to_screen(lppoint);
}

inline int ScreenToClient(::oswindow oswindow, POINT * lppoint)
{
   return oswindow->screen_to_client(lppoint);
}

inline int32_t IsIconic(::oswindow oswindow)
{
   return oswindow->is_iconic();
}

inline int32_t IsWindowVisible(::oswindow oswindow)
{
   return oswindow->is_window_visible();
}


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA

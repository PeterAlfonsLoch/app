//
//  macos_window.h
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once


#ifdef __MM


typedef void * int_to_int;


namespace user
{
    
    
    class interaction;
    
    
} // namespace user


#else

struct NSWindow;

#endif


typedef NSWindow * nswindow;


class CLASS_DECL_BASE oswindow_data
{
public:
   
   
   nswindow                      m_nswindow;
   ::user::interaction *    m_pui;
   
   
   int_to_int *                  m_plongmap;
   
   
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
   
   
   void set_user_interaction(::user::interaction * pui);
   ::user::interaction * get_user_interaction_base();
   ::user::interaction * get_user_interaction_base() const;
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


inline int IsWindow(oswindow window)
{
   return window->get_user_interaction() != NULL;
}

inline int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant)
{
   return oswindowParent->is_child(oswindowCandidateChildOrDescendant);
}

inline oswindow GetParent(::oswindow window)
{
   return window->get_parent();
}

inline oswindow SetParent(::oswindow window, ::oswindow oswindowNewParent)
{
   return window->set_parent(oswindowNewParent);
}

inline int ShowWindow(::oswindow window, int32_t nCmdShow)
{
   return window->show_window(nCmdShow);
}

inline int32_t GetWindowLongA(::oswindow window, int32_t nIndex)
{
   return window->get_window_long(nIndex);
}

inline int32_t SetWindowLongA(::oswindow window, int32_t nIndex, int32_t l)
{
   return window->set_window_long(nIndex, l);
}

inline int ClientToScreen(::oswindow window, POINT * lppoint)
{
   return window->client_to_screen(lppoint);
}

inline int ScreenToClient(::oswindow window, POINT * lppoint)
{
   return window->screen_to_client(lppoint);
}

inline int32_t IsIconic(::oswindow window)
{
   return window->is_iconic();
}

inline int32_t IsWindowVisible(::oswindow window)
{
   return window->is_window_visible();
}


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA






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


typedef comparable_array < oswindow_data * > oswindow_dataptra;

class simple_event;


class simple_mutex;



struct CLASS_DECL_BASE oswindow_data
{


   bool                          m_bMessageOnlyWindow;
   ::user::interaction *         m_pui;
   HTHREAD                       m_hthread;
   COLORREF *                    m_pcolorref;
   RECT                          m_rect;
   int_map < LONG > *            m_plongmap;
   bool                          m_bDestroying;


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
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
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






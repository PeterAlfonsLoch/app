#ifndef BASE_SOLARIS_USER_IMPL_H
#define BASE_SOLARIS_USER_IMPL_H


#pragma once



struct hthread;

namespace ca2 {


    class thread_base;


} // namespace ca2


//class oswindow_data;


//typedef oswindow_data * oswindow;



namespace user {


    class interaction;
    class interaction;


} // namespace user


class oswindow_dataptra;


class simple_event;


class mutex;


//typedef hthread * HTHREAD;

class CLASS_DECL_BASE oswindow_data {
public:


    osdisplay m_osdisplay;
    Window m_window;
    Visual m_visual;
    int m_iDepth;
    int m_iScreen;
    bool m_bMessageOnlyWindow;
    ::user::interaction * m_pui;
    HTHREAD m_hthread;
    int_to_int * m_plongmap;
    bool m_bDestroying;
    Colormap m_colormap;


    static oswindow_dataptra * s_pdataptra;
    static mutex * s_pmutex;

    static Atom s_atomLongType;
    static Atom s_atomLongStyle;
    static Atom s_atomLongStyleEx;

    static Atom get_window_long_atom(int32_t nIndex);




    oswindow_data();
    oswindow_data(::user::interaction * puibaseMessageOnlyWindow);
    oswindow_data(const void * p);
    oswindow_data(const LPARAM & lparam);
    oswindow_data(const WPARAM & wparam);


    ~oswindow_data();

    operator void * () {
        return this;
    }

    operator void * () const {
        return (void *) this;
    }

    oswindow_data & operator =(const oswindow_data & window);

    bool operator ==(const void * p) const {
        return this == p;
    }

    bool operator !=(const void * p) const {
        return this != p;
    }

    Display * display() {
        return this == NULL ? NULL : m_osdisplay->display();
    }

    Display * display() const {
        return this == NULL ? NULL : m_osdisplay->display();
    }

    Window window() {
        return this == NULL ? None : m_window;
    }

    Window window() const {
        return this == NULL ? None : m_window;
    }

    Visual * visual() {
        return this == NULL ? NULL : &m_visual;
    }

    Visual * visual() const {
        return this == NULL ? NULL : (Visual *) & m_visual;
    }


    int32_t store_name(const char * psz);
    int32_t select_input(int32_t iInput);
    int32_t select_all_input();
    int32_t map_window();

    void set_user_interaction(::user::interaction * pui);
    ::user::interaction * get_user_interaction_base();
    ::user::interaction * get_user_interaction_base() const;
    ::user::interaction * get_user_interaction();
    ::user::interaction * get_user_interaction() const;


    void post_nc_destroy();


    bool is_child(oswindow oswindowcandidateChildOrDescendant); // or descendant
    oswindow get_parent();
    oswindow set_parent(oswindow oswindowNewParent);
    long get_state();
    bool is_iconic();
    bool is_window_visible();
    bool show_window(int32_t nCmdShow);
    LONG get_window_long(int32_t nIndex);
    LONG set_window_long(int32_t nIndex, LONG l);
    bool client_to_screen(LPPOINT lppoint);
    bool screen_to_client(LPPOINT lppoint);

    bool is_null() const {
        return this == NULL;
    }


    bool is_destroying();


};


CLASS_DECL_BASE int32_t oswindow_find_message_only_window(::user::interaction * puibaseMessageWindow);
CLASS_DECL_BASE int32_t oswindow_find(Display * pdisplay, Window window);
CLASS_DECL_BASE int32_t oswindow_find(Window window);
CLASS_DECL_BASE oswindow_data * oswindow_get_message_only_window(::user::interaction * puibaseMessageWindow);
//CLASS_DECL_BASE oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = NULL);
CLASS_DECL_BASE oswindow_data * oswindow_get(Window window);
CLASS_DECL_BASE oswindow oswindow_defer_get(Window w);
CLASS_DECL_BASE bool oswindow_remove(Display * pdisplay, Window window);
CLASS_DECL_BASE bool oswindow_remove_message_only_window(::user::interaction * puibaseMessageOnlyWindow);




#define HWND_MESSAGE ((::oswindow_data *) (int_ptr) 1)

inline bool IsChild(oswindow oswindowParent, ::oswindow oswindowcandidateChildOrDescendant) {
    return oswindowParent->is_child(oswindowcandidateChildOrDescendant);
}

inline oswindow GetParent(::oswindow oswindow) {
    return oswindow->get_parent();
}

inline oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent) {
    return oswindow->set_parent(oswindowNewParent);
}

inline bool ShowWindow(::oswindow oswindow, int32_t nCmdShow) {
    return oswindow->show_window(nCmdShow);
}

inline LONG GetWindowLongA(::oswindow oswindow, int32_t nIndex) {
    return oswindow->get_window_long(nIndex);
}

inline LONG SetWindowLongA(::oswindow oswindow, int32_t nIndex, LONG l) {
    return oswindow->set_window_long(nIndex, l);
}

inline bool ClientToScreen(::oswindow oswindow, LPPOINT lppoint) {
    return oswindow->client_to_screen(lppoint);
}

inline bool ScreenToClient(::oswindow oswindow, LPPOINT lppoint) {
    return oswindow->screen_to_client(lppoint);
}

inline int32_t IsIconic(::oswindow oswindow) {
    return oswindow->is_iconic();
}

inline int32_t IsWindowVisible(::oswindow oswindow) {
    return oswindow->is_window_visible();
}


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA



CLASS_DECL_BASE int IsWindow(oswindow oswindow);

class oswindow_dataptra :
public array < oswindow_data * > {
public:


};

extern oswindow g_oswindowDesktop;

oswindow GetCapture();
oswindow SetCapture(oswindow window);
WINBOOL ReleaseCapture();
oswindow SetFocus(oswindow window);
oswindow GetFocus();
oswindow GetWindow(oswindow window, int iParentHood);
oswindow GetActiveWindow();
oswindow SetActiveWindow(oswindow window);
WINBOOL DestroyWindow(oswindow window);
oswindow GetDesktopWindow();

class osdisplay_dataptra :
public ::raw_array < osdisplay_data * > {
public:


};


#endif // BASE_SOLARIS_USER_IMPL_H











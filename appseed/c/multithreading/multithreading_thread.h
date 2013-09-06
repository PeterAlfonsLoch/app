#pragma once


#ifdef WINDOWSEX

typedef HANDLE HTHREAD;

#else

class event;

typedef hthread * HTHREAD;

#endif



CLASS_DECL_c HTHREAD get_current_thread();

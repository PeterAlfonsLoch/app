#pragma once


#ifdef WINDOWSEX

typedef HANDLE HTHREAD;

#else

typedef hthread * HTHREAD;

#endif


class CLASS_DECL_c thread_base :
   virtual public object
{
public:


   thread *          m_pthread;


   thread_base();
   virtual ~thread_base();


   virtual HTHREAD get_os_handle() const;
   virtual int get_x_window_count() const;
   virtual void step_timer();
   virtual bool get_run();

   virtual bool verb();


};

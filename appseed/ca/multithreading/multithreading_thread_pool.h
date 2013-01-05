//*****************************************************************************
//
//      Class:          thread_pool
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides the ability to queue simple member functions
//                      to the Windows thread pool.
//
//*****************************************************************************

#pragma once

template < typename T >
class simple_signal :
   virtual public ::radix::object
{
public:

   typedef void (T::*method)();


   T *      m_pobject;
   method   m_pmethod;


   simple_signal(T * pobject, method pmethod);

   void emit();

};

template < typename T >
simple_signal < T > ::simple_signal(T * pobject, method pmethod) :
   m_pobject(pobject),
   m_pmethod(pmethod)
{
}

template < typename T >
void simple_signal < T > ::emit()
{
   (m_pobject->*m_pmethod)();
}

class thread_pool
{
public:

   template <typename T>
   static void QueueUserWorkItem(T * pobject, void (T::*pmethod)(), ULONG flags =
#ifdef WINDOWSEX
   WT_EXECUTELONGFUNCTION
#else
   0
#endif
   )
   {
      simple_signal < T > * psignal = new simple_signal < T >(pobject, pmethod);

#ifdef WINDOWSEX
      if(!::QueueUserWorkItem(thread_proc < T >, psignal, flags))
      {
         delete psignal;
         throw last_error_exception(pobject->get_app());
      }
#else
      if(!__begin_thread(pobject->get_app(), thread_proc < T >, psignal))
      {
         delete psignal;
         throw 0;
      }
#endif
   }

private:

   template <typename T>
#ifdef WINDOWSEX
   static uint32_t WINAPI thread_proc(PVOID pcontext)
#else
   static UINT c_cdecl thread_proc(PVOID pcontext)
#endif
   {
      simple_signal < T > * psignal =  static_cast < simple_signal < T > * >(pcontext);

      psignal->emit();

      delete psignal;
      return 0;
   }

   thread_pool();
};

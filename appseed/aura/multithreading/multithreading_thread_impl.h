//
//  multithreading_thread_impl.h
//  aura
//
//
//
#pragma once


#ifdef WINDOWS

typedef uint32_t IDTHREAD;

#else
#define QS_ALLEVENTS 0xffff

void __clear_mq();

typedef HTHREAD IDTHREAD;

template <  >
inline bool EqualElements<IDTHREAD>(IDTHREAD r1, IDTHREAD r2)
{
   return id_thread_equals(r1, r2) != 0;
}
template <  >
inline UINT HashKey(IDTHREAD key)
{
   return 0;
}

#endif



class thread_startup :
   virtual public object
{
public:


   ::thread *              m_pthread;
//   ::thread_impl *         m_pthreadimpl;
   manual_reset_event      m_event;
   manual_reset_event      m_event2;
   DWORD                   m_dwCreateFlags;
   bool                    m_bError;
   int32_t                 m_iError;
   bool                    m_bSynch;
   int32_t                 m_iPriority;


   thread_startup(::aura::application * papp);
   ~thread_startup();

};




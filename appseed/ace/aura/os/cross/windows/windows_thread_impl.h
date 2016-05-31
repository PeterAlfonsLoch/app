#pragma once


CLASS_DECL_AURA IDTHREAD get_current_thread_id();


class CLASS_DECL_AURA message_array:
   public raw_array < MESSAGE >
{


};


class CLASS_DECL_AURA mq{
public:


   mutex m_mutex;
   message_array ma;
   manual_reset_event m_eventNewMessage;
   IDTHREAD m_idthread;
   //uint32_t m_uiId;


   mq();



};


#ifdef __cplusplus

CLASS_DECL_AURA void * __thread_get_data(IDTHREAD thread,uint32_t dwIndex);
CLASS_DECL_AURA int_bool __thread_set_data(IDTHREAD thread,uint32_t dwIndex,void * lpTlsValue);

#endif

//mq * __get_mq();
//mq * __get_mq(IDTHREAD hthread);
void __clear_mq();



void __node_init_cross_windows_threading();


void __node_term_cross_windows_threading();


class CLASS_DECL_AURA thread_data
{
public:


#if defined(_POSIX_THREADS) || defined(LINUX)

   pthread_key_t        m_key;

#else

   DWORD                m_dwIndex;

#endif


   thread_data();
   ~thread_data();


   void * get();
   void set(void * p);


};

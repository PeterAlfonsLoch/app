#pragma once


// thread allocated as non-heap
// 
class CLASS_DECL_ACE simple_thread :
   virtual public thread
{
public:


   uint32_t          m_dwFinishTimeout;


   simple_thread(::ace::application * papp);
   virtual ~simple_thread();


   virtual bool initialize_instance();


};




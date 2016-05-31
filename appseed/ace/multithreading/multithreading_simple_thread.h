#pragma once


// thread allocated as non-heap
// 
class CLASS_DECL_AURA simple_thread :
   virtual public thread
{
public:


   uint32_t          m_dwFinishTimeout;


   simple_thread(::aura::application * papp);
   virtual ~simple_thread();


   virtual bool initialize_instance();


};




#pragma once


class CLASS_DECL_ca2 simple_thread :
   virtual public ::core::thread
{
public:


   uint32_t          m_dwFinishTimeout;


   simple_thread(sp(base_application) papp);
   virtual ~simple_thread();


   virtual bool initialize_instance();


};




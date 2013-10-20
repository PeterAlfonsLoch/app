#pragma once


class CLASS_DECL_CORE simple_thread :
   virtual public thread
{
public:


   uint32_t          m_dwFinishTimeout;


   simple_thread(sp(base_application) papp);
   virtual ~simple_thread();


   virtual bool initialize_instance();


};




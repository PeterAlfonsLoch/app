#pragma once


class CLASS_DECL_BASE simple_thread :
   virtual public thread
{
public:


   uint32_t          m_dwFinishTimeout;


   simple_thread(sp(::base::application) papp);
   virtual ~simple_thread();


   virtual bool initialize_instance();


};




#pragma once


class CLASS_DECL_CORE job :
   virtual public thread
{
public:


   bool        m_bCancel;


   job(sp(base_application) papp);
   virtual ~job();


   virtual int32_t run() = 0;


};

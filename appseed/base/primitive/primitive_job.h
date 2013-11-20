#pragma once


class CLASS_DECL_BASE job :
   virtual public ::object
{
public:


   bool        m_bCancel;


   job(sp(base_application) papp);
   virtual ~job();


   virtual int32_t run() = 0;


};

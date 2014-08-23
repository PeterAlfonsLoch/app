#pragma once


class CLASS_DECL_AXIS job :
   virtual public ::thread
{
public:


   bool        m_bCancel;


   job(sp(::axis::application) papp);
   virtual ~job();



};

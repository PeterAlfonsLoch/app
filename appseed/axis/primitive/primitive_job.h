#pragma once


class CLASS_DECL_AXIS job :
   virtual public ::thread
{
public:


   bool        m_bCancel;


   job(sp(::base::application) papp);
   virtual ~job();



};

#pragma once


class CLASS_DECL_BASE job :
   virtual public ::thread
{
public:


   bool        m_bCancel;


   job(sp(::base::application) papp);
   virtual ~job();



};

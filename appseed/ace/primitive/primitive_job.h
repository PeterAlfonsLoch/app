#pragma once


class CLASS_DECL_ACE job :
   virtual public ::thread
{
public:


   bool        m_bCancel;


   job(::ace::application * papp);
   virtual ~job();



};

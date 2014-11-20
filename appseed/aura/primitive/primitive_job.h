#pragma once


class CLASS_DECL_AURA job :
   virtual public ::thread
{
public:


   bool        m_bCancel;


   job(::aura::application * papp);
   virtual ~job();



};

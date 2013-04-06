#pragma once


typedef long VMSRESULT;


class CLASS_DECL_ca vms_exception : 
   virtual public base_exception  
{
public:


   VMSRESULT   m_vmsResult;


   vms_exception(sp(::ca::application) papp);
   vms_exception(sp(::ca::application) papp, VMSRESULT vmsr);
   virtual ~vms_exception();


};


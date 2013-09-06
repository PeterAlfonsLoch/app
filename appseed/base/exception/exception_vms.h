#pragma once


typedef long VMSRESULT;


class CLASS_DECL_c vms_exception : 
   virtual public ::exception::base  
{
public:


   VMSRESULT   m_vmsResult;


   vms_exception(sp(base_application) papp);
   vms_exception(sp(base_application) papp, VMSRESULT vmsr);
   virtual ~vms_exception();


};


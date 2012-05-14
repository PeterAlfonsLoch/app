#pragma once


typedef long VMSRESULT;


class CLASS_DECL_ca vms_exception : public base_exception  
{
public:


   VMSRESULT   m_vmsResult;


   vms_exception();
   vms_exception(VMSRESULT vmsr);
   virtual ~vms_exception();


};


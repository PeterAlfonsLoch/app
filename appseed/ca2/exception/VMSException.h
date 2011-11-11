#pragma once

typedef long VMSRESULT;

class CLASS_DECL_ca CVMSException : public base_exception  
{
    
public:
   CVMSException();
    CVMSException(VMSRESULT vmsr);
   virtual ~CVMSException();

    VMSRESULT   m_vmsResult;
};

void CLASS_DECL_ca AfxThrowVMSException(VMSRESULT vmsr);

#include "StdAfx.h"


CVMSException::CVMSException()
{
    m_vmsResult = 0;
}

CVMSException::CVMSException(VMSRESULT vmsr)
{
    m_vmsResult = vmsr;
}


CVMSException::~CVMSException()
{

}

CLASS_DECL_ca void AfxThrowVMSException(VMSRESULT vmsr)
{
   throw new CVMSException(vmsr);
}

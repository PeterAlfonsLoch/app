#include "framework.h"


vms_exception::vms_exception()
{
    m_vmsResult = 0;
}

vms_exception::vms_exception(VMSRESULT vmsr)
{
    m_vmsResult = vmsr;
}


vms_exception::~vms_exception()
{

}



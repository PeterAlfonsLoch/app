#include "framework.h"


vms_exception::vms_exception(::ca::application * papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{
    m_vmsResult = 0;
}

vms_exception::vms_exception(::ca::application * papp, VMSRESULT vmsr) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{
    m_vmsResult = vmsr;
}


vms_exception::~vms_exception()
{

}



#include "framework.h"


vms_exception::vms_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{
    m_vmsResult = 0;
}

vms_exception::vms_exception(sp(::ca2::application) papp, VMSRESULT vmsr) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{
    m_vmsResult = vmsr;
}


vms_exception::~vms_exception()
{

}



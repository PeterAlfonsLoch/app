#include "framework.h"


vms_exception::vms_exception(sp(::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
    m_vmsResult = 0;
}

vms_exception::vms_exception(sp(::application) papp, VMSRESULT vmsr) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
    m_vmsResult = vmsr;
}


vms_exception::~vms_exception()
{

}



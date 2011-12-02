#pragma once 

namespace cube8
{


   class system;


} // namespace cube8

namespace bergedge
{


   class bergedge;


} // namespace bergedge



#define cubeSys(papp) (*papp->m_psystem)
#undef Sys
#define Sys(papp) (cubeSys(papp))


#include "cube8/cube8.h"


#include "acube_application.h"



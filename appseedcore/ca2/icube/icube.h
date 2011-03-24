#pragma once


namespace icube
{

   class application;

} // namespace icube

#undef App
#define App(pcaapp) (::icube::app_cast(pcaapp))
#define Application (App(get_app()))


#include "fontopus/fontopus.h"
#include "bergedge/bergedge.h"

#include "icube_application.h"

#include "icube_system.h"
#include "icube_system_ca_template.h"
#include "icube_system_allocate.h"
#include "icube_system_template_trace.h"


#include "icube_main.h"


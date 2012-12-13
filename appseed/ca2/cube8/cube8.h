#pragma once


#include "app/appseed/ca2/cube5/cube5.h"


namespace cube8
{

   class application;

} // namespace cube8

#define cubeApp(pcaapp) (pcaapp->cast_app < cube8::application >())
#define cubeApplication (cubeApp(get_app()))
#undef App
#define App(pcaapp) cubeApp(pcaapp)



#include "app/appseed/ca2/bergedge/bergedge.h"




#include "cube8_application.h"



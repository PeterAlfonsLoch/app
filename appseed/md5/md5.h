#pragma once

#include "include/cube.h"


#ifdef _CA2_FONTOPUS_MD5_DLL
    #define CLASS_DECL_CA2_MD5  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_MD5  _declspec(dllimport)
#endif

namespace md5
{
   class application;
} // namespace md5

#undef App
#define App(pcaapp) (md5::app_cast(pcaapp))


#include "md5_document.h"
#include "md5_frame.h"
#include "md5_view.h"

#include "service.h"
#include "application.h"


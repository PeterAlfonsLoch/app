#pragma once


#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_TESSERACT_DLL
    #define CLASS_DECL_CA2_TESSERACT  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_TESSERACT  _declspec(dllimport)
#endif


namespace tesseract
{

   class application;

} // namespace tesseract


#undef App
#define App(pcaapp) (pcaapp->cast_app < ::tesseract::application > ())


#include "atesseract_application.h"



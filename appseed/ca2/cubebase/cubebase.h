#pragma once 


#include "ca/ca.h"



#ifdef _WINDOWS
#ifdef __CA2__DLL
   #define CLASS_DECL_ca2  _declspec(dllexport)
#else
   #define CLASS_DECL_ca2  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_ca2
#endif



namespace cube8
{


   class system;


} // namespace cube8


namespace bergedge
{


   class bergedge;


} // namespace bergedge



#define cubeCube(papp) (*papp->m_pcube)
#undef Cub
#define Cub(papp) (cubeCube(papp))
#define Cube (Cub(this->get_app()))


#include "cubebase_application.h"



#include "Imf.h"



#ifndef INCLUDED_IMF_FLOAT_ATTRIBUTE_H
#define INCLUDED_IMF_FLOAT_ATTRIBUTE_H

//-----------------------------------------------------------------------------
//
//	class FloatAttribute
//
//-----------------------------------------------------------------------------

#include <ImfAttribute.h>


namespace Imf {


typedef TypedAttribute<float> FloatAttribute;
template <> const char *FloatAttribute::staticTypeName ();


} // namespace Imf

// Metrowerks compiler wants the .cpp file inlined, too
#ifdef __MWERKS__
#include <ImfFloatAttribute.cpp>
#endif

#endif

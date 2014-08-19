#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class FloatAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfFloatAttribute.h>


namespace Imf {


template <>
const char *
FloatAttribute::staticTypeName ()
{
    return "float";
}


} // namespace Imf

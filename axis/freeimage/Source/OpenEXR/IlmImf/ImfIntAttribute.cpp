#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class IntAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfIntAttribute.h>


namespace Imf {


template <>
const char *
IntAttribute::staticTypeName ()
{
    return "int";
}


} // namespace Imf

#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class DoubleAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfDoubleAttribute.h>


namespace Imf {


template <>
const char *
DoubleAttribute::staticTypeName ()
{
    return "double";
}


} // namespace Imf

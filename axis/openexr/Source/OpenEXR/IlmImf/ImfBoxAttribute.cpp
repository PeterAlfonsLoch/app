#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class Box2iAttribute
//	class Box2fAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfBoxAttribute.h>


namespace Imf {


template <>
const char *
Box2iAttribute::staticTypeName ()
{
    return "box2i";
}


template <>
void
Box2iAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.min.x);
    Xdr::write <StreamIO> (os, _value.min.y);
    Xdr::write <StreamIO> (os, _value.max.x);
    Xdr::write <StreamIO> (os, _value.max.y);
}


template <>
void
Box2iAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.min.x);
    Xdr::read <StreamIO> (is, _value.min.y);
    Xdr::read <StreamIO> (is, _value.max.x);
    Xdr::read <StreamIO> (is, _value.max.y);
}


template <>
const char *
Box2fAttribute::staticTypeName ()
{
    return "box2f";
}


template <>
void
Box2fAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.min.x);
    Xdr::write <StreamIO> (os, _value.min.y);
    Xdr::write <StreamIO> (os, _value.max.x);
    Xdr::write <StreamIO> (os, _value.max.y);
}


template <>
void
Box2fAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.min.x);
    Xdr::read <StreamIO> (is, _value.min.y);
    Xdr::read <StreamIO> (is, _value.max.x);
    Xdr::read <StreamIO> (is, _value.max.y);
}


} // namespace Imf

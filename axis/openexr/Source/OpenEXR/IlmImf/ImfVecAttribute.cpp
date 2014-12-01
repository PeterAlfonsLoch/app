#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class V2iAttribute
//	class V2fAttribute
//	class V2dAttribute
//	class V3iAttribute
//	class V3fAttribute
//	class V3dAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfVecAttribute.h>


namespace Imf {


template <>
const char *
V2iAttribute::staticTypeName ()
{
    return "v2i";
}


template <>
void
V2iAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.x);
    Xdr::write <StreamIO> (os, _value.y);
}


template <>
void
V2iAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.x);
    Xdr::read <StreamIO> (is, _value.y);
}


template <>
const char *
V2fAttribute::staticTypeName ()
{
    return "v2f";
}


template <>
void
V2fAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.x);
    Xdr::write <StreamIO> (os, _value.y);
}


template <>
void
V2fAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.x);
    Xdr::read <StreamIO> (is, _value.y);
}


template <>
const char *
V2dAttribute::staticTypeName ()
{
    return "v2d";
}


template <>
void
V2dAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.x);
    Xdr::write <StreamIO> (os, _value.y);
}


template <>
void
V2dAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.x);
    Xdr::read <StreamIO> (is, _value.y);
}


template <>
const char *
V3iAttribute::staticTypeName ()
{
    return "v3i";
}


template <>
void
V3iAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.x);
    Xdr::write <StreamIO> (os, _value.y);
    Xdr::write <StreamIO> (os, _value.z);
}


template <>
void
V3iAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.x);
    Xdr::read <StreamIO> (is, _value.y);
    Xdr::read <StreamIO> (is, _value.z);
}


template <>
const char *
V3fAttribute::staticTypeName ()
{
    return "v3f";
}


template <>
void
V3fAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.x);
    Xdr::write <StreamIO> (os, _value.y);
    Xdr::write <StreamIO> (os, _value.z);
}


template <>
void
V3fAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.x);
    Xdr::read <StreamIO> (is, _value.y);
    Xdr::read <StreamIO> (is, _value.z);
}


template <>
const char *
V3dAttribute::staticTypeName ()
{
    return "v3d";
}


template <>
void
V3dAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value.x);
    Xdr::write <StreamIO> (os, _value.y);
    Xdr::write <StreamIO> (os, _value.z);
}


template <>
void
V3dAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value.x);
    Xdr::read <StreamIO> (is, _value.y);
    Xdr::read <StreamIO> (is, _value.z);
}


} // namespace Imf

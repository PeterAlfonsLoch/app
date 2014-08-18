#include "Imf.h"


namespace Imf {


template <>
const char *
M33fAttribute::staticTypeName ()
{
    return "m33f";
}


template <>
void
M33fAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value[0][0]);
    Xdr::write <StreamIO> (os, _value[0][1]);
    Xdr::write <StreamIO> (os, _value[0][2]);

    Xdr::write <StreamIO> (os, _value[1][0]);
    Xdr::write <StreamIO> (os, _value[1][1]);
    Xdr::write <StreamIO> (os, _value[1][2]);

    Xdr::write <StreamIO> (os, _value[2][0]);
    Xdr::write <StreamIO> (os, _value[2][1]);
    Xdr::write <StreamIO> (os, _value[2][2]);
}


template <>
void
M33fAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value[0][0]);
    Xdr::read <StreamIO> (is, _value[0][1]);
    Xdr::read <StreamIO> (is, _value[0][2]);

    Xdr::read <StreamIO> (is, _value[1][0]);
    Xdr::read <StreamIO> (is, _value[1][1]);
    Xdr::read <StreamIO> (is, _value[1][2]);

    Xdr::read <StreamIO> (is, _value[2][0]);
    Xdr::read <StreamIO> (is, _value[2][1]);
    Xdr::read <StreamIO> (is, _value[2][2]);
}


template <>
const char *
M33dAttribute::staticTypeName ()
{
    return "m33d";
}


template <>
void
M33dAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value[0][0]);
    Xdr::write <StreamIO> (os, _value[0][1]);
    Xdr::write <StreamIO> (os, _value[0][2]);

    Xdr::write <StreamIO> (os, _value[1][0]);
    Xdr::write <StreamIO> (os, _value[1][1]);
    Xdr::write <StreamIO> (os, _value[1][2]);

    Xdr::write <StreamIO> (os, _value[2][0]);
    Xdr::write <StreamIO> (os, _value[2][1]);
    Xdr::write <StreamIO> (os, _value[2][2]);
}


template <>
void
M33dAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value[0][0]);
    Xdr::read <StreamIO> (is, _value[0][1]);
    Xdr::read <StreamIO> (is, _value[0][2]);

    Xdr::read <StreamIO> (is, _value[1][0]);
    Xdr::read <StreamIO> (is, _value[1][1]);
    Xdr::read <StreamIO> (is, _value[1][2]);

    Xdr::read <StreamIO> (is, _value[2][0]);
    Xdr::read <StreamIO> (is, _value[2][1]);
    Xdr::read <StreamIO> (is, _value[2][2]);
}


template <>
const char *
M44fAttribute::staticTypeName ()
{
    return "m44f";
}


template <>
void
M44fAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value[0][0]);
    Xdr::write <StreamIO> (os, _value[0][1]);
    Xdr::write <StreamIO> (os, _value[0][2]);
    Xdr::write <StreamIO> (os, _value[0][3]);

    Xdr::write <StreamIO> (os, _value[1][0]);
    Xdr::write <StreamIO> (os, _value[1][1]);
    Xdr::write <StreamIO> (os, _value[1][2]);
    Xdr::write <StreamIO> (os, _value[1][3]);

    Xdr::write <StreamIO> (os, _value[2][0]);
    Xdr::write <StreamIO> (os, _value[2][1]);
    Xdr::write <StreamIO> (os, _value[2][2]);
    Xdr::write <StreamIO> (os, _value[2][3]);

    Xdr::write <StreamIO> (os, _value[3][0]);
    Xdr::write <StreamIO> (os, _value[3][1]);
    Xdr::write <StreamIO> (os, _value[3][2]);
    Xdr::write <StreamIO> (os, _value[3][3]);
}


template <>
void
M44fAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value[0][0]);
    Xdr::read <StreamIO> (is, _value[0][1]);
    Xdr::read <StreamIO> (is, _value[0][2]);
    Xdr::read <StreamIO> (is, _value[0][3]);

    Xdr::read <StreamIO> (is, _value[1][0]);
    Xdr::read <StreamIO> (is, _value[1][1]);
    Xdr::read <StreamIO> (is, _value[1][2]);
    Xdr::read <StreamIO> (is, _value[1][3]);

    Xdr::read <StreamIO> (is, _value[2][0]);
    Xdr::read <StreamIO> (is, _value[2][1]);
    Xdr::read <StreamIO> (is, _value[2][2]);
    Xdr::read <StreamIO> (is, _value[2][3]);

    Xdr::read <StreamIO> (is, _value[3][0]);
    Xdr::read <StreamIO> (is, _value[3][1]);
    Xdr::read <StreamIO> (is, _value[3][2]);
    Xdr::read <StreamIO> (is, _value[3][3]);
}


template <>
const char *
M44dAttribute::staticTypeName ()
{
    return "m44d";
}


template <>
void
M44dAttribute::writeValueTo (OStream &os, int version) const
{
    Xdr::write <StreamIO> (os, _value[0][0]);
    Xdr::write <StreamIO> (os, _value[0][1]);
    Xdr::write <StreamIO> (os, _value[0][2]);
    Xdr::write <StreamIO> (os, _value[0][3]);

    Xdr::write <StreamIO> (os, _value[1][0]);
    Xdr::write <StreamIO> (os, _value[1][1]);
    Xdr::write <StreamIO> (os, _value[1][2]);
    Xdr::write <StreamIO> (os, _value[1][3]);

    Xdr::write <StreamIO> (os, _value[2][0]);
    Xdr::write <StreamIO> (os, _value[2][1]);
    Xdr::write <StreamIO> (os, _value[2][2]);
    Xdr::write <StreamIO> (os, _value[2][3]);

    Xdr::write <StreamIO> (os, _value[3][0]);
    Xdr::write <StreamIO> (os, _value[3][1]);
    Xdr::write <StreamIO> (os, _value[3][2]);
    Xdr::write <StreamIO> (os, _value[3][3]);
}


template <>
void
M44dAttribute::readValueFrom (IStream &is, int size, int version)
{
    Xdr::read <StreamIO> (is, _value[0][0]);
    Xdr::read <StreamIO> (is, _value[0][1]);
    Xdr::read <StreamIO> (is, _value[0][2]);
    Xdr::read <StreamIO> (is, _value[0][3]);

    Xdr::read <StreamIO> (is, _value[1][0]);
    Xdr::read <StreamIO> (is, _value[1][1]);
    Xdr::read <StreamIO> (is, _value[1][2]);
    Xdr::read <StreamIO> (is, _value[1][3]);

    Xdr::read <StreamIO> (is, _value[2][0]);
    Xdr::read <StreamIO> (is, _value[2][1]);
    Xdr::read <StreamIO> (is, _value[2][2]);
    Xdr::read <StreamIO> (is, _value[2][3]);

    Xdr::read <StreamIO> (is, _value[3][0]);
    Xdr::read <StreamIO> (is, _value[3][1]);
    Xdr::read <StreamIO> (is, _value[3][2]);
    Xdr::read <StreamIO> (is, _value[3][3]);
}


} // namespace Imf

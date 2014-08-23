#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class StringAttribute
//
//-----------------------------------------------------------------------------

//#include <ImfStringVectorAttribute.h>


namespace Imf {


template <>
const char *
StringVectorAttribute::staticTypeName ()
{
    return "stringvector";
}


template <>
void
StringVectorAttribute::writeValueTo (OStream &os, int version) const
{
    int size = _value.size();

    for (int i = 0; i < size; i++)
    {
        int strSize = _value[i].size();
        Xdr::write <StreamIO> (os, strSize);
	Xdr::write <StreamIO> (os, &_value[i][0], strSize);
    }
}


template <>
void
StringVectorAttribute::readValueFrom (IStream &is, int size, int version)
{
    int read = 0;

    while (read < size)
    {   
       int strSize;
       Xdr::read <StreamIO> (is, strSize);
       read += Xdr::size<int>();       

       std::string str;

       Xdr::read<StreamIO>(is,str.GetBufferSetLength(strSize),strSize);

       read += strSize;

       str.ReleaseBuffer(strSize);

       _value.push_back (str);
    }
}


} // namespace Imf

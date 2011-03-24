#pragma once

namespace gen
{

class CLASS_DECL_ca base64 :
   virtual public ::radix::object
{

public:
   base64();
   virtual ~base64();

protected:
   unsigned char etable[256];
   unsigned char dtable[256];

public:
   void encode(ex1::input_stream & istreamBinary, ex1::output_stream & ostreamBase64);
   string encode(primitive::memory & storageBinary);
   string encode(const char * psz);
   string serialize(ex1::serializable & serializable);

   void decode(ex1::input_stream & istreamBase64, ex1::output_stream & ostreamBinary);
   void decode(const char * pszBase64, primitive::memory & storageBinary);
   string decode(const char * psz);
   void unserialize(const char * pszBase64, ex1::serializable & serializable);

   
};

   


}

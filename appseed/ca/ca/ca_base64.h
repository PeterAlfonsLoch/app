#pragma once



class CLASS_DECL_ca base64 :
   virtual public object
{
protected:


   uchar etable[256];
   uchar dtable[256];


public:


   base64();
   virtual ~base64();


   void encode(::primitive::memory & mem64, const ::primitive::memory & mem);
   string encode(const ::primitive::memory & storageBinary);
   string encode(const byte * p, ::count c);
   string encode(const char * psz);


   void decode(::primitive::memory & mem, const ::primitive::memory & mem64);
   void decode(::primitive::memory & storageBinary, const char * pszBase64);
   string decode(const char * psz);

   
};





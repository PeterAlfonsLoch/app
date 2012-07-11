#pragma once



class CLASS_DECL_c base64
{
protected:


   unsigned char etable[256];
   unsigned char dtable[256];


public:


   base64();
   virtual ~base64();


   void encode(simple_memory & mem64, const simple_memory & mem);
   vsstring encode(const simple_memory & storageBinary);
   vsstring encode(const byte * p, count c);
   vsstring encode(const char * psz);


   void decode(simple_memory & mem, const simple_memory & mem64);
   void decode(simple_memory & storageBinary, const char * pszBase64);
   vsstring decode(const char * psz);

   
};





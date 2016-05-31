#pragma once


namespace str
{


   class CLASS_DECL_AURA base64 :
      virtual public ::object
   {
   protected:


      uchar etable[256];
      uchar dtable[256];


   public:


      base64();
      virtual ~base64();


      void encode(::file::ostream & ostreamBase64, ::file::istream & istreamBinary);
      string encode(primitive::memory_base & storageBinary);
      string encode(byte * p, ::count ca);
      string encode(const char * psz);
      string serialize(::file::serializable & serializable);

      void decode(::file::ostream & ostreamBinary, ::file::istream & istreamBase64);
      void decode(primitive::memory_base & storageBinary, const char * pszBase64);
      string decode(const char * psz);
      void unserialize(::file::serializable & serializable, const char * pszBase64);

   
   };


} // namespace str




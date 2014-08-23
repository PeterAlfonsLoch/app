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


      void encode(::file::output_stream & ostreamBase64, ::file::input_stream & istreamBinary);
      string encode(primitive::memory_base & storageBinary);
      string encode(byte * p, ::count ca);
      string encode(const char * psz);
      string serialize(::file::serializable & serializable);

      void decode(::file::output_stream & ostreamBinary, ::file::input_stream & istreamBase64);
      void decode(primitive::memory & storageBinary, const char * pszBase64);
      string decode(const char * psz);
      void unserialize(::file::serializable & serializable, const char * pszBase64);

   
   };


} // namespace str




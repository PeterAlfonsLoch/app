#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 base64 :
      virtual public object
   {
   protected:


      uchar etable[256];
      uchar dtable[256];


   public:


      base64();
      virtual ~base64();


      void encode(::ca2::plain_text_output_stream & ostreamBase64, ::file::byte_input_stream & istreamBinary);
      string encode(primitive::memory_base & storageBinary);
      string encode(byte * p, ::count ca);
      string encode(const char * psz);
      string serialize(::file::byte_serializable & serializable);

      void decode(::file::byte_output_stream & ostreamBinary, ::ca2::plain_text_input_stream & istreamBase64);
      void decode(primitive::memory & storageBinary, const char * pszBase64);
      string decode(const char * psz);
      void unserialize(::file::byte_serializable & serializable, const char * pszBase64);

   
   };


} // namespace ca2




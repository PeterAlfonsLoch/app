#pragma once


namespace ca
{


   class CLASS_DECL_ca base64 :
      virtual public ::ca::object
   {
   protected:


      uchar etable[256];
      uchar dtable[256];


   public:


      base64();
      virtual ~base64();


      void encode(::ca::plain_text_output_stream & ostreamBase64, ::ca::byte_input_stream & istreamBinary);
      string encode(primitive::memory_base & storageBinary);
      string encode(byte * p, count c);
      string encode(const char * psz);
      string serialize(::ca::byte_serializable & serializable);

      void decode(::ca::byte_output_stream & ostreamBinary, ::ca::plain_text_input_stream & istreamBase64);
      void decode(primitive::memory & storageBinary, const char * pszBase64);
      string decode(const char * psz);
      void unserialize(::ca::byte_serializable & serializable, const char * pszBase64);

   
   };


} // namespace ca




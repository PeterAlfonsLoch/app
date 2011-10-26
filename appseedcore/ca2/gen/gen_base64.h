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
      void encode(ex1::plain_text_output_stream & ostreamBase64, ex1::byte_input_stream & istreamBinary);
      string encode(primitive::memory_base & storageBinary);
      string encode(byte * p, count c);
      string encode(const char * psz);
      string serialize(ex1::byte_serializable & serializable);

      void decode(ex1::byte_output_stream & ostreamBinary, ex1::plain_text_input_stream & istreamBase64);
      void decode(primitive::memory & storageBinary, const char * pszBase64);
      string decode(const char * psz);
      void unserialize(ex1::byte_serializable & serializable, const char * pszBase64);

   
   };


} // namespace gen




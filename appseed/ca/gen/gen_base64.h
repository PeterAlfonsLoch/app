#pragma once


namespace gen
{


   class CLASS_DECL_ca base64 :
      virtual public ::gen::object
   {
   protected:


      uchar etable[256];
      uchar dtable[256];


   public:


      base64();
      virtual ~base64();


      void encode(gen::plain_text_output_stream & ostreamBase64, gen::byte_input_stream & istreamBinary);
      string encode(primitive::memory_base & storageBinary);
      string encode(byte * p, count c);
      string encode(const char * psz);
      string serialize(gen::byte_serializable & serializable);

      void decode(gen::byte_output_stream & ostreamBinary, gen::plain_text_input_stream & istreamBase64);
      void decode(primitive::memory & storageBinary, const char * pszBase64);
      string decode(const char * psz);
      void unserialize(gen::byte_serializable & serializable, const char * pszBase64);

   
   };


} // namespace gen




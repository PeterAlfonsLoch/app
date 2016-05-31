#pragma once


namespace file
{


   class CLASS_DECL_ACE byte_istream_binary_buffer :
      virtual public byte_istream
   {
   public:

      buffer_sp     m_spbinarybuffer;


      byte_istream_binary_buffer(::ace::application * papp, const char * pszFilePath, uint32_t uiFlags = 0);
      virtual ~byte_istream_binary_buffer();

   };


} // namespace file



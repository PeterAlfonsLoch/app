#pragma once


namespace file
{


   class CLASS_DECL_AURA byte_ostream_binary_buffer :
      virtual public byte_ostream
   {
   public:


      binary_buffer_sp     m_spbinarybuffer;

      byte_ostream_binary_buffer(::aura::application * papp, const char * pszFilePath, uint32_t uiFlags = 0);
      virtual ~byte_ostream_binary_buffer();

   };


} // namespace file



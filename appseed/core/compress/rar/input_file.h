// RarIn.h
// from 7-zip

#pragma once

/*
#include "Common/DynamicBuffer.h"
#include "Common/MyCom.h"

#include "../../ICoder.h"
#include "../../IStream.h"

#include "../../Common/StreamObjects.h"

#include "../../Crypto/RarAes.h"

#include "RarHeader.h"
#include "RarItem.h"
*/

namespace rar
{

   class input_file_exception :
      virtual public simple_exception
   {
   public:

      enum CCauseType
      {
         kUnexpectedEndOfArchive = 0,
         kArchiveHeaderCRCError,
         kFileHeaderCRCError,
         kIncorrectArchive
      } Cause;

      input_file_exception(sp(::axis::application) papp, CCauseType cause) :
         element(papp),
         ::call_stack(papp),
         ::exception::base(papp),
         simple_exception(papp),
         Cause(cause)
      {

      }

   };


   struct input_file_info
   {
      UINT Flags;
      byte EncryptVersion;
      uint64_t StartPosition;

      bool IsSolid() const { return (Flags & header::archive::kSolid) != 0; }
      bool IsCommented() const {  return (Flags & header::archive::kComment) != 0; }
      bool IsVolume() const {  return (Flags & header::archive::kVolume) != 0; }
      bool HaveNewVolumeName() const {  return (Flags & header::archive::kNewVolName) != 0; }
      bool IsEncrypted() const { return (Flags & header::archive::kBlockEncryption) != 0; }
      bool IsThereEncryptVer() const { return (Flags & header::archive::kEncryptVer) != 0; }
      bool IsEncryptOld() const { return (!IsThereEncryptVer() || EncryptVersion < 36); }
   };

   class input_file :
      public ::file::binary_buffer
   {
   public:


      sp(::file::input_stream)                      m_Stream;

      file_position                                   m_StreamStartPosition;

      input_file_info                                 _header;
      ::file::char_dynamic_buffer                        m_NameBuffer;
      ::file::wchar_dynamic_buffer                       _unicodeNameBuffer;

      ::file::byte_buffer                                _comment;

      ::file::byte_dynamic_buffer                        m_FileHeaderData;

      header::NBlock::CBlock                          m_BlockHeader;

      crypto::rar29::decoder *                        m_RarAESSpec;
      sp(::libcompress::filter_interface)                  m_RarAES;


      byte *                                          m_CurData; // it must point to start of Rar::Block
      uint32_t                                          m_CurPos;
      uint32_t                                          m_PosLimit;

      ::file::byte_buffer                                m_DecryptedData;
      byte *                                          m_DecryptedDataAligned;
      ::primitive::memory_size                        m_DecryptedDataSize;

      bool m_CryptoMode;
      uint32_t m_CryptoPos;
      uint64_t m_Position;

      void ReadName(CItemEx &item, int32_t nameSize);
      void ReadHeaderReal(CItemEx &item);

      HRESULT ReadBytesSpec(void * data, ::primitive::memory_size * size);
      bool ReadBytesAndTestSize(void * data, ::primitive::memory_size size);

      HRESULT Open2(::file::input_stream *stream, const file_position *searchHeaderSizeLimit);

      void ThrowExceptionWithCode(input_file_exception::CCauseType cause);
      void ThrowUnexpectedEndOfArchiveException();

      void AddToSeekValue(uint64_t addValue);


      byte ReadByte();
      uint16_t ReadUInt16();
      uint32_t ReadUInt32();
      void ReadTime(byte mask, CRarTime &rarTime);

      void FinishCryptoBlock()
      {
         if (m_CryptoMode)
            while ((m_CryptoPos & 0xF) != 0)
            {
               m_CryptoPos++;
               m_Position++;
            }
      }


      HRESULT Open(::file::input_stream *inStream, const file_position *searchHeaderSizeLimit);
      void Close();
      HRESULT GetNextItem(CItemEx &item, crypto::get_text_password_interface *getTextPassword, bool &decryptionError, string &errorMessage);

      void GetArchiveInfo(input_file_info &archiveInfo) const;

      void SeekInArchive(file_position position);
      ::file::reader * CreateLimitedStream(file_position position, file_size size);
   };

}

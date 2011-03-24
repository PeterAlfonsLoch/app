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
      }
      Cause;
      input_file_exception(CCauseType cause) :   Cause(cause) {}
   };


   struct input_file_info
   {
      UINT Flags;
      byte EncryptVersion;
      unsigned __int64 StartPosition;

      bool IsSolid() const { return (Flags & header::archive::kSolid) != 0; }
      bool IsCommented() const {  return (Flags & header::archive::kComment) != 0; }
      bool IsVolume() const {  return (Flags & header::archive::kVolume) != 0; }
      bool HaveNewVolumeName() const {  return (Flags & header::archive::kNewVolName) != 0; }
      bool IsEncrypted() const { return (Flags & header::archive::kBlockEncryption) != 0; }
      bool IsThereEncryptVer() const { return (Flags & header::archive::kEncryptVer) != 0; }
      bool IsEncryptOld() const { return (!IsThereEncryptVer() || EncryptVersion < 36); }
   };

   class input_file :
      public ex1::file
   {
   public:
      
      
      pointer_object<ex1::input_stream>   m_Stream;

      unsigned __int64                    m_StreamStartPosition;

      input_file_info                     _header;
      ex1::char_dynamic_buffer            m_NameBuffer;
      ex1::wchar_dynamic_buffer           _unicodeNameBuffer;

      ex1::byte_buffer                    _comment;

      ex1::byte_dynamic_buffer            m_FileHeaderData;

      header::NBlock::CBlock              m_BlockHeader;

      crypto::rar29::decoder *            m_RarAESSpec;
      pointer_object<compress::filter_interface>     m_RarAES;


      byte *m_CurData; // it must point to start of Rar::Block
      uint32 m_CurPos;
      uint32 m_PosLimit;

      ex1::byte_buffer m_DecryptedData;
      byte *m_DecryptedDataAligned;
      uint32 m_DecryptedDataSize;

      bool m_CryptoMode;
      uint32 m_CryptoPos;
      uint64 m_Position;

      void ReadName(CItemEx &item, int nameSize);
      void ReadHeaderReal(CItemEx &item);

      HRESULT ReadBytesSpec(void *data, size_t *size);
      bool ReadBytesAndTestSize(void *data, uint32 size);

      HRESULT Open2(ex1::input_stream *stream, const uint64 *searchHeaderSizeLimit);

      void ThrowExceptionWithCode(input_file_exception::CCauseType cause);
      void ThrowUnexpectedEndOfArchiveException();

      void AddToSeekValue(uint64 addValue);


      byte ReadByte();
      uint16 ReadUInt16();
      uint32 ReadUInt32();
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


      HRESULT Open(ex1::input_stream *inStream, const uint64 *searchHeaderSizeLimit);
      void Close();
      HRESULT GetNextItem(CItemEx &item, crypto::get_text_password_interface *getTextPassword, bool &decryptionError, string &errorMessage);

      void GetArchiveInfo(input_file_info &archiveInfo) const;

      void SeekInArchive(uint64 position);
      ex1::reader * CreateLimitedStream(uint64 position, uint64 size);
   };

}

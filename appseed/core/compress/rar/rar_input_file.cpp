// Archive/RarIn.cpp
// from 7-zip
#include "framework.h"


/*#include "../../../../C/7zCrc.h"
#include "../../../../C/CpuArch.h"

#include "Common/StringConvert.h"
#include "Common/UTFConvert.h"

#include "../../Common/LimitedStreams.h"
#include "../../Common/StreamUtils.h"

#include "../Common/FindSignature.h"

#include "RarIn.h"*/

#define Get16(p) GetUi16(p)
#define Get32(p) GetUi32(p)
#define Get64(p) GetUi64(p)

namespace rar
{

   static const char *k_UnexpectedEnd = "Unexpected end of archive";
   static const char *k_DecryptionError = "Decryption Error";

   void input_file::ThrowExceptionWithCode(input_file_exception::CCauseType cause)
   {
      throw input_file_exception(get_app(), cause);
   }

   HRESULT input_file::Open(::file::input_stream *inStream, const file_position *searchHeaderSizeLimit)
   {
      try
      {
         Close();
         HRESULT res = Open2(inStream, searchHeaderSizeLimit);
         if (res == S_OK)
            return res;
         Close();
         return res;
      }
      catch(...) { Close(); throw; }
   }

   void input_file::Close()
   {
      //m_Stream.Release();
   }

   HRESULT input_file::ReadBytesSpec(void * data, ::primitive::memory_size * resSize)
   {
      if (m_CryptoMode)
      {
         ::primitive::memory_size size = *resSize;
         *resSize = 0;
         const byte *bufData = m_DecryptedDataAligned;
         ::primitive::memory_size bufSize = m_DecryptedDataSize;
         ::primitive::memory_size i;
         for (i = 0; i < size && m_CryptoPos < bufSize; i++)
            ((byte *)data)[i] = bufData[m_CryptoPos++];
         *resSize = i;
         return S_OK;
      }
      return ::file::read(m_Stream, data, resSize);
   }

   bool input_file::ReadBytesAndTestSize(void *data, ::primitive::memory_size size)
   {
      ::primitive::memory_size processed = size;
      if (ReadBytesSpec(data, &processed) != S_OK)
         return false;
      return processed == size;
   }

   HRESULT input_file::Open2(::file::input_stream *stream, const file_position *searchHeaderSizeLimit)
   {
      m_CryptoMode = false;
      try
      {
         m_StreamStartPosition = stream->seek(0, ::file::seek_begin);
      }
      catch(...)
      {
         return E_FAIL;
      }
      m_Position = m_StreamStartPosition;

      uint64_t arcStartPos;
      arcStartPos = stream->find(header::kMarker, header::kMarkerSize, searchHeaderSizeLimit);
      if(arcStartPos == ::numeric_info::get_maximum_value < uint64_t >())
         return E_FAIL;
      m_Position = arcStartPos + header::kMarkerSize;
      try
      {
         stream->seek(m_Position, ::file::seek_begin);
      }
      catch(...)
      {
         return E_FAIL;
      }
      byte buf[header::archive::kArchiveHeaderSize + 1];

      RINOK(::file::read_false(stream, buf, header::archive::kArchiveHeaderSize));
      AddToSeekValue(header::archive::kArchiveHeaderSize);


      uint32_t blockSize = Get16(buf + 5);

      _header.EncryptVersion = 0;
      _header.Flags = Get16(buf + 3);

      uint32_t headerSize = header::archive::kArchiveHeaderSize;
      if (_header.IsThereEncryptVer())
      {
         if (blockSize <= headerSize)
            return S_FALSE;
         RINOK(::file::read_false(stream, buf + header::archive::kArchiveHeaderSize, 1));
         AddToSeekValue(1);
         _header.EncryptVersion = buf[header::archive::kArchiveHeaderSize];
         headerSize += 1;
      }
      if (blockSize < headerSize ||
         buf[2] != header::block_type::kArchiveHeader ||
         (uint32_t)Get16(buf) != (crc_calc(buf + 2, headerSize - 2) & 0xFFFF))
         return S_FALSE;

      ::primitive::memory_size commentSize = blockSize - headerSize;
      _comment.SetCapacity((size_t) commentSize);
      RINOK(::file::read_false(stream, _comment, commentSize));
      AddToSeekValue(commentSize);
      m_Stream = stream;
      _header.StartPosition = arcStartPos;
      return S_OK;
   }

   void input_file::GetArchiveInfo(input_file_info &archiveInfo) const
   {
      archiveInfo = _header;
   }

   static void DecodeUnicodeFileName(const char *name, const byte *encName, int32_t encSize, unichar *unicodeName, int32_t maxDecSize)
   {
      int32_t encPos = 0;
      int32_t decPos = 0;
      int32_t flagBits = 0;
      byte flags = 0;
      byte highByte = encName[encPos++];
      while (encPos < encSize && decPos < maxDecSize)
      {
         if (flagBits == 0)
         {
            flags = encName[encPos++];
            flagBits = 8;
         }
         switch(flags >> 6)
         {
         case 0:
            unicodeName[decPos++] = encName[encPos++];
            break;
         case 1:
            unicodeName[decPos++] = (unichar)(encName[encPos++] + (highByte << 8));
            break;
         case 2:
            unicodeName[decPos++] = (unichar)(encName[encPos] + (encName[encPos + 1] << 8));
            encPos += 2;
            break;
         case 3:
            {
               int32_t length = encName[encPos++];
               if (length & 0x80)
               {
                  byte correction = encName[encPos++];
                  for (length = (length & 0x7f) + 2;
                     length > 0 && decPos < maxDecSize; length--, decPos++)
                     unicodeName[decPos] = (unichar)(((name[decPos] + correction) & 0xff) + (highByte << 8));
               }
               else
                  for (length += 2; length > 0 && decPos < maxDecSize; length--, decPos++)
                     unicodeName[decPos] = name[decPos];
            }
            break;
         }
         flags <<= 2;
         flagBits -= 2;
      }
      unicodeName[decPos < maxDecSize ? decPos : maxDecSize - 1] = 0;
   }

   void input_file::ReadName(CItemEx &item, int32_t nameSize)
   {
      item.Name.Empty();
      if (nameSize > 0)
      {
         m_NameBuffer.EnsureCapacity(nameSize + 1);
         char *buffer = (char *)m_NameBuffer;

         for (int32_t i = 0; i < nameSize; i++)
            buffer[i] = ReadByte();

         int32_t mainLen;
         for (mainLen = 0; mainLen < nameSize; mainLen++)
            if (buffer[mainLen] == '\0')
               break;
         buffer[mainLen] = '\0';
         item.Name = buffer;

         if(item.HasUnicodeName())
         {
            if(mainLen < nameSize)
            {
               int32_t unicodeNameSizeMax = min(nameSize, (0x400));
               _unicodeNameBuffer.EnsureCapacity(unicodeNameSizeMax + 1);
               DecodeUnicodeFileName(buffer, (const byte *)buffer + mainLen + 1,
                  nameSize - (mainLen + 1), _unicodeNameBuffer, unicodeNameSizeMax);
               item.Name = ::str::international::unicode_to_utf8(_unicodeNameBuffer);
            }
         }
      }
      else
         item.Name.Empty();
   }

   byte input_file::ReadByte()
   {
      if (m_CurPos >= m_PosLimit)
         throw input_file_exception(get_app(), input_file_exception::kIncorrectArchive);
      return m_CurData[m_CurPos++];
   }

   uint16_t input_file::ReadUInt16()
   {
      uint16_t value = 0;
      for (int32_t i = 0; i < 2; i++)
      {
         byte b = ReadByte();
         value |= (uint16_t(b) << (8 * i));
      }
      return value;
   }

   uint32_t input_file::ReadUInt32()
   {
      uint32_t value = 0;
      for (int32_t i = 0; i < 4; i++)
      {
         byte b = ReadByte();
         value |= (uint32_t(b) << (8 * i));
      }
      return value;
   }

   void input_file::ReadTime(byte mask, CRarTime &rarTime)
   {
      rarTime.LowSecond = (byte)(((mask & 4) != 0) ? 1 : 0);
      int32_t numDigits = (mask & 3);
      rarTime.SubTime[0] = rarTime.SubTime[1] = rarTime.SubTime[2] = 0;
      for (int32_t i = 0; i < numDigits; i++)
         rarTime.SubTime[3 - numDigits + i] = ReadByte();
   }

   void input_file::ReadHeaderReal(CItemEx &item)
   {
      item.Flags = m_BlockHeader.Flags;
      item.PackSize = ReadUInt32();
      item.Size = ReadUInt32();
      item.HostOS = ReadByte();
      item.FileCRC = ReadUInt32();
      item.MTime.DosTime = ReadUInt32();
      item.UnPackVersion = ReadByte();
      item.Method = ReadByte();
      int32_t nameSize = ReadUInt16();
      item.Attrib = ReadUInt32();

      item.MTime.LowSecond = 0;
      item.MTime.SubTime[0] =
         item.MTime.SubTime[1] =
         item.MTime.SubTime[2] = 0;

      if((item.Flags & header::file::kSize64Bits) != 0)
      {
         item.PackSize |= ((uint64_t)ReadUInt32() << 32);
         item.Size |= ((uint64_t)ReadUInt32() << 32);
      }

      ReadName(item, nameSize);

      if (item.HasSalt())
         for (int32_t i = 0; i < sizeof(item.Salt); i++)
            item.Salt[i] = ReadByte();

      // some rar archives have HasExtTime flag without field.
      if (m_CurPos < m_PosLimit && item.HasExtTime())
      {
         byte accessMask = (byte)(ReadByte() >> 4);
         byte b = ReadByte();
         byte modifMask = (byte)(b >> 4);
         byte createMask = (byte)(b & 0xF);
         if ((modifMask & 8) != 0)
            ReadTime(modifMask, item.MTime);
         item.CTimeDefined = ((createMask & 8) != 0);
         if (item.CTimeDefined)
         {
            item.CTime.DosTime = ReadUInt32();
            ReadTime(createMask, item.CTime);
         }
         item.ATimeDefined = ((accessMask & 8) != 0);
         if (item.ATimeDefined)
         {
            item.ATime.DosTime = ReadUInt32();
            ReadTime(accessMask, item.ATime);
         }
      }

      uint16_t fileHeaderWithNameSize = (uint16_t)m_CurPos;

      item.Position = m_Position;
      item.MainPartSize = fileHeaderWithNameSize;
      item.CommentSize = (uint16_t)(m_BlockHeader.HeadSize - fileHeaderWithNameSize);

      if (m_CryptoMode)
         item.AlignSize = (uint16_t)((16 - ((m_BlockHeader.HeadSize) & 0xF)) & 0xF);
      else
         item.AlignSize = 0;
      AddToSeekValue(m_BlockHeader.HeadSize);
   }

   void input_file::AddToSeekValue(uint64_t addValue)
   {
      m_Position += addValue;
   }

   HRESULT input_file::GetNextItem(CItemEx &item, ::crypto::get_text_password_interface *getTextPassword, bool &decryptionError, string &errorMessage)
   {
      decryptionError = false;
      for (;;)
      {
         SeekInArchive(m_Position);
         if (!m_CryptoMode && (_header.Flags &
            header::archive::kBlockHeadersAreEncrypted) != 0)
         {
            m_CryptoMode = false;
            if (getTextPassword == 0)
               return S_FALSE;
            if (!m_RarAES)
            {
               m_RarAESSpec = new ::crypto::rar29::decoder;
               m_RarAES = m_RarAESSpec;
            }
            m_RarAESSpec->SetRar350Mode(_header.IsEncryptOld());

            // Salt
            const uint32_t kSaltSize = 8;
            byte salt[kSaltSize];
            if(!ReadBytesAndTestSize(salt, kSaltSize))
               return S_FALSE;
            m_Position += kSaltSize;
            RINOK(m_RarAESSpec->SetDecoderProperties2(salt, kSaltSize))
               // Password
            string password;
            RINOK(getTextPassword->CryptoGetTextPassword(password))
            wstring unicodePassword = ::str::international::utf8_to_unicode(password);

            ::file::byte_buffer buffer;
            const uint32_t sizeInBytes = (const uint32_t) (unicodePassword.get_length() * 2);
            buffer.SetCapacity(sizeInBytes);
            for (int32_t i = 0; i < unicodePassword.get_length(); i++)
            {
               unichar ca = unicodePassword[i];
               ((byte *)buffer)[i * 2] = (byte)ca;
               ((byte *)buffer)[i * 2 + 1] = (byte)(ca >> 8);
            }

            RINOK(m_RarAESSpec->CryptoSetPassword((const byte *)buffer, sizeInBytes));

            const uint32_t kDecryptedBufferSize = (1 << 12);
            if (m_DecryptedData.GetCapacity() == 0)
            {
               const uint32_t kAlign = 16;
               m_DecryptedData.SetCapacity(kDecryptedBufferSize + kAlign);
               m_DecryptedDataAligned = (byte *)((ptrdiff_t)((byte *)m_DecryptedData + kAlign - 1) & ~(ptrdiff_t)(kAlign - 1));
            }
            RINOK(m_RarAES->Init());
            ::primitive::memory_size decryptedDataSizeT = kDecryptedBufferSize;
            RINOK(::file::read(m_Stream, m_DecryptedDataAligned, &decryptedDataSizeT));
            m_DecryptedDataSize = (uint32_t)decryptedDataSizeT;
            m_DecryptedDataSize = m_RarAES->Filter(m_DecryptedDataAligned, (uint32_t) m_DecryptedDataSize);

            m_CryptoMode = true;
            m_CryptoPos = 0;
         }

         m_FileHeaderData.EnsureCapacity(7);
         ::primitive::memory_size processed = 7;
         RINOK(ReadBytesSpec((byte *)m_FileHeaderData, &processed));
         if (processed != 7)
         {
            if (processed != 0)
               errorMessage = k_UnexpectedEnd;
            return S_FALSE;
         }

         m_CurData = (byte *)m_FileHeaderData;
         m_CurPos = 0;
         m_PosLimit = 7;
         m_BlockHeader.CRC = ReadUInt16();
         m_BlockHeader.Type = ReadByte();
         m_BlockHeader.Flags = ReadUInt16();
         m_BlockHeader.HeadSize = ReadUInt16();

         if (m_BlockHeader.HeadSize < 7)
            ThrowExceptionWithCode(input_file_exception::kIncorrectArchive);

         if (m_BlockHeader.Type == header::block_type::kEndOfArchive)
            return S_FALSE;

         if (m_BlockHeader.Type == header::block_type::kFileHeader)
         {
            m_FileHeaderData.EnsureCapacity(m_BlockHeader.HeadSize);
            m_CurData = (byte *)m_FileHeaderData;
            m_PosLimit = m_BlockHeader.HeadSize;
            if (!ReadBytesAndTestSize(m_CurData + m_CurPos, m_BlockHeader.HeadSize - 7))
            {
               errorMessage = k_UnexpectedEnd;
               return S_FALSE;
            }

            ReadHeaderReal(item);
            if ((crc_calc(m_CurData + 2,
               m_BlockHeader.HeadSize - item.CommentSize - 2) & 0xFFFF) != m_BlockHeader.CRC)
               ThrowExceptionWithCode(input_file_exception::kFileHeaderCRCError);

            FinishCryptoBlock();
            m_CryptoMode = false;
            SeekInArchive(m_Position); // Move Position to compressed Data;
            AddToSeekValue(item.PackSize);  // m_Position points to next header;
            return S_OK;
         }
         if (m_CryptoMode && m_BlockHeader.HeadSize > (1 << 10))
         {
            decryptionError = true;
            errorMessage = k_DecryptionError;
            return S_FALSE;
         }
         if ((m_BlockHeader.Flags & header::NBlock::kLongBlock) != 0)
         {
            m_FileHeaderData.EnsureCapacity(7 + 4);
            m_CurData = (byte *)m_FileHeaderData;
            if (!ReadBytesAndTestSize(m_CurData + m_CurPos, 4))
            {
               errorMessage = k_UnexpectedEnd;
               return S_FALSE;
            }
            m_PosLimit = 7 + 4;
            uint32_t dataSize = ReadUInt32();
            AddToSeekValue(dataSize);
            if (m_CryptoMode && dataSize > (1 << 27))
            {
               decryptionError = true;
               errorMessage = k_DecryptionError;
               return S_FALSE;
            }
            m_CryptoPos = m_BlockHeader.HeadSize;
         }
         else
            m_CryptoPos = 0;
         AddToSeekValue(m_BlockHeader.HeadSize);
         FinishCryptoBlock();
         m_CryptoMode = false;
      }
   }

   void input_file::SeekInArchive(file_position position)
   {
      m_Stream->seek((file_offset) position, ::file::seek_begin);
   }

   ::file::reader* input_file::CreateLimitedStream(file_position position, file_size size)
   {
      ::file::limited_reader *streamSpec = new ::file::limited_reader;
      ::file::reader * inStream = streamSpec;
      SeekInArchive(position);
      streamSpec->SetStream(m_Stream);
      streamSpec->Init(size);
      return inStream;
   }

} // namespace rar

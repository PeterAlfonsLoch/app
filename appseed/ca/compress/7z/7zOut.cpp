// 7zOut.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"

/*#include "../../../../C/7zCrc.h"

#include "../../../Common/AutoPtr.h"

#include "../../Common/StreamObjects.h"

#include "7zOut.h"
*/
static HRESULT WriteBytes(::ex1::writer *stream, const void *data, ::primitive::memory_size size)
{
   while (size > 0)
   {
      ::primitive::memory_size curSize = size;
      ::primitive::memory_size processedSize;
      stream->write(data, curSize, &processedSize);
      if (processedSize == 0)
         return E_FAIL;
      data = (const void *)((const byte *)data + processedSize);
      size -= processedSize;
   }
   return S_OK;
}


namespace n7z
{
   COutArchive::COutArchive(::ca::application * papp) :
      ca(papp)
   {
     _outByte.create(1 << 16); 
   }


   HRESULT COutArchive::WriteDirect(const void *data, uint32 size)
   {
      return ::WriteBytes(SeqStream, data, size);
   }

   HRESULT COutArchive::WriteSignature()
   {
      byte buf[8];
      memcpy(buf, kSignature, kSignatureSize);
      buf[kSignatureSize] = kMajorVersion;
      buf[kSignatureSize + 1] = 3;
      return WriteDirect(buf, 8);
   }

#ifdef _7Z_VOL
   HRESULT COutArchive::WriteFinishSignature()
   {
      RINOK(WriteDirect(kFinishSignature, kSignatureSize));
      CArchiveVersion av;
      av.Major = kMajorVersion;
      av.Minor = 2;
      RINOK(WriteDirectByte(av.Major));
      return WriteDirectByte(av.Minor);
   }
#endif

   static void SetUInt32(byte *p, uint32 d)
   {
      for (int i = 0; i < 4; i++, d >>= 8)
         p[i] = (byte)d;
   }

   static void SetUInt64(byte *p, uint64 d)
   {
      for (int i = 0; i < 8; i++, d >>= 8)
         p[i] = (byte)d;
   }

   HRESULT COutArchive::WriteStartHeader(const CStartHeader &h)
   {
      byte buf[24];
      SetUInt64(buf + 4, h.NextHeaderOffset);
      SetUInt64(buf + 12, h.NextHeaderSize);
      SetUInt32(buf + 20, h.NextHeaderCRC);
      SetUInt32(buf, crc_calc(buf + 4, 20));
      return WriteDirect(buf, 24);
   }

#ifdef _7Z_VOL
   HRESULT COutArchive::WriteFinishHeader(const CFinishHeader &h)
   {
      CCRC crc;
      crc.UpdateUInt64(h.NextHeaderOffset);
      crc.UpdateUInt64(h.NextHeaderSize);
      crc.UpdateUInt32(h.NextHeaderCRC);
      crc.UpdateUInt64(h.ArchiveStartOffset);
      crc.UpdateUInt64(h.AdditionalStartBlockSize);
      RINOK(WriteDirectUInt32(crc.GetDigest()));
      RINOK(WriteDirectUInt64(h.NextHeaderOffset));
      RINOK(WriteDirectUInt64(h.NextHeaderSize));
      RINOK(WriteDirectUInt32(h.NextHeaderCRC));
      RINOK(WriteDirectUInt64(h.ArchiveStartOffset));
      return WriteDirectUInt64(h.AdditionalStartBlockSize);
   }
#endif

   HRESULT COutArchive::Create(::ex1::writer *stream, bool endMarker)
   {
      Close();
#ifdef _7Z_VOL
      // endMarker = false;
      _endMarker = endMarker;
#endif
      SeqStream = stream;
      if (!endMarker)
      {
         Stream = dynamic_cast < ::ex1::byte_output_stream * > (SeqStream.m_p);
         if (!Stream)
         {
            return E_NOTIMPL;
            // endMarker = true;
         }
      }
#ifdef _7Z_VOL
      if (endMarker)
      {
         /*
         CStartHeader sh;
         sh.NextHeaderOffset = (uint32)(Int32)-1;
         sh.NextHeaderSize = (uint32)(Int32)-1;
         sh.NextHeaderCRC = 0;
         WriteStartHeader(sh);
         */
      }
      else
#endif
      {
         if (!Stream)
            return E_FAIL;
         RINOK(WriteSignature());
         _prefixHeaderPos = Stream->seek(0, ex1::seek_current);
      }
      return S_OK;
   }

   void COutArchive::Close()
   {
      gen::release(SeqStream.m_p);
      gen::release(Stream.m_p);
   }

   HRESULT COutArchive::SkipPrefixArchiveHeader()
   {
#ifdef _7Z_VOL
      if (_endMarker)
         return S_OK;
#endif
      Stream->seek(24, ex1::seek_current);
      return S_OK;
   }

   uint64 COutArchive::GetPos() const
   {
      if (_countMode)
         return _countSize;
      if (_writeToStream)
         return _outByte.GetProcessedSize();
      return _outByte2.GetPos();
   }

   void COutArchive::WriteBytes(const void *data, size_t size)
   {
      if (_countMode)
         _countSize += size;
      else if (_writeToStream)
      {
         _outByte.WriteBytes(data, size);
         _crc = crc_update(_crc, data, size);
      }
      else
         _outByte2.WriteBytes(data, size);
   }

   void COutArchive::WriteByte(byte b)
   {
      if (_countMode)
         _countSize++;
      else if (_writeToStream)
      {
         _outByte.WriteByte(b);
         _crc = CRC_UPDATE_BYTE(_crc, b);
      }
      else
         _outByte2.WriteByte(b);
   }

   void COutArchive::WriteUInt32(uint32 value)
   {
      for (int i = 0; i < 4; i++)
      {
         WriteByte((byte)value);
         value >>= 8;
      }
   }

   void COutArchive::WriteUInt64(uint64 value)
   {
      for (int i = 0; i < 8; i++)
      {
         WriteByte((byte)value);
         value >>= 8;
      }
   }

   void COutArchive::WriteNumber(uint64 value)
   {
      byte firstByte = 0;
      byte mask = 0x80;
      int i;
      for (i = 0; i < 8; i++)
      {
         if (value < ((uint64(1) << ( 7  * (i + 1)))))
         {
            firstByte |= byte(value >> (8 * i));
            break;
         }
         firstByte |= mask;
         mask >>= 1;
      }
      WriteByte(firstByte);
      for (;i > 0; i--)
      {
         WriteByte((byte)value);
         value >>= 8;
      }
   }

   static uint32 GetBigNumberSize(uint64 value)
   {
      int i;
      for (i = 1; i < 9; i++)
         if (value < (((uint64)1 << (i * 7))))
            break;
      return i;
   }

#ifdef _7Z_VOL
   uint32 COutArchive::GetVolHeadersSize(uint64 dataSize, int nameLength, bool props)
   {
      uint32 result = GetBigNumberSize(dataSize) * 2 + 41;
      if (nameLength != 0)
      {
         nameLength = (nameLength + 1) * 2;
         result += nameLength + GetBigNumberSize(nameLength) + 2;
      }
      if (props)
      {
         result += 20;
      }
      if (result >= 128)
         result++;
      result += kSignatureSize + 2 + kFinishHeaderSize;
      return result;
   }

   uint64 COutArchive::GetVolPureSize(uint64 volSize, int nameLength, bool props)
   {
      uint32 headersSizeBase = COutArchive::GetVolHeadersSize(1, nameLength, props);
      int testSize;
      if (volSize > headersSizeBase)
         testSize = volSize - headersSizeBase;
      else
         testSize = 1;
      uint32 headersSize = COutArchive::GetVolHeadersSize(testSize, nameLength, props);
      uint64 pureSize = 1;
      if (volSize > headersSize)
         pureSize = volSize - headersSize;
      return pureSize;
   }
#endif

   void COutArchive::WriteFolder(const CFolder &folder)
   {
      WriteNumber(folder.Coders.get_count());
      int i;
      for (i = 0; i < folder.Coders.get_count(); i++)
      {
         const CCoderInfo &coder = folder.Coders[i];
         {
            size_t propsSize = coder.Props.GetCapacity();

            uint64 id = coder.MethodID;
            int idSize;
            for (idSize = 1; idSize < sizeof(id); idSize++)
               if ((id >> (8 * idSize)) == 0)
                  break;
            BYTE longID[15];
            for (int t = idSize - 1; t >= 0 ; t--, id >>= 8)
               longID[t] = (byte)(id & 0xFF);
            byte b;
            b = (byte)(idSize & 0xF);
            bool isComplex = !coder.IsSimpleCoder();
            b |= (isComplex ? 0x10 : 0);
            b |= ((propsSize != 0) ? 0x20 : 0 );
            WriteByte(b);
            WriteBytes(longID, idSize);
            if (isComplex)
            {
               WriteNumber(coder.NumInStreams);
               WriteNumber(coder.NumOutStreams);
            }
            if (propsSize == 0)
               continue;
            WriteNumber(propsSize);
            WriteBytes(coder.Props, propsSize);
         }
      }
      for (i = 0; i < folder.BindPairs.get_count(); i++)
      {
         const CBindPair &bindPair = folder.BindPairs[i];
         WriteNumber(bindPair.InIndex);
         WriteNumber(bindPair.OutIndex);
      }
      if (folder.PackStreams.get_count() > 1)
         for (i = 0; i < folder.PackStreams.get_count(); i++)
         {
            WriteNumber(folder.PackStreams[i]);
         }
   }

   void COutArchive::WriteBoolVector(const bool_array &boolVector)
   {
      byte b = 0;
      byte mask = 0x80;
      for (int i = 0; i < boolVector.get_count(); i++)
      {
         if (boolVector[i])
            b |= mask;
         mask >>= 1;
         if (mask == 0)
         {
            WriteByte(b);
            mask = 0x80;
            b = 0;
         }
      }
      if (mask != 0x80)
         WriteByte(b);
   }


   void COutArchive::WriteHashDigests(
      const bool_array &digestsDefined,
      const base_array<uint32> &digests)
   {
      int numDefined = 0;
      int i;
      for (i = 0; i < digestsDefined.get_count(); i++)
         if (digestsDefined[i])
            numDefined++;
      if (numDefined == 0)
         return;

      WriteByte(NID::kCRC);
      if (numDefined == digestsDefined.get_count())
         WriteByte(1);
      else
      {
         WriteByte(0);
         WriteBoolVector(digestsDefined);
      }
      for (i = 0; i < digests.get_count(); i++)
         if (digestsDefined[i])
            WriteUInt32(digests[i]);
   }

   void COutArchive::WritePackInfo(
      uint64 dataOffset,
      const base_array<file_size> &packSizes,
      const bool_array &packCRCsDefined,
      const base_array<uint32> &packCRCs)
   {
      if (packSizes.is_empty())
         return;
      WriteByte(NID::kPackInfo);
      WriteNumber(dataOffset);
      WriteNumber(packSizes.get_count());
      WriteByte(NID::kSize);
      for (int i = 0; i < packSizes.get_count(); i++)
         WriteNumber(packSizes[i]);

      WriteHashDigests(packCRCsDefined, packCRCs);

      WriteByte(NID::kEnd);
   }

   void COutArchive::WriteUnpackInfo(const array_ptr_alloc<CFolder> &folders)
   {
      if (folders.is_empty())
         return;

      WriteByte(NID::kUnpackInfo);

      WriteByte(NID::kFolder);
      WriteNumber(folders.get_count());
      {
         WriteByte(0);
         for (int i = 0; i < folders.get_count(); i++)
            WriteFolder(folders[i]);
      }

      WriteByte(NID::kCodersUnpackSize);
      int i;
      for (i = 0; i < folders.get_count(); i++)
      {
         const CFolder &folder = folders[i];
         for (int j = 0; j < folder.UnpackSizes.get_count(); j++)
            WriteNumber(folder.UnpackSizes[j]);
      }

      bool_array unpackCRCsDefined;
      base_array<uint32> unpackCRCs;
      for (i = 0; i < folders.get_count(); i++)
      {
         const CFolder &folder = folders[i];
         unpackCRCsDefined.add(folder.UnpackCRCDefined);
         unpackCRCs.add(folder.UnpackCRC);
      }
      WriteHashDigests(unpackCRCsDefined, unpackCRCs);

      WriteByte(NID::kEnd);
   }

   void COutArchive::WriteSubStreamsInfo(
      const array_ptr_alloc<CFolder> &folders,
      const base_array<CNum> &numUnpackStreamsInFolders,
      const base_array<file_size> &unpackSizes,
      const bool_array &digestsDefined,
      const base_array<uint32> &digests)
   {
      WriteByte(NID::kSubStreamsInfo);

      int i;
      for (i = 0; i < numUnpackStreamsInFolders.get_count(); i++)
      {
         if (numUnpackStreamsInFolders[i] != 1)
         {
            WriteByte(NID::kNumUnpackStream);
            for (i = 0; i < numUnpackStreamsInFolders.get_count(); i++)
               WriteNumber(numUnpackStreamsInFolders[i]);
            break;
         }
      }


      bool needFlag = true;
      CNum index = 0;
      for (i = 0; i < numUnpackStreamsInFolders.get_count(); i++)
         for (CNum j = 0; j < numUnpackStreamsInFolders[i]; j++)
         {
            if (j + 1 != numUnpackStreamsInFolders[i])
            {
               if (needFlag)
                  WriteByte(NID::kSize);
               needFlag = false;
               WriteNumber(unpackSizes[index]);
            }
            index++;
         }

         bool_array digestsDefined2;
         base_array<uint32> digests2;

         int digestIndex = 0;
         for (i = 0; i < folders.get_count(); i++)
         {
            int numSubStreams = (int)numUnpackStreamsInFolders[i];
            if (numSubStreams == 1 && folders[i].UnpackCRCDefined)
               digestIndex++;
            else
               for (int j = 0; j < numSubStreams; j++, digestIndex++)
               {
                  digestsDefined2.add(digestsDefined[digestIndex]);
                  digests2.add(digests[digestIndex]);
               }
         }
         WriteHashDigests(digestsDefined2, digests2);
         WriteByte(NID::kEnd);
   }

   void COutArchive::SkipAlign(unsigned /* pos */, unsigned /* alignSize */)
   {
      return;
   }

   /*
   7-Zip 4.50 - 4.58 contain BUG, so they do not support .7z archives with Unknown field.

   void COutArchive::SkipAlign(unsigned pos, unsigned alignSize)
   {
   pos += (unsigned)GetPos();
   pos &= (alignSize - 1);
   if (pos == 0)
   return;
   unsigned skip = alignSize - pos;
   if (skip < 2)
   skip += alignSize;
   skip -= 2;
   WriteByte(NID::kDummy);
   WriteByte((byte)skip);
   for (unsigned i = 0; i < skip; i++)
   WriteByte(0);
   }
   */

   static inline unsigned Bv_GetSizeInBytes(const bool_array &v) { return ((unsigned)v.get_count() + 7) / 8; }

   void COutArchive::WriteAlignedBoolHeader(const bool_array &v, int numDefined, byte type, unsigned itemSize)
   {
      const unsigned bvSize = (numDefined == v.get_count()) ? 0 : Bv_GetSizeInBytes(v);
      const uint64 dataSize = (uint64)numDefined * itemSize + bvSize + 2;
      SkipAlign(3 + (unsigned)bvSize + (unsigned)GetBigNumberSize(dataSize), itemSize);

      WriteByte(type);
      WriteNumber(dataSize);
      if (numDefined == v.get_count())
         WriteByte(1);
      else
      {
         WriteByte(0);
         WriteBoolVector(v);
      }
      WriteByte(0);
   }

   void COutArchive::WriteUInt64DefVector(const CUInt64DefVector &v, byte type)
   {
      int numDefined = 0;

      int i;
      for (i = 0; i < v.Defined.get_count(); i++)
         if (v.Defined[i])
            numDefined++;

      if (numDefined == 0)
         return;

      WriteAlignedBoolHeader(v.Defined, numDefined, type, 8);

      for (i = 0; i < v.Defined.get_count(); i++)
         if (v.Defined[i])
            WriteUInt64(v.Values[i]);
   }

   HRESULT COutArchive::EncodeStream(
      ::compress::codecs_info_interface * codecsInfo,
      const base_array < ::compress::codec_info_ex > * externalCodecs,
      CEncoder & encoder,
      const ::ex1::byte_buffer & data,
      base_array < file_size > & packSizes,
      array_ptr_alloc < CFolder > & folders)
   {
      UNREFERENCED_PARAMETER(codecsInfo);
      UNREFERENCED_PARAMETER(externalCodecs);
      UNREFERENCED_PARAMETER(encoder);
      UNREFERENCED_PARAMETER(packSizes);
      throw "implement below";
      //CBufInStream *streamSpec = new CBufInStream;
      //::ca::smart_pointer<::ex1::reader> stream = streamSpec;
      //streamSpec->Init(data, data.GetCapacity());
      CFolder folderItem;
      folderItem.UnpackCRCDefined = true;
      folderItem.UnpackCRC = crc_calc(data, data.GetCapacity());
      //  uint64 dataSize64 = data.GetCapacity();
      throw "uncomment below if implement above";
      /*  RINOK(encoder.Encode(
      codecsInfo, externalCodecs,
      stream, NULL, &dataSize64, folderItem, SeqStream, packSizes, NULL))*/
      folders.add(folderItem);
      return S_OK;
   }

   void COutArchive::WriteHeader(
      const CArchiveDatabase &db,
      const CHeaderOptions &headerOptions,
      uint64 &headerOffset)
   {
      int i;

      uint64 packedSize = 0;
      for (i = 0; i < db.PackSizes.get_count(); i++)
         packedSize += db.PackSizes[i];

      headerOffset = packedSize;

      WriteByte(NID::kHeader);

      // Archive Properties

      if (db.Folders.get_count() > 0)
      {
         WriteByte(NID::kMainStreamsInfo);
         WritePackInfo(0, db.PackSizes,
            db.PackCRCsDefined,
            db.PackCRCs);

         WriteUnpackInfo(db.Folders);

         base_array<file_size> unpackSizes;
         bool_array digestsDefined;
         base_array<uint32> digests;
         for (i = 0; i < db.Files.get_count(); i++)
         {
            const CFileItem &file = db.Files[i];
            if (!file.HasStream)
               continue;
            unpackSizes.add(file.get_count);
            digestsDefined.add(file.CrcDefined);
            digests.add(file.Crc);
         }

         WriteSubStreamsInfo(
            db.Folders,
            db.NumUnpackStreamsVector,
            unpackSizes,
            digestsDefined,
            digests);
         WriteByte(NID::kEnd);
      }

      if (db.Files.is_empty())
      {
         WriteByte(NID::kEnd);
         return;
      }

      WriteByte(NID::kFilesInfo);
      WriteNumber(db.Files.get_count());

      {
         /* ---------- Empty Streams ---------- */
         bool_array emptyStreamVector;
         emptyStreamVector.set_size(0, db.Files.get_count());
         int numEmptyStreams = 0;
         for (i = 0; i < db.Files.get_count(); i++)
            if (db.Files[i].HasStream)
               emptyStreamVector.add(false);
            else
            {
               emptyStreamVector.add(true);
               numEmptyStreams++;
            }
            if (numEmptyStreams > 0)
            {
               WriteByte(NID::kEmptyStream);
               WriteNumber(Bv_GetSizeInBytes(emptyStreamVector));
               WriteBoolVector(emptyStreamVector);

               bool_array emptyFileVector, antiVector;
               emptyFileVector.set_size(0, numEmptyStreams);
               antiVector.set_size(0, numEmptyStreams);
               CNum numEmptyFiles = 0, numAntiItems = 0;
               for (i = 0; i < db.Files.get_count(); i++)
               {
                  const CFileItem &file = db.Files[i];
                  if (!file.HasStream)
                  {
                     emptyFileVector.add(!file.IsDir);
                     if (!file.IsDir)
                        numEmptyFiles++;
                     bool isAnti = db.IsItemAnti(i);
                     antiVector.add(isAnti);
                     if (isAnti)
                        numAntiItems++;
                  }
               }

               if (numEmptyFiles > 0)
               {
                  WriteByte(NID::kEmptyFile);
                  WriteNumber(Bv_GetSizeInBytes(emptyFileVector));
                  WriteBoolVector(emptyFileVector);
               }

               if (numAntiItems > 0)
               {
                  WriteByte(NID::kAnti);
                  WriteNumber(Bv_GetSizeInBytes(antiVector));
                  WriteBoolVector(antiVector);
               }
            }
      }


      {
         /* ---------- Names ---------- */

         int numDefined = 0;
         size_t namesDataSize = 0;
         for (int i = 0; i < db.Files.get_count(); i++)
         {
            const string &name = db.Files[i].Name;
            if (!name.is_empty())
               numDefined++;
            namesDataSize += (name.get_length() + 1) * 2;
         }

         if (numDefined > 0)
         {
            namesDataSize++;
            SkipAlign(2 + GetBigNumberSize(namesDataSize), 2);

            WriteByte(NID::kName);
            WriteNumber(namesDataSize);
            WriteByte(0);
            for (int i = 0; i < db.Files.get_count(); i++)
            {
               const string &name = db.Files[i].Name;
               for (int t = 0; t <= name.get_length(); t++)
               {
                  wchar_t c = name[t];
                  WriteByte((byte)c);
                  WriteByte((byte)(c >> 8));
               }
            }
         }
      }

      if (headerOptions.WriteCTime) WriteUInt64DefVector(db.CTime, NID::kCTime);
      if (headerOptions.WriteATime) WriteUInt64DefVector(db.ATime, NID::kATime);
      if (headerOptions.WriteMTime) WriteUInt64DefVector(db.MTime, NID::kMTime);
      WriteUInt64DefVector(db.StartPos, NID::kStartPos);

      {
         /* ---------- Write Attrib ---------- */
         bool_array boolVector;
         boolVector.set_size(0, db.Files.get_count());
         int numDefined = 0;
         for (i = 0; i < db.Files.get_count(); i++)
         {
            bool defined = db.Files[i].AttribDefined;
            boolVector.add(defined);
            if (defined)
               numDefined++;
         }
         if (numDefined > 0)
         {
            WriteAlignedBoolHeader(boolVector, numDefined, NID::kWinAttributes, 4);
            for (i = 0; i < db.Files.get_count(); i++)
            {
               const CFileItem &file = db.Files[i];
               if (file.AttribDefined)
                  WriteUInt32(file.Attrib);
            }
         }
      }

      WriteByte(NID::kEnd); // for files
      WriteByte(NID::kEnd); // for headers
   }

   HRESULT COutArchive::WriteDatabase(
      ::compress::codecs_info_interface *codecsInfo,
      const base_array < ::compress::codec_info_ex > *externalCodecs,
      const CArchiveDatabase & db,
      const CCompressionMethodMode * options,
      const CHeaderOptions & headerOptions)
   {
      if (!db.CheckNumFiles())
         return E_FAIL;

      uint64 headerOffset;
      uint32 headerCRC;
      uint64 headerSize;
      if (db.is_empty())
      {
         headerSize = 0;
         headerOffset = 0;
         headerCRC = crc_calc(0, 0);
      }
      else
      {
         bool encodeHeaders = false;
         if (options != 0)
            if (options->is_empty())
               options = 0;
         if (options != 0)
            if (options->PasswordIsDefined || headerOptions.CompressMainHeader)
               encodeHeaders = true;

         _outByte.SetStream(SeqStream);
         _outByte.Init();
         _crc = CRC_INIT_VAL;
         _countMode = encodeHeaders;
         _writeToStream = true;
         _countSize = 0;
         WriteHeader(db, headerOptions, headerOffset);

         if (encodeHeaders)
         {
            ::ex1::byte_buffer buf;
            buf.SetCapacity(_countSize);
            _outByte2.Init((byte *)buf, _countSize);

            _countMode = false;
            _writeToStream = false;
            WriteHeader(db, headerOptions, headerOffset);

            if (_countSize != _outByte2.GetPos())
               return E_FAIL;

            CCompressionMethodMode encryptOptions;
            encryptOptions.PasswordIsDefined = options->PasswordIsDefined;
            encryptOptions.Password = options->Password;
            CEncoder encoder(get_app(), headerOptions.CompressMainHeader ? *options : encryptOptions);
            base_array<file_size> packSizes;
            array_ptr_alloc<CFolder> folders;
            RINOK(EncodeStream(
               codecsInfo, externalCodecs,
               encoder, buf,
               packSizes, folders));

            _writeToStream = true;

            if (folders.get_count() == 0)
               throw 1;

            WriteID(NID::kEncodedHeader);
            WritePackInfo(headerOffset, packSizes,
               bool_array(), base_array<uint32>());
            WriteUnpackInfo(folders);
            WriteByte(NID::kEnd);
            for (int i = 0; i < packSizes.get_count(); i++)
               headerOffset += packSizes[i];
         }
         RINOK(_outByte.Flush());
         headerCRC = CRC_GET_DIGEST(_crc);
         headerSize = _outByte.GetProcessedSize();
      }
#ifdef _7Z_VOL
      if (_endMarker)
      {
         CFinishHeader h;
         h.NextHeaderSize = headerSize;
         h.NextHeaderCRC = headerCRC;
         h.NextHeaderOffset =
            uint64(0) - (headerSize +
            4 + kFinishHeaderSize);
         h.ArchiveStartOffset = h.NextHeaderOffset - headerOffset;
         h.AdditionalStartBlockSize = 0;
         RINOK(WriteFinishHeader(h));
         return WriteFinishSignature();
      }
      else
#endif
      {
         CStartHeader h;
         h.NextHeaderSize = headerSize;
         h.NextHeaderCRC = headerCRC;
         h.NextHeaderOffset = headerOffset;
         Stream->seek(_prefixHeaderPos, ex1::seek_begin);
         return WriteStartHeader(h);
      }
   }

   void CArchiveDatabase::GetFile(index index, CFileItem &file, CFileItem2 &file2) const
   {

      file = Files[index];
      file2.CTimeDefined = CTime.GetItem(index, file2.CTime);
      file2.ATimeDefined = ATime.GetItem(index, file2.ATime);
      file2.MTimeDefined = MTime.GetItem(index, file2.MTime);
      file2.StartPosDefined = StartPos.GetItem(index, file2.StartPos);
      file2.IsAnti = IsItemAnti(index);

   }

   void CArchiveDatabase::AddFile(const CFileItem &file, const CFileItem2 &file2)
   {

      count index = Files.get_count();

      CTime.SetItem(index, file2.CTimeDefined, file2.CTime);
      ATime.SetItem(index, file2.ATimeDefined, file2.ATime);
      MTime.SetItem(index, file2.MTimeDefined, file2.MTime);
      StartPos.SetItem(index, file2.StartPosDefined, file2.StartPos);
      SetItemAnti(index, file2.IsAnti);
      Files.add(file);

   }

} // namespace n7z

// RarHandler.cpp

#include "StdAfx.h"
#include "../prop_id.h"

/*#include "Common/ComTry.h"
#include "Common/IntToString.h"
#include "Common/StringConvert.h"

#include "Windows/PropVariant.h"
#include "Windows/PropVariantUtils.h"
#include "Windows/Time.h"

#include "../../IPassword.h"

#include "../../Common/CreateCoder.h"
#include "../../Common/FilterCoder.h"
#include "../../Common/MethodId.h"
#include "../../Common/ProgressUtils.h"

#include "../../Compress/CopyCoder.h"

#include "../../Crypto/Rar20Crypto.h"
#include "../../Crypto/RarAes.h"

#include "../Common/ItemNameUtils.h"
#include "../Common/OutStreamWithCRC.h"

#include "RarHandler.h"

using namespace NWindows;
using namespace NTime;*/



namespace rar
{

   static const wchar_t *kHostOS[] =
   {
      L"MS DOS",
      L"OS/2",
      L"Win32",
      L"Unix",
      L"Mac OS",
      L"BeOS"
   };

   static const int kNumHostOSes = sizeof(kHostOS) / sizeof(kHostOS[0]);

   static const wchar_t *kUnknownOS = L"Unknown";

   static const CUInt32PCharPair k_Flags[] =
   {
      { 0, "Volume" },
      { 1, "Comment" },
      { 2, "lock" },
      { 3, "Solid" },
      { 4, "NewVolName" }, // pack_comment in old versuons
      { 5, "Authenticity" },
      { 6, "Recovery" },
      { 7, "BlockEncryption" },
      { 8, "FirstVolume" },
      { 9, "EncryptVer" }
   };


   static const stat_prop_stg kProps[] =
   {
      { NULL, ::compress::kpidPath, var::type_string},
      { NULL, ::compress::kpidIsDir, var::type_bool},
      { NULL, ::compress::kpidSize, var::type_uint64},
      { NULL, ::compress::kpidPackSize, var::type_uint64},
      { NULL, ::compress::kpidMTime, var::type_filetime},
      { NULL, ::compress::kpidCTime, var::type_filetime},
      { NULL, ::compress::kpidATime, var::type_filetime},
      { NULL, ::compress::kpidAttrib, var::type_uint},

      { NULL, ::compress::kpidEncrypted, var::type_bool},
      { NULL, ::compress::kpidSolid, var::type_bool},
      { NULL, ::compress::kpidCommented, var::type_bool},
      { NULL, ::compress::kpidSplitBefore, var::type_bool},
      { NULL, ::compress::kpidSplitAfter, var::type_bool},
      { NULL, ::compress::kpidCRC, var::type_uint},
      { NULL, ::compress::kpidHostOS, var::type_string},
      { NULL, ::compress::kpidMethod, var::type_string},
      { NULL, ::compress::kpidUnpackVer, var::type_byte}
   };

   static const stat_prop_stg kArcProps[] =
   {
      { NULL, ::compress::kpidCharacts, var::type_string},
      { NULL, ::compress::kpidSolid, var::type_bool},
      { NULL, ::compress::kpidNumBlocks, var::type_uint},
      // { NULL, ::compress::kpidEncrypted, var::type_bool},
      { NULL, ::compress::kpidIsVolume, var::type_bool},
      { NULL, ::compress::kpidNumVolumes, var::type_uint},
      { NULL, ::compress::kpidPhySize, var::type_uint64}
      // { NULL, ::compress::kpidCommented, var::type_bool}
   };

   IMP_IInArchive_Props
      IMP_IInArchive_ArcProps

   uint64 handler::GetPackSize(int refIndex) const
   {
      const CRefItem &refItem = _refItems[refIndex];
      uint64 totalPackSize = 0;
      for (int i = 0; i < refItem.NumItems; i++)
         totalPackSize += _items[refItem.ItemIndex + i].PackSize;
      return totalPackSize;
   }

   ex1::HRes handler::GetArchiveProperty(int propID, var *value)
   {
      var var;
      switch(propID)
      {
      case ::compress::kpidSolid: var = _archiveInfo.IsSolid(); break;
      case ::compress::kpidCharacts: FLAGS_TO_PROP(k_Flags, _archiveInfo.Flags, &var); break;
         // case ::compress::kpidEncrypted: prop = _archiveInfo.IsEncrypted(); break; // it's for encrypted names.
      case ::compress::kpidIsVolume: var = _archiveInfo.IsVolume(); break;
      case ::compress::kpidNumVolumes: var = (int32)_archives.get_size(); break;
      case ::compress::kpidOffset: if (_archiveInfo.StartPosition != 0) var = _archiveInfo.StartPosition; break;
         // case ::compress::kpidCommented: prop = _archiveInfo.IsCommented(); break;
      case ::compress::kpidNumBlocks:
         {
            uint32 numBlocks = 0;
            for (int i = 0; i < _refItems.get_size(); i++)
               if (!IsSolid(i))
                  numBlocks++;
            var = (int32)numBlocks;
            break;
         }
      case ::compress::kpidError: if (!_errorMessage.is_empty()) var = _errorMessage; break;
      }
      *value = var;
      return S_OK;
   }

   ex1::HRes handler::GetNumberOfItems(uint32 * numItems)
   {

      *numItems = (uint32_t) _refItems.get_size();

      return S_OK;

   }



   static bool RarTimeToFileTime(const CRarTime &rarTime, FILETIME &result)
   {
      if (!windows::file_time::DosTimeToFileTime(rarTime.DosTime, result))
         return false;
      uint64 value =  (((uint64)result.dwHighDateTime) << 32) + result.dwLowDateTime;
      value += (uint64)rarTime.LowSecond * 10000000;
      value += ((uint64)rarTime.SubTime[2] << 16) +
         ((uint64)rarTime.SubTime[1] << 8) +
         ((uint64)rarTime.SubTime[0]);
      result.dwLowDateTime = (DWORD)value;
      result.dwHighDateTime = DWORD(value >> 32);
      return true;
   }

   static void RarTimeToProp(const CRarTime &rarTime, var &prop)
   {
      FILETIME localFileTime, utcFileTime;
      if (RarTimeToFileTime(rarTime, localFileTime))
      {
         throw not_implemented_exception();
/*         if (!LocalFileTimeToFileTime(&localFileTime, &utcFileTime))
            utcFileTime.dwHighDateTime = utcFileTime.dwLowDateTime = 0;*/
      }
      else
         utcFileTime.dwHighDateTime = utcFileTime.dwLowDateTime = 0;
      prop = utcFileTime;
   }

   ex1::HRes handler::GetProperty(uint32 index, int propID,  var *value)
   {
      var prop;
      const CRefItem &refItem = _refItems[index];
      const CItemEx &item = _items[refItem.ItemIndex];
      switch(propID)
      {
      case ::compress::kpidPath:
         {
            prop = ::archive::item_name::WinNameToOSName(item.Name);
            break;
         }
      case ::compress::kpidIsDir: prop = item.IsDir(); break;
      case ::compress::kpidSize: prop = item.Size; break;
      case ::compress::kpidPackSize: prop = GetPackSize(index); break;
      case ::compress::kpidMTime: RarTimeToProp(item.MTime, prop); break;
      case ::compress::kpidCTime: if (item.CTimeDefined) RarTimeToProp(item.CTime, prop); break;
      case ::compress::kpidATime: if (item.ATimeDefined) RarTimeToProp(item.ATime, prop); break;
      case ::compress::kpidAttrib: prop = (int32) item.GetWinAttributes(); break;
      case ::compress::kpidEncrypted: prop = item.IsEncrypted(); break;
      case ::compress::kpidSolid: prop = IsSolid(index); break;
      case ::compress::kpidCommented: prop = item.IsCommented(); break;
      case ::compress::kpidSplitBefore: prop = item.IsSplitBefore(); break;
      case ::compress::kpidSplitAfter: prop = _items[refItem.ItemIndex + refItem.NumItems - 1].IsSplitAfter(); break;
      case ::compress::kpidCRC:
         {
            const CItemEx &lastItem = _items[refItem.ItemIndex + refItem.NumItems - 1];
            prop = (int32) (((lastItem.IsSplitAfter()) ? item.FileCRC : lastItem.FileCRC));
            break;
         }
      case ::compress::kpidUnpackVer: prop = item.UnPackVersion; break;
      case ::compress::kpidMethod:
         {
            string method;
            if (item.Method >= byte('0') && item.Method <= byte('5'))
            {
               method = "m";
               method += convert_to_string((uint64)(item.Method - byte('0')));
               if (!item.IsDir())
               {
                  method += ":";
                  method += convert_to_string((uint64)( 16 + item.GetDictSize()));;
               }
            }
            else
            {
               method += convert_to_string((uint64) item.Method);
            }
            prop = method;
            break;
         }
      case ::compress::kpidHostOS: prop = (item.HostOS < kNumHostOSes) ? (kHostOS[item.HostOS]) : kUnknownOS; break;
      }
      *value = prop;
      return S_OK;
   }

   class CVolumeName
   {
   public:
      bool _first;
      bool _newStyle;
      string _unchangedPart;
      string _changedPart;
      string _afterPart;
      CVolumeName(): _newStyle(true) {};

      bool InitName(const string &name, bool newStyle)
      {

         _first = true;

         _newStyle = newStyle;

         strsize dotPos = name.reverse_find('.');

         string basePart = name;

         if (dotPos >= 0)
         {

            string ext = name.Mid(dotPos + 1);

            if (ext.CompareNoCase("rar") == 0)
            {
               _afterPart = name.Mid(dotPos);
               basePart = name.Left(dotPos);
            }
            else if (ext.CompareNoCase("exe") == 0)
            {
               _afterPart = ".rar";
               basePart = name.Left(dotPos);
            }
            else if (!_newStyle)
            {
               if (ext.CompareNoCase("000") == 0 ||
                  ext.CompareNoCase("001") == 0 ||
                  ext.CompareNoCase("r00") == 0 ||
                  ext.CompareNoCase("r01") == 0)
               {
                  _afterPart.Empty();
                  _first = false;
                  _changedPart = ext;
                  _unchangedPart = name.Left(dotPos + 1);
                  return true;
               }
            }
         }

         if (!_newStyle)
         {
            _afterPart.Empty();
            _unchangedPart = basePart + string(".");
            _changedPart = "r00";
            return true;
         }

         int numLetters = 1;
         if (basePart.Right(numLetters) == "1" || basePart.Right(numLetters) == "0")
         {
            while (numLetters < basePart.get_length())
            {
               if (basePart[basePart.get_length() - numLetters - 1] != '0')
                  break;
               numLetters++;
            }
         }
         else
            return false;
         _unchangedPart = basePart.Left(basePart.get_length() - numLetters);
         _changedPart = basePart.Right(numLetters);
         return true;
      }

      string GetNextName()
      {
         string newName;
         if (_newStyle || !_first)
         {

            strsize i;

            strsize numLetters = _changedPart.get_length();

            for (i = numLetters - 1; i >= 0; i--)
            {
               wchar_t c = _changedPart[i];
               if (c == '9')
               {
                  c = '0';
                  newName = c + newName;
                  if (i == 0)
                     newName = string(L'1') + newName;
                  continue;
               }
               c++;
               newName = string(c) + newName;
               i--;
               for (; i >= 0; i--)
                  newName = _changedPart[i] + newName;
               break;
            }
            _changedPart = newName;
         }
         _first = false;
         return _unchangedPart + _changedPart + _afterPart;
      }
   };

   //HRESULT handler::Open2(IInStream *stream,
   HRESULT handler::Open2(ex1::byte_input_stream * stream, const file_position *maxCheckStartPosition, ::compress::archive_open_callback_interface *openCallback)
   {
      {
         ::compress::archive_open_volume_callback_interface  * openVolumeCallback = NULL;
         ::crypto::get_text_password_interface * getTextPassword = NULL;
//         ::compress::archive_open_callback_interface * openArchiveCallbackWrap = openCallback;

         CVolumeName seqName;

         uint64 totalBytes = 0;
         uint64 curBytes = 0;

         if (openCallback)
         {
            openVolumeCallback   = dynamic_cast < ::compress::archive_open_volume_callback_interface * > (openCallback);
            getTextPassword      = dynamic_cast < ::crypto::get_text_password_interface * > (openCallback);
         }

         for (;;)
         {
            ::ex1::byte_input_stream * inStream;
            if (!_archives.is_empty())
            {
               if (!openVolumeCallback)
                  break;

               if (_archives.get_size() == 1)
               {
                  if (!_archiveInfo.IsVolume())
                     break;
                  string baseName;
                  {
                     var prop;
                     RINOK(openVolumeCallback->GetProperty(::compress::kpidName, &prop));
                     if(prop.m_etype != var::type_string)
                        break;
                     baseName = prop;
                  }
                  seqName.InitName(baseName, _archiveInfo.HaveNewVolumeName());
               }

               string fullName = seqName.GetNextName();
               HRESULT result = openVolumeCallback->GetStream(fullName, &inStream);
               if (result == S_FALSE)
                  break;
               if (result != S_OK)
                  return result;
               if (!stream)
                  break;
            }
            else
               inStream = stream;

            uint64 endPos = 0;
            endPos = stream->seek(0, ::ex1::seek_end);
            stream->seek(0, ::ex1::seek_begin);
            if (openCallback)
            {
               totalBytes += endPos;
               RINOK(openCallback->SetTotal(NULL, &totalBytes));
            }

            rar::input_file archive;
            RINOK(archive.Open(inStream, maxCheckStartPosition));

            if (_archives.is_empty())
               archive.GetArchiveInfo(_archiveInfo);

            CItemEx item;
            for (;;)
            {
               if (archive.m_Position > endPos)
               {
                  AddErrorMessage("Unexpected end of archive");
                  break;
               }
               bool decryptionError;
               string errorMessageLoc;
               HRESULT result = archive.GetNextItem(item, getTextPassword, decryptionError, errorMessageLoc);
               if (errorMessageLoc)
                  AddErrorMessage(errorMessageLoc);
               if (result == S_FALSE)
               {
                  if (decryptionError && _items.is_empty())
                     return S_FALSE;
                  break;
               }
               RINOK(result);
               if (item.IgnoreItem())
                  continue;

               bool needAdd = true;
               if (item.IsSplitBefore())
               {
                  if (!_refItems.is_empty())
                  {
                     CRefItem &refItem = _refItems.last_element();
                     refItem.NumItems++;
                     needAdd = false;
                  }
               }
               if (needAdd)
               {
                  CRefItem refItem;
                  refItem.ItemIndex = (int) _items.get_size();
                  refItem.NumItems = 1;
                  refItem.VolumeIndex = (int) _archives.get_size();
                  _refItems.add(refItem);
               }
               _items.add(item);
               if (openCallback && _items.get_size() % 100 == 0)
               {
                  uint64 numFiles = _items.get_size();
                  uint64 numBytes = curBytes + item.Position;
                  RINOK(openCallback->SetCompleted(&numFiles, &numBytes));
               }
            }
            curBytes += endPos;
            _archives.add(archive);
         }
      }
      return S_OK;
   }

   ex1::HRes handler::Open(ex1::byte_input_stream * stream, const file_position *maxCheckStartPosition, ::compress::archive_open_callback_interface *openCallback)
   {
      Close();
      try
      {
         HRESULT res = Open2(stream, maxCheckStartPosition, openCallback);
         if (res != S_OK)
            Close();
         return res;
      }
      catch(const input_file_exception &)
      {
         Close();
         return S_FALSE;
      }
      catch(...)
      {
         Close(); throw;
      }
   }

   ex1::HRes handler::Close()
   {
      _errorMessage.Empty();
      _refItems.remove_all();
      _items.remove_all();
      _archives.remove_all();
      return S_OK;
   }

   struct CMethodItem
   {
      byte RarUnPackVersion;
      ::compress::coder_interface * Coder;
   };


   ex1::HRes handler::Extract(const uint32 *indices, uint32 numItems, int32 testMode, ::compress::archive_extract_callback_interface *extractCallback)
   {
      ::crypto::get_text_password_interface * getTextPassword = NULL;
      file_size censoredTotalUnPacked = 0,
         // censoredTotalPacked = 0,
         importantTotalUnPacked = 0;
      // importantTotalPacked = 0;
      bool allFilesMode = (numItems == (uint32)-1);
      if (allFilesMode)
         numItems = (uint32_t) _refItems.get_size();
      if (numItems == 0)
         return S_OK;
      int lastIndex = 0;
      int_array importantIndexes;
      bool_array extractStatuses;

      for (uint32 t = 0; t < numItems; t++)
      {
         int index = allFilesMode ? t : indices[t];
         const CRefItem &refItem = _refItems[index];
         const CItemEx &item = _items[refItem.ItemIndex];
         censoredTotalUnPacked += item.Size;
         // censoredTotalPacked += item.PackSize;
         int j;
         for (j = lastIndex; j <= index; j++)
            // if (!_items[_refItems[j].ItemIndex].IsSolid())
            if (!IsSolid(j))
               lastIndex = j;
         for (j = lastIndex; j <= index; j++)
         {
            const CRefItem &refItem = _refItems[j];
            const CItemEx &item = _items[refItem.ItemIndex];

            // const CItemEx &item = _items[j];

            importantTotalUnPacked += item.Size;
            // importantTotalPacked += item.PackSize;
            importantIndexes.add(j);
            extractStatuses.add(j == index);
         }
         lastIndex = index + 1;
      }

      RINOK(extractCallback->SetTotal(importantTotalUnPacked));
      uint64 currentImportantTotalUnPacked = 0;
      uint64 currentImportantTotalPacked = 0;
      uint64 currentUnPackSize, currentPackSize;

      base_array < CMethodItem > methodItems;

      ::compress::copy_coder * copyCoderSpec = new ::compress::copy_coder;
      ::compress::coder_interface * copyCoder = copyCoderSpec;

      ::compress::filter_coder *filterStreamSpec = new ::compress::filter_coder;
      ::ex1::reader * filterStream = filterStreamSpec;

      ::crypto::rar20::decoder *rar20CryptoDecoderSpec = NULL;
      ::compress::filter_interface * rar20CryptoDecoder = NULL;
      ::crypto::rar29::decoder *rar29CryptoDecoderSpec = NULL;
      ::compress::filter_interface * rar29CryptoDecoder = NULL;

      folder_reader * folderInStreamSpec = NULL;
      ::ex1::reader * folderInStream = NULL;

      ::compress::local_progress *lps = new ::compress::local_progress;
      ::compress::progress_info_interface * progress = lps;
      lps->Init(extractCallback, false);

      bool solidStart = true;
      for (int i = 0; i < importantIndexes.get_count(); i++, currentImportantTotalUnPacked += currentUnPackSize, currentImportantTotalPacked += currentPackSize)
      {
         lps->InSize = currentImportantTotalPacked;
         lps->OutSize = currentImportantTotalUnPacked;
         RINOK(lps->SetCur());
         ::ex1::writer * realOutStream;

         int32 askMode;
         if (extractStatuses[i])
            askMode = testMode ? ::compress::archive::extract::ask_mode_test : ::compress::archive::extract::ask_mode_extract;
         else
            askMode = ::compress::archive::extract::ask_mode_skip;

         uint32 index = importantIndexes[i];

         const CRefItem &refItem = _refItems[index];
         const CItemEx &item = _items[refItem.ItemIndex];

         currentUnPackSize = item.Size;

         currentPackSize = GetPackSize(index);

         if (item.IgnoreItem())
            continue;

         RINOK(extractCallback->GetStream(index, &realOutStream, askMode));

         if (!IsSolid(index))
            solidStart = true;
         if (item.IsDir())
         {
            RINOK(extractCallback->PrepareOperation(askMode));
            RINOK(extractCallback->SetOperationResult(::compress::archive::extract::operation_result_ok));
            continue;
         }

         bool mustBeProcessedAnywhere = false;
         if (i < importantIndexes.get_size() - 1)
         {
            // const CRefItem &nextRefItem = _refItems[importantIndexes[i + 1]];
            // const CItemEx &nextItemInfo = _items[nextRefItem.ItemIndex];
            // mustBeProcessedAnywhere = nextItemInfo.IsSolid();
            mustBeProcessedAnywhere = IsSolid(importantIndexes[i + 1]);
         }

         if (!mustBeProcessedAnywhere && !testMode && !realOutStream)
            continue;

         if (!realOutStream && !testMode)
            askMode = ::compress::archive::extract::ask_mode_skip;

         RINOK(extractCallback->PrepareOperation(askMode));

         ::compress::writer_with_crc *outStreamSpec = new ::compress::writer_with_crc;
         ::ex1::writer * outStream(outStreamSpec);
         outStreamSpec->SetStream(realOutStream);
         outStreamSpec->Init();
         //realOutStream.Release();

         /*
         for (int partIndex = 0; partIndex < 1; partIndex++)
         {
         CMyComPtr<::ex1::reader> inStream;

         // item redefinition
         const CItemEx &item = _items[refItem.ItemIndex + partIndex];

         NArchive::NRar::CInArchive &archive = _archives[refItem.VolumeIndex + partIndex];

         inStream.Attach(archive.CreateLimitedStream(item.GetDataPosition(),
         item.PackSize));
         */
         if (!folderInStream)
         {
            folderInStreamSpec = new folder_reader;
            folderInStream = folderInStreamSpec;
         }

         folderInStreamSpec->Init(&_archives, &_items, refItem);

         file_size packSize = currentPackSize;

         // packedPos += item.PackSize;
         // unpackedPos += 0;

         ex1::reader * inStream;
         if (item.IsEncrypted())
         {
            ::crypto::set_password_interface * cryptoSetPassword;
            if (item.UnPackVersion >= 29)
            {
               if (!rar29CryptoDecoder)
               {
                  rar29CryptoDecoderSpec = new ::crypto::rar29::decoder;
                  rar29CryptoDecoder = rar29CryptoDecoderSpec;
                  // RINOK(rar29CryptoDecoder.CoCreateInstance(CLSID_CCryptoRar29Decoder));
               }
               rar29CryptoDecoderSpec->SetRar350Mode(item.UnPackVersion < 36);
               ::compress::set_decoder_properties2_interface * cryptoProperties;
               cryptoProperties = dynamic_cast < ::compress::set_decoder_properties2_interface * > (rar29CryptoDecoder);
               RINOK(cryptoProperties->SetDecoderProperties2(item.Salt, item.HasSalt() ? sizeof(item.Salt) : 0));
               filterStreamSpec->Filter = rar29CryptoDecoder;
            }
            else if (item.UnPackVersion >= 20)
            {
               if (!rar20CryptoDecoder)
               {
                  rar20CryptoDecoderSpec = new ::crypto::rar20::decoder;
                  rar20CryptoDecoder = rar20CryptoDecoderSpec;
                  // RINOK(rar20CryptoDecoder.CoCreateInstance(CLSID_CCryptoRar20Decoder));
               }
               filterStreamSpec->Filter = rar20CryptoDecoder;
            }
            else
            {
               //outStream.Release();
               RINOK(extractCallback->SetOperationResult(::compress::archive::extract::operation_result_UnSupportedMethod));
               continue;
            }
            cryptoSetPassword = dynamic_cast < ::crypto::set_password_interface * > (filterStreamSpec);

            if (!getTextPassword)
            {
               getTextPassword = dynamic_cast < ::crypto::get_text_password_interface * > (extractCallback);
            }
            if (getTextPassword)
            {
               string password;
               RINOK(getTextPassword->CryptoGetTextPassword(password));
               if (item.UnPackVersion >= 29)
               {
                  ::ex1::byte_buffer buffer;
                  wstring unicodePassword = gen::international::utf8_to_unicode(password);
                  const uint32 sizeInBytes = (const uint32_t) (unicodePassword.get_length() * 2);
                  buffer.SetCapacity(sizeInBytes);
                  for (int i = 0; i < unicodePassword.get_length(); i++)
                  {
                     wchar_t c = unicodePassword[i];
                     ((byte *)buffer)[i * 2] = (byte)c;
                     ((byte *)buffer)[i * 2 + 1] = (byte)(c >> 8);
                  }
                  RINOK(cryptoSetPassword->CryptoSetPassword(
                     (const byte *)buffer, sizeInBytes));
               }
               else
               {
                  string oemPassword;
                  gen::international::utf8_to_multibyte(CP_OEMCP, oemPassword, password);
                  RINOK(cryptoSetPassword->CryptoSetPassword((const byte *)(const char *)oemPassword, (uint32_t) oemPassword.get_length()));
               }
            }
            else
            {
               RINOK(cryptoSetPassword->CryptoSetPassword(0, 0));
            }
            filterStreamSpec->SetInStream(folderInStream);
            inStream = filterStream;
         }
         else
         {
            inStream = folderInStream;
         }
         ::compress::coder_interface * commonCoder;
         switch(item.Method)
         {
         case '0':
            {
               commonCoder = copyCoder;
               break;
            }
         case '1':
         case '2':
         case '3':
         case '4':
         case '5':
            {
               /*
               if (item.UnPackVersion >= 29)
               {
               outStream.Release();
               RINOK(extractCallback->SetOperationResult(NExtract::NOperationResult::kUnSupportedMethod));
               continue;
               }
               */
               ::index m;
               for (m = 0; m < methodItems.get_size(); m++)
                  if (methodItems[m].RarUnPackVersion == item.UnPackVersion)
                     break;
               if (m == methodItems.get_size())
               {
                  CMethodItem mi;
                  mi.RarUnPackVersion = item.UnPackVersion;

//                  mi.Coder.Release();
                  if (item.UnPackVersion <= 30)
                  {
                     ::compress::method_id methodID = 0x040300;
                     if (item.UnPackVersion < 20)
                        methodID += 1;
                     else if (item.UnPackVersion < 29)
                        methodID += 2;
                     else
                        methodID += 3;
                     RINOK(CreateCoder(_codecsInfo, &_externalCodecs, methodID, mi.Coder, false));
                  }

                  if (mi.Coder == 0)
                  {
                     //outStream.Release();
                     RINOK(extractCallback->SetOperationResult(::compress::archive::extract::operation_result_UnSupportedMethod));
                     continue;
                  }

                  m = methodItems.add(mi);
               }
               ::compress::coder_interface * decoder = methodItems[m].Coder;

               ::compress::set_decoder_properties2_interface * compressSetDecoderProperties;
               compressSetDecoderProperties = dynamic_cast < ::compress::set_decoder_properties2_interface * > (decoder);

               byte isSolid = (byte)((IsSolid(index) || item.IsSplitBefore()) ? 1: 0);
               if (solidStart)
               {
                  isSolid = false;
                  solidStart = false;
               }


               RINOK(compressSetDecoderProperties->SetDecoderProperties2(&isSolid, 1));

               commonCoder = decoder;
               break;
            }
         default:
            //outStream.Release();
            RINOK(extractCallback->SetOperationResult(::compress::archive::extract::operation_result_UnSupportedMethod));
            continue;
         }
         HRESULT result = commonCoder->Code(inStream, outStream, &packSize, &item.Size, progress);
         if (item.IsEncrypted())
            filterStreamSpec->ReleaseInStream();
         if (result == S_FALSE)
         {
            //outStream.Release();
            RINOK(extractCallback->SetOperationResult(::compress::archive::extract::operation_result_DataError));
            continue;
         }
         if (result != S_OK)
            return result;

         /*
         if (refItem.NumItems == 1 &&
         !item.IsSplitBefore() && !item.IsSplitAfter())
         */
         {
            const CItemEx &lastItem = _items[refItem.ItemIndex + refItem.NumItems - 1];
            bool crcOK = outStreamSpec->GetCRC() == lastItem.FileCRC;
            //outStream.Release();
            RINOK(extractCallback->SetOperationResult(crcOK ? ::compress::archive::extract::operation_result_ok : ::compress::archive::extract::operation_result_CRCError));
         }
         /*
         else
         {
         bool crcOK = true;
         for (int partIndex = 0; partIndex < refItem.NumItems; partIndex++)
         {
         const CItemEx &item = _items[refItem.ItemIndex + partIndex];
         if (item.FileCRC != folderInStreamSpec->CRCs[partIndex])
         {
         crcOK = false;
         break;
         }
         }
         RINOK(extractCallback->SetOperationResult(crcOK ?
         NExtract::NOperationResult::kOK:
         NExtract::NOperationResult::kCRCError));
         }
         */
      }
      return S_OK;
   }

   // IMPL_ISetCompressCodecsInfo2(CHandler)
   ex1::HRes handler::SetCompressCodecsInfo(::compress::codecs_info_interface * compressCodecsInfo)
   {
      _codecsInfo = compressCodecsInfo;
      return LoadExternalCodecs(_codecsInfo, _externalCodecs);

   }


   bool handler::IsSolid(int refIndex)
   {
      const CItemEx &item = _items[_refItems[refIndex].ItemIndex];
      if (item.UnPackVersion < 20)
      {
         if (_archiveInfo.IsSolid())
            return (refIndex > 0);
         return false;
      }
      return item.IsSolid();
   }
   void handler::AddErrorMessage(const string &s)
   {
      if (!_errorMessage.is_empty())
         _errorMessage += '\n';
      _errorMessage += s;
   }


} // compress "rar"

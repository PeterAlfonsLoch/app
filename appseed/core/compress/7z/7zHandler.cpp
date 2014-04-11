// 7zHandler.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"

/*#include "../../../../C/CpuArch.h"

#include "../../../Common/ComTry.h"
#include "../../../Common/IntToString.h"

#ifndef __7Z_SET_PROPERTIES
#include "../../../Windows/System.h"
#endif

#include "../Common/ItemNameUtils.h"

#include "7zHandler.h"
#include "7zProperties.h"

#ifdef __7Z_SET_PROPERTIES
#ifdef EXTRACT_ONLY
#include "../Common/ParseProperties.h"
#endif
#endif

using namespace NWindows;*/

extern string ConvertMethodIdToString(uint64_t id);


namespace n7z
{

handler::handler()
{
  _crcSize = 4;

  #ifndef _NO_CRYPTO
  _passwordIsDefined = false;
  #endif

  #ifdef EXTRACT_ONLY
  #ifdef __7Z_SET_PROPERTIES
  _numThreads = NSystem::GetNumberOfProcessors();
  #endif
  #else
  Init();
  #endif
}

HRes handler::GetNumberOfItems(uint32_t *numItems)
{
  *numItems = (uint32_t) _db.Files.get_count();
  return S_OK;
}

#ifdef _SFX

IMP_IInArchive_ArcProps_NO

HRes handler::GetNumberOfProperties(uint32_t * /* numProperties */)
{
  return E_NOTIMPL;
}

HRes handler::GetPropertyInfo(uint32_t /* index */,
      BSTR * /* name */, PROPID * /* propID */, VARTYPE * /* varType */)
{
  return E_NOTIMPL;
}


#else

/*struct STATPROPSTG
{

  int32_t m_i1;
  int32_t m_i2;
  int32_t m_i3;
};*/

stat_prop_stg kArcProps[] =
{
  { NULL, ::libcompress::kpidMethod, var::type_string},
  { NULL, ::libcompress::kpidSolid, var::type_bool},
  { NULL, ::libcompress::kpidNumBlocks, var::type_uint32},
  { NULL, ::libcompress::kpidPhySize, var::type_uint64},
  { NULL, ::libcompress::kpidHeadersSize, var::type_uint64},
  { NULL, ::libcompress::kpidOffset, var::type_uint64}
};

HRes handler::GetArchiveProperty(int32_t propID, var *value)
{
  var prop;
  switch(propID)
  {
  case ::libcompress::kpidMethod:
    {
      string resString;
      uint64_array ids;
      int32_t i;
      for (i = 0; i < _db.Folders.get_count(); i++)
      {
        const CFolder &f = _db.Folders[i];
        for (index j = f.Coders.get_count() - 1; j >= 0; j--)
           ids.add_unique(f.Coders[j].MethodID);
      }
      ids.quick_sort(true);

      for (i = 0; i < ids.get_count(); i++)
      {
        uint64_t id = ids[i];
        string methodName;
        /* bool methodIsKnown = */ FindMethod(_codecsInfo, &_externalCodecs, id, methodName);
        if (methodName.is_empty())
          methodName = ConvertMethodIdToString(id);
        if (!resString.is_empty())
          resString += L' ';
        resString += methodName;
      }
      prop = resString;
      break;
    }
    case ::libcompress::kpidSolid: prop = _db.IsSolid(); break;
    case ::libcompress::kpidNumBlocks: prop = _db.Folders.get_count(); break;
    case ::libcompress::kpidHeadersSize:  prop = _db.HeadersSize; break;
    case ::libcompress::kpidPhySize:  prop = _db.PhySize; break;
    case ::libcompress::kpidOffset: if (_db.ArchiveInfo.StartPosition != 0) prop = _db.ArchiveInfo.StartPosition; break;
  }
  *value = prop;
  return S_OK;
}

IMP_IInArchive_ArcProps

#endif

static void SetPropFromUInt64Def(CUInt64DefVector &v, int32_t index, var &prop)
{
  uint64_t value;
  if (v.GetItem(index, value))
  {
    FILETIME ft;
    ft.dwLowDateTime = (uint32_t)value;
    ft.dwHighDateTime = (uint32_t)(value >> 32);
    prop = ft;
  }
}

#ifndef _SFX

static string ConvertUInt32ToString(uint32_t value)
{
  return convert_to_string((uint64_t) value);
}

static string GetStringForSizeValue(uint32_t value)
{
  for (int32_t i = 31; i >= 0; i--)
    if ((uint32_t(1) << i) == value)
      return ConvertUInt32ToString(i);
  string result;
  if (value % (1 << 20) == 0)
  {
    result += ConvertUInt32ToString(value >> 20);
    result += L"m";
  }
  else if (value % (1 << 10) == 0)
  {
    result += ConvertUInt32ToString(value >> 10);
    result += L"k";
  }
  else
  {
    result += ConvertUInt32ToString(value);
    result += L"b";
  }
  return result;
}

//static const uint64_t k_Copy = 0x0;
static const uint64_t k_Delta = 3;
static const uint64_t k_LZMA2 = 0x21;
static const uint64_t k_LZMA  = 0x030101;
static const uint64_t k_PPMD  = 0x030401;

static wchar_t GetHex(byte value)
{
  return (wchar_t)((value < 10) ? (L'0' + value) : (L'A' + (value - 10)));
}
static inline void AddHexToString(string &res, byte value)
{
  res += GetHex((byte)(value >> 4));
  res += GetHex((byte)(value & 0xF));
}

#endif

bool handler::IsEncrypted(uint32_t index1) const
{
  CNum folderIndex = _db.FileIndexToFolderIndexMap[index1];
  if (folderIndex != kNumNoIndex)
    return _db.Folders[folderIndex].IsEncrypted();
  return false;
}

HRes handler::GetProperty(uint32_t index, int32_t propID,  var *value)
{
  var prop;

  /*
  const CRef2 &ref2 = _refs[index];
  if (ref2.Refs.is_empty())
    return E_FAIL;
  const CRef &ref = ref2.Refs.Front();
  */

  const CFileItem &item = _db.Files[index];
  uint32_t index1 = index;

  switch(propID)
  {
  case ::libcompress::kpidPath:
      if (!item.Name.is_empty())
      {
         throw "should implement following";
       // prop = NItemName::GetOSName(item.Name);
      }
      break;
    case ::libcompress::kpidIsDir:  prop = item.IsDir; break;
    case ::libcompress::kpidSize:
    {
      prop = item.get_count;
      // prop = ref2.get_count;
      break;
    }
    case ::libcompress::kpidPackSize:
    {
      // prop = ref2.PackSize;
      {
        CNum folderIndex = _db.FileIndexToFolderIndexMap[index1];
        if (folderIndex != kNumNoIndex)
        {
          if (_db.FolderStartFileIndex[folderIndex] == (CNum)index1)
            prop = _db.GetFolderFullPackSize(folderIndex);
          /*
          else
            prop = (uint64_t)0;
          */
        }
        else
          prop = (uint64_t)0;
      }
      break;
    }
    case ::libcompress::kpidPosition:  { uint64_t v; if (_db.StartPos.GetItem(index1, v)) prop = v; break; }
    case ::libcompress::kpidCTime:  SetPropFromUInt64Def(_db.CTime, index1, prop); break;
    case ::libcompress::kpidATime:  SetPropFromUInt64Def(_db.ATime, index1, prop); break;
    case ::libcompress::kpidMTime:  SetPropFromUInt64Def(_db.MTime, index1, prop); break;
    case ::libcompress::kpidAttrib:  if (item.AttribDefined) prop = (uint64_t) item.Attrib; break;
    case ::libcompress::kpidCRC:  if (item.CrcDefined) prop = (uint64_t) item.Crc; break;
    case ::libcompress::kpidEncrypted:  prop = IsEncrypted(index1); break;
    case ::libcompress::kpidIsAnti:  prop = _db.IsItemAnti(index1); break;
    #ifndef _SFX
    case ::libcompress::kpidMethod:
      {
        CNum folderIndex = _db.FileIndexToFolderIndexMap[index1];
        if (folderIndex != kNumNoIndex)
        {
          const CFolder &folderInfo = _db.Folders[folderIndex];
          string methodsString;
          for (::index i = folderInfo.Coders.get_count() - 1; i >= 0; i--)
          {
            const CCoderInfo &coder = folderInfo.Coders[i];
            if (!methodsString.is_empty())
              methodsString += L' ';

            string methodName, propsString;
            bool methodIsKnown = FindMethod(
              _codecsInfo, &_externalCodecs,
              coder.MethodID, methodName);

            if (!methodIsKnown)
              methodsString += ConvertMethodIdToString(coder.MethodID);
            else
            {
              methodsString += methodName;
              if (coder.MethodID == k_Delta && coder.Props.GetCapacity() == 1)
                propsString = ConvertUInt32ToString((uint32_t)coder.Props[0] + 1);
              else if (coder.MethodID == k_LZMA && coder.Props.GetCapacity() == 5)
              {
                uint32_t dicSize = GetUi32((const byte *)coder.Props + 1);
                propsString = GetStringForSizeValue(dicSize);
              }
              else if (coder.MethodID == k_LZMA2 && coder.Props.GetCapacity() == 1)
              {
                byte p = coder.Props[0];
                uint32_t dicSize = (((uint32_t)2 | ((p) & 1)) << ((p) / 2 + 11));
                propsString = GetStringForSizeValue(dicSize);
              }
              else if (coder.MethodID == k_PPMD && coder.Props.GetCapacity() == 5)
              {
                byte order = *(const byte *)coder.Props;
                propsString = L'o';
                propsString += ConvertUInt32ToString(order);
                propsString += L":mem";
                uint32_t dicSize = GetUi32((const byte *)coder.Props + 1);
                propsString += GetStringForSizeValue(dicSize);
              }
              else if (coder.MethodID == k_AES && coder.Props.GetCapacity() >= 1)
              {
                const byte *data = (const byte *)coder.Props;
                byte firstByte = *data++;
                uint32_t numCyclesPower = firstByte & 0x3F;
                propsString = ConvertUInt32ToString(numCyclesPower);
                /*
                if ((firstByte & 0xC0) != 0)
                {
                  uint32_t saltSize = (firstByte >> 7) & 1;
                  uint32_t ivSize = (firstByte >> 6) & 1;
                  if (coder.Props.GetCapacity() >= 2)
                  {
                    byte secondByte = *data++;
                    saltSize += (secondByte >> 4);
                    ivSize += (secondByte & 0x0F);
                  }
                }
                */
              }
            }
            if (!propsString.is_empty())
            {
              methodsString += L':';
              methodsString += propsString;
            }
            else if (coder.Props.GetCapacity() > 0)
            {
              methodsString += L":[";
              for (size_t bi = 0; bi < coder.Props.GetCapacity(); bi++)
              {
                if (bi > 5 && bi + 1 < coder.Props.GetCapacity())
                {
                  methodsString += L"..";
                  break;
                }
                else
                  AddHexToString(methodsString, coder.Props[bi]);
              }
              methodsString += L']';
            }
          }
          prop = methodsString;
        }
      }
      break;
    case ::libcompress::kpidBlock:
      {
        CNum folderIndex = _db.FileIndexToFolderIndexMap[index1];
        if (folderIndex != kNumNoIndex)
          prop = (uint64_t) folderIndex;
      }
      break;
    case kpidPackedSize0:
    case kpidPackedSize1:
    case kpidPackedSize2:
    case kpidPackedSize3:
    case kpidPackedSize4:
      {
        CNum folderIndex = _db.FileIndexToFolderIndexMap[index1];
        if (folderIndex != kNumNoIndex)
        {
          const CFolder &folderInfo = _db.Folders[folderIndex];
          if (_db.FolderStartFileIndex[folderIndex] == (CNum)index1 &&
              folderInfo.PackStreams.get_count() > (int32_t)(propID - kpidPackedSize0))
          {
            prop = _db.GetFolderPackStreamSize(folderIndex, propID - kpidPackedSize0);
          }
          else
            prop = (uint64_t)0;
        }
        else
          prop = (uint64_t)0;
      }
      break;
    #endif
  }
  *value = prop;
  return S_OK;
}

HRes handler::Open(::file::input_stream *stream,
    const file_position *maxCheckStartPosition,
    ::libcompress::archive_open_callback_interface *openArchiveCallback)
{
  Close();
  #ifndef _SFX
  _fileInfoPopIDs.remove_all();
  #endif
  try
  {
    smart_pointer < ::libcompress::archive_open_callback_interface > openArchiveCallbackTemp = openArchiveCallback;

    #ifndef _NO_CRYPTO
    smart_pointer < ::crypto::get_text_password_interface > getTextPassword;
    if (openArchiveCallback)
    {
      getTextPassword = dynamic_cast < ::crypto::get_text_password_interface * > (openArchiveCallbackTemp.m_p);
    }
    #endif
    CInArchive archive(get_app());
    RINOK(archive.Open(stream, maxCheckStartPosition));
    #ifndef _NO_CRYPTO
    _passwordIsDefined = false;
    string password;
    #endif
    HRESULT result = archive.ReadDatabase(
      _codecsInfo, &_externalCodecs,
      _db
      #ifndef _NO_CRYPTO
      , getTextPassword, _passwordIsDefined
      #endif
      );
    RINOK(result);
    _db.Fill();
    _inStream = stream;
  }
  catch(...)
  {
    Close();
    return S_FALSE;
  }
  // _inStream = stream;
  #ifndef _SFX
  FillPopIDs();
  #endif
  return S_OK;
}

HRes handler::Close()
{
::release(_inStream.m_p);
  _db.clear();
  return S_OK;
}

#ifdef __7Z_SET_PROPERTIES
#ifdef EXTRACT_ONLY

HRes handler::SetProperties(const wchar_t **names, const PROPVARIANT *values, Int32 numProperties)
{
  COM_TRY_BEGIN
  const uint32_t numProcessors = NSystem::GetNumberOfProcessors();
  _numThreads = numProcessors;

  for (int32_t i = 0; i < numProperties; i++)
  {
    string name = names[i];
    name.MakeUpper();
    if (name.is_empty())
      return E_INVALIDARG;
    const PROPVARIANT &value = values[i];
    uint32_t number;
    int32_t index = ParseStringToUInt32(name, number);
    if (index == 0)
    {
      if(name.Left(2).CompareNoCase(L"MT") == 0)
      {
        RINOK(ParseMtProp(name.Mid(2), value, numProcessors, _numThreads));
        continue;
      }
      else
        return E_INVALIDARG;
    }
  }
  return S_OK;
  COM_TRY_END
}

#endif
#endif

   // IMPL_ISetCompressCodecsInfo2(handler)
   HRes handler::SetCompressCodecsInfo(::libcompress::codecs_info_interface * compressCodecsInfo)
   {
      _codecsInfo = compressCodecsInfo;
      return LoadExternalCodecs(_codecsInfo, _externalCodecs);

   }


   /*bool handler::IsSolid(int32_t refIndex)
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
   }*/

} // namespace n7z

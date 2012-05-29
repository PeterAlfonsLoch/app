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

extern string ConvertMethodIdToString(uint64 id);


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

ex1::HRes handler::GetNumberOfItems(uint32 *numItems)
{
  *numItems = (uint32_t) _db.Files.get_count();
  return S_OK;
}

#ifdef _SFX

IMP_IInArchive_ArcProps_NO

ex1::HRes handler::GetNumberOfProperties(uint32 * /* numProperties */)
{
  return E_NOTIMPL;
}

ex1::HRes handler::GetPropertyInfo(uint32 /* index */,
      BSTR * /* name */, PROPID * /* propID */, VARTYPE * /* varType */)
{
  return E_NOTIMPL;
}


#else

/*struct STATPROPSTG
{

  int m_i1;
  int m_i2;
  int m_i3;
};*/

stat_prop_stg kArcProps[] =
{
  { NULL, ::compress::kpidMethod, var::type_string},
  { NULL, ::compress::kpidSolid, var::type_bool},
  { NULL, ::compress::kpidNumBlocks, var::type_uint},
  { NULL, ::compress::kpidPhySize, var::type_uint64},
  { NULL, ::compress::kpidHeadersSize, var::type_uint64},
  { NULL, ::compress::kpidOffset, var::type_uint64}
};

ex1::HRes handler::GetArchiveProperty(int propID, var *value)
{
  var prop;
  switch(propID)
  {
  case ::compress::kpidMethod:
    {
      string resString;
      uint64_array ids;
      int i;
      for (i = 0; i < _db.Folders.get_count(); i++)
      {
        const CFolder &f = _db.Folders[i];
        for (index j = f.Coders.get_count() - 1; j >= 0; j--)
           ids.add_unique(f.Coders[j].MethodID);
      }
      ids.QuickSort(true);

      for (i = 0; i < ids.get_count(); i++)
      {
        uint64 id = ids[i];
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
    case ::compress::kpidSolid: prop = _db.IsSolid(); break;
    case ::compress::kpidNumBlocks: prop = _db.Folders.get_count(); break;
    case ::compress::kpidHeadersSize:  prop = _db.HeadersSize; break;
    case ::compress::kpidPhySize:  prop = _db.PhySize; break;
    case ::compress::kpidOffset: if (_db.ArchiveInfo.StartPosition != 0) prop = _db.ArchiveInfo.StartPosition; break;
  }
  *value = prop;
  return S_OK;
}

IMP_IInArchive_ArcProps

#endif

static void SetPropFromUInt64Def(CUInt64DefVector &v, int index, var &prop)
{
  uint64 value;
  if (v.GetItem(index, value))
  {
    FILETIME ft;
    ft.dwLowDateTime = (DWORD)value;
    ft.dwHighDateTime = (DWORD)(value >> 32);
    prop = ft;
  }
}

#ifndef _SFX

static string ConvertUInt32ToString(uint32 value)
{
  return convert_to_string((uint64) value);
}

static string GetStringForSizeValue(uint32 value)
{
  for (int i = 31; i >= 0; i--)
    if ((uint32(1) << i) == value)
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

static const uint64 k_Copy = 0x0;
static const uint64 k_Delta = 3;
static const uint64 k_LZMA2 = 0x21;
static const uint64 k_LZMA  = 0x030101;
static const uint64 k_PPMD  = 0x030401;

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

bool handler::IsEncrypted(uint32 index2) const
{
  CNum folderIndex = _db.FileIndexToFolderIndexMap[index2];
  if (folderIndex != kNumNoIndex)
    return _db.Folders[folderIndex].IsEncrypted();
  return false;
}

ex1::HRes handler::GetProperty(uint32 index, int propID,  var *value)
{
  var prop;

  /*
  const CRef2 &ref2 = _refs[index];
  if (ref2.Refs.is_empty())
    return E_FAIL;
  const CRef &ref = ref2.Refs.Front();
  */

  const CFileItem &item = _db.Files[index];
  uint32 index2 = index;

  switch(propID)
  {
  case ::compress::kpidPath:
      if (!item.Name.is_empty())
      {
         throw "should implement following";
       // prop = NItemName::GetOSName(item.Name);
      }
      break;
    case ::compress::kpidIsDir:  prop = item.IsDir; break;
    case ::compress::kpidSize:
    {
      prop = item.get_count;
      // prop = ref2.get_count;
      break;
    }
    case ::compress::kpidPackSize:
    {
      // prop = ref2.PackSize;
      {
        CNum folderIndex = _db.FileIndexToFolderIndexMap[index2];
        if (folderIndex != kNumNoIndex)
        {
          if (_db.FolderStartFileIndex[folderIndex] == (CNum)index2)
            prop = _db.GetFolderFullPackSize(folderIndex);
          /*
          else
            prop = (uint64)0;
          */
        }
        else
          prop = (uint64)0;
      }
      break;
    }
    case ::compress::kpidPosition:  { uint64 v; if (_db.StartPos.GetItem(index2, v)) prop = v; break; }
    case ::compress::kpidCTime:  SetPropFromUInt64Def(_db.CTime, index2, prop); break;
    case ::compress::kpidATime:  SetPropFromUInt64Def(_db.ATime, index2, prop); break;
    case ::compress::kpidMTime:  SetPropFromUInt64Def(_db.MTime, index2, prop); break;
    case ::compress::kpidAttrib:  if (item.AttribDefined) prop = (uint64) item.Attrib; break;
    case ::compress::kpidCRC:  if (item.CrcDefined) prop = (uint64) item.Crc; break;
    case ::compress::kpidEncrypted:  prop = IsEncrypted(index2); break;
    case ::compress::kpidIsAnti:  prop = _db.IsItemAnti(index2); break;
    #ifndef _SFX
    case ::compress::kpidMethod:
      {
        CNum folderIndex = _db.FileIndexToFolderIndexMap[index2];
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
                propsString = ConvertUInt32ToString((uint32)coder.Props[0] + 1);
              else if (coder.MethodID == k_LZMA && coder.Props.GetCapacity() == 5)
              {
                uint32 dicSize = GetUi32((const byte *)coder.Props + 1);
                propsString = GetStringForSizeValue(dicSize);
              }
              else if (coder.MethodID == k_LZMA2 && coder.Props.GetCapacity() == 1)
              {
                byte p = coder.Props[0];
                uint32 dicSize = (((uint32)2 | ((p) & 1)) << ((p) / 2 + 11));
                propsString = GetStringForSizeValue(dicSize);
              }
              else if (coder.MethodID == k_PPMD && coder.Props.GetCapacity() == 5)
              {
                byte order = *(const byte *)coder.Props;
                propsString = L'o';
                propsString += ConvertUInt32ToString(order);
                propsString += L":mem";
                uint32 dicSize = GetUi32((const byte *)coder.Props + 1);
                propsString += GetStringForSizeValue(dicSize);
              }
              else if (coder.MethodID == k_AES && coder.Props.GetCapacity() >= 1)
              {
                const byte *data = (const byte *)coder.Props;
                byte firstByte = *data++;
                uint32 numCyclesPower = firstByte & 0x3F;
                propsString = ConvertUInt32ToString(numCyclesPower);
                /*
                if ((firstByte & 0xC0) != 0)
                {
                  uint32 saltSize = (firstByte >> 7) & 1;
                  uint32 ivSize = (firstByte >> 6) & 1;
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
    case ::compress::kpidBlock:
      {
        CNum folderIndex = _db.FileIndexToFolderIndexMap[index2];
        if (folderIndex != kNumNoIndex)
          prop = (uint64) folderIndex;
      }
      break;
    case kpidPackedSize0:
    case kpidPackedSize1:
    case kpidPackedSize2:
    case kpidPackedSize3:
    case kpidPackedSize4:
      {
        CNum folderIndex = _db.FileIndexToFolderIndexMap[index2];
        if (folderIndex != kNumNoIndex)
        {
          const CFolder &folderInfo = _db.Folders[folderIndex];
          if (_db.FolderStartFileIndex[folderIndex] == (CNum)index2 &&
              folderInfo.PackStreams.get_count() > (int)(propID - kpidPackedSize0))
          {
            prop = _db.GetFolderPackStreamSize(folderIndex, propID - kpidPackedSize0);
          }
          else
            prop = (uint64)0;
        }
        else
          prop = (uint64)0;
      }
      break;
    #endif
  }
  *value = prop;
  return S_OK;
}

ex1::HRes handler::Open(::ex1::byte_input_stream *stream,
    const file_position *maxCheckStartPosition,
    ::compress::archive_open_callback_interface *openArchiveCallback)
{
  Close();
  #ifndef _SFX
  _fileInfoPopIDs.remove_all();
  #endif
  try
  {
    ::ca::smart_pointer < ::compress::archive_open_callback_interface > openArchiveCallbackTemp = openArchiveCallback;

    #ifndef _NO_CRYPTO
    ::ca::smart_pointer < ::crypto::get_text_password_interface > getTextPassword;
    if (openArchiveCallback)
    {
      getTextPassword = dynamic_cast < ::crypto::get_text_password_interface * > (openArchiveCallbackTemp.m_p);
    }
    #endif
    CInArchive archive;
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

ex1::HRes handler::Close()
{
gen::release(_inStream.m_p);
  _db.clear();
  return S_OK;
}

#ifdef __7Z_SET_PROPERTIES
#ifdef EXTRACT_ONLY

ex1::HRes handler::SetProperties(const wchar_t **names, const PROPVARIANT *values, Int32 numProperties)
{
  COM_TRY_BEGIN
  const uint32 numProcessors = NSystem::GetNumberOfProcessors();
  _numThreads = numProcessors;

  for (int i = 0; i < numProperties; i++)
  {
    string name = names[i];
    name.MakeUpper();
    if (name.is_empty())
      return E_INVALIDARG;
    const PROPVARIANT &value = values[i];
    uint32 number;
    int index = ParseStringToUInt32(name, number);
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
   ex1::HRes handler::SetCompressCodecsInfo(::compress::codecs_info_interface * compressCodecsInfo)
   {
      _codecsInfo = compressCodecsInfo;
      return LoadExternalCodecs(_codecsInfo, _externalCodecs);

   }


   /*bool handler::IsSolid(int refIndex)
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

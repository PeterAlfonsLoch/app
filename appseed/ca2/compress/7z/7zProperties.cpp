// 7zProperties.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "StdAfx.h"

#include "7zProperties.h"
#include "7zHeader.h"
#include "7zHandler.h"

// #define _MULTI_PACK


namespace n7z {

struct CPropMap
{
  uint64 FilePropID;
  STATPROPSTG StatPROPSTG;
};

CPropMap kPropMap[] =
{
  { NID::kName, { NULL, ::compress::kpidPath, VT_BSTR } },
  { NID::kSize, { NULL, ::compress::kpidSize, VT_UI8 } },
  { NID::kPackInfo, { NULL,::compress:: kpidPackSize, VT_UI8 } },

  #ifdef _MULTI_PACK
  { 100, { L"Pack0", kpidPackedSize0, VT_UI8 } },
  { 101, { L"Pack1", kpidPackedSize1, VT_UI8 } },
  { 102, { L"Pack2", kpidPackedSize2, VT_UI8 } },
  { 103, { L"Pack3", kpidPackedSize3, VT_UI8 } },
  { 104, { L"Pack4", kpidPackedSize4, VT_UI8 } },
  #endif

  { NID::kCTime, { NULL, ::compress::kpidCTime, VT_FILETIME } },
  { NID::kMTime, { NULL, ::compress::kpidMTime, VT_FILETIME } },
  { NID::kATime, { NULL, ::compress::kpidATime, VT_FILETIME } },
  { NID::kWinAttributes, { NULL, ::compress::kpidAttrib, VT_UI4 } },
  { NID::kStartPos, { NULL, ::compress::kpidPosition, VT_UI4 } },

  { NID::kCRC, { NULL, ::compress::kpidCRC, VT_UI4 } },

  { NID::kAnti, { NULL, ::compress::kpidIsAnti, VT_BOOL } }

  #ifndef _SFX
  ,
  { 97, { NULL,::compress::kpidEncrypted, VT_BOOL } },
  { 98, { NULL,::compress::kpidMethod, VT_BSTR } },
  { 99, { NULL,::compress::kpidBlock, VT_UI4 } }
  #endif
};

static const int kPropMapSize = sizeof(kPropMap) / sizeof(kPropMap[0]);

static int FindPropInMap(uint64 filePropID)
{
  for (int i = 0; i < kPropMapSize; i++)
    if (kPropMap[i].FilePropID == filePropID)
      return i;
  return -1;
}

static void CopyOneItem(base_array<uint64> &src,
    base_array<uint64> &dest, uint32 item)
{
  for (int i = 0; i < src.get_count(); i++)
    if (src[i] == item)
    {
      dest.add(item);
      src.remove_at(i);
      return;
    }
}

static void RemoveOneItem(base_array<uint64> &src, uint32 item)
{
  for (int i = 0; i < src.get_count(); i++)
    if (src[i] == item)
    {
      src.remove_at(i);
      return;
    }
}

static void InsertToHead(base_array<uint64> &dest, uint32 item)
{
  for (int i = 0; i < dest.get_count(); i++)
    if (dest[i] == item)
    {
      dest.remove_at(i);
      break;
    }
  dest.insert_at(0, item);
}

void CHandler::FillPopIDs()
{
  _fileInfoPopIDs.remove_all();

  #ifdef _7Z_VOL
  if(_volumes.get_count() < 1)
    return;
  const CVolume &volume = _volumes.Front();
  const CArchiveDatabaseEx &_db = volume.Database;
  #endif

  base_array<uint64> fileInfoPopIDs = _db.ArchiveInfo.FileInfoPopIDs;

  RemoveOneItem(fileInfoPopIDs, NID::kEmptyStream);
  RemoveOneItem(fileInfoPopIDs, NID::kEmptyFile);

  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kName);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kAnti);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kSize);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kPackInfo);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kCTime);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kMTime);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kATime);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kWinAttributes);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kCRC);
  CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kComment);
  _fileInfoPopIDs.add(fileInfoPopIDs);

  #ifndef _SFX
  _fileInfoPopIDs.add(97);
  _fileInfoPopIDs.add(98);
  _fileInfoPopIDs.add(99);
  #endif
  #ifdef _MULTI_PACK
  _fileInfoPopIDs.add(100);
  _fileInfoPopIDs.add(101);
  _fileInfoPopIDs.add(102);
  _fileInfoPopIDs.add(103);
  _fileInfoPopIDs.add(104);
  #endif

  #ifndef _SFX
  InsertToHead(_fileInfoPopIDs, NID::kMTime);
  InsertToHead(_fileInfoPopIDs, NID::kPackInfo);
  InsertToHead(_fileInfoPopIDs, NID::kSize);
  InsertToHead(_fileInfoPopIDs, NID::kName);
  #endif
}

ex1::HRes CHandler::GetNumberOfProperties(uint32 *numProperties)
{
  *numProperties = _fileInfoPopIDs.get_count();
  return S_OK;
}

ex1::HRes CHandler::GetPropertyInfo(uint32 index, string & name, int * propID, var::e_type *varType)
{
  if ((int)index >= _fileInfoPopIDs.get_count())
    return E_INVALIDARG;
  int indexInMap = FindPropInMap(_fileInfoPopIDs[index]);
  if (indexInMap == -1)
    return E_INVALIDARG;
  const STATPROPSTG &srcItem = kPropMap[indexInMap].StatPROPSTG;
  *propID = srcItem.propid;
  *varType = srcItem.vt;
  name.Empty();
  return S_OK;
}

}

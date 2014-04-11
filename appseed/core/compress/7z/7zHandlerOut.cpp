// 7zHandlerOut.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"

/*#include "../../../Windows/PropVariant.h"

#include "../../../Common/ComTry.h"
#include "../../../Common/StringToInt.h"

#include "../../ICoder.h"

#include "../Common/ItemNameUtils.h"
#include "../Common/ParseProperties.h"

#include "7zHandler.h"
#include "7zOut.h"
#include "7zUpdate.h"*/

//using namespace NWindows;

uint64_t ConvertStringToUInt64(const char *s, const char **end);
int32_t ParseStringToUInt32(const string &srcString, uint32_t &number);


uint64_t ConvertStringToUInt64(const char *s, const char **end)
{
  uint64_t result = 0;
  for (;;)
  {
    char ca = *s;
    if (ca < '0' || ca > '9')
    {
      if (end != NULL)
        *end = s;
      return result;
    }
    result *= 10;
    result += (ca - '0');
    s++;
  }
}


int32_t ParseStringToUInt32(const string &srcString, uint32_t &number)
{
  const char *start = srcString;
  const char *end;
  uint64_t number64 = ConvertStringToUInt64(start, &end);
  if (number64 > 0xFFFFFFFF)
  {
    number = 0;
    return 0;
  }
  number = (uint32_t)number64;
  return (int32_t)(end - start);
}


inline bool IntToBool(int32_t value)
  { return (value != 0); }


namespace n7z
{

   static const char * kLZMAMethodName = "LZMA";
   static const char * kCopyMethod = "Copy";
   static const char * kDefaultMethodName = kLZMAMethodName;

   static const uint32_t kLzmaAlgorithmX5 = 1;
   static const char * kLzmaMatchFinderForHeaders = "BT2";
   static const uint32_t kDictionaryForHeaders =
#ifdef UNDER_CE
      1 << 18
#else
      1 << 20
#endif
      ;
//   static const uint32_t kNumFastBytesForHeaders = 273;
   static const uint32_t kAlgorithmForHeaders = kLzmaAlgorithmX5;

   static inline bool IsCopyMethod(const string &methodName)
   { return (methodName.CompareNoCase(kCopyMethod) == 0); }

   HRes handler::GetFileTimeType(uint32_t *type)
   {
      *type = ::libcompress::NFileTimeType::kWindows;
      return S_OK;
   }

   HRes handler::SetCompressionMethod(
      CCompressionMethodMode &methodMode,
      CCompressionMethodMode &headerMethod)
   {
      HRes res = SetCompressionMethod(methodMode, _methods
#ifndef _7ZIP_ST
         , _numThreads
#endif
         );
      RINOK(res);
      methodMode.Binds = _binds;

      if (_compressHeaders)
      {
         // headerMethod.Methods.add(methodMode.Methods.Back());

         smart_pointer_array < ::libcompress::COneMethodInfo > headerMethodInfoVector;
         ::libcompress::COneMethodInfo & oneMethodInfo = *headerMethodInfoVector.add_new();
         oneMethodInfo.MethodName = kLZMAMethodName;
         oneMethodInfo.Props[NCoderPropID::kMatchFinder] = kLzmaMatchFinderForHeaders;
         oneMethodInfo.Props[NCoderPropID::kAlgorithm] = (int32_t) kAlgorithmForHeaders;
         oneMethodInfo.Props[NCoderPropID::kNumFastBytes] = (int32_t) kAlgorithmForHeaders;
         oneMethodInfo.Props[NCoderPropID::kDictionarySize] = (int32_t) kDictionaryForHeaders;
         
         HRes res = SetCompressionMethod(headerMethod, headerMethodInfoVector
#ifndef _7ZIP_ST
            , 1
#endif
            );
         RINOK(res);
      }
      return S_OK;
   }

   HRes handler::SetCompressionMethod(
      CCompressionMethodMode &methodMode,
      smart_pointer_array < ::libcompress::COneMethodInfo > &methodsInfo
#ifndef _7ZIP_ST
      , uint32_t numThreads
#endif
      )
   {
      uint32_t level = _level;

      if (methodsInfo.is_empty())
      {
         ::libcompress::COneMethodInfo & oneMethodInfo = *methodsInfo.add_new();
         oneMethodInfo.MethodName = ((level == 0) ? kCopyMethod : kDefaultMethodName);
         
      }

      bool needSolid = false;
      for(int32_t i = 0; i < methodsInfo.get_count(); i++)
      {
         ::libcompress::COneMethodInfo &oneMethodInfo = methodsInfo[i];
         SetCompressionMethod2(oneMethodInfo
#ifndef _7ZIP_ST
            , numThreads
#endif
            );

         if (!IsCopyMethod(oneMethodInfo.MethodName))
            needSolid = true;

         CMethodFull & methodFull = *methodMode.Methods.add_new();

         if (!FindMethod(
            _codecsInfo, &_externalCodecs,
            oneMethodInfo.MethodName, methodFull.Id, methodFull.NumInStreams, methodFull.NumOutStreams))
            return E_INVALIDARG;
         methodFull.Props = oneMethodInfo.Props;
         

         if (!_numSolidBytesDefined)
         {
            for (int32_t j = 0; j < methodFull.Props.m_propertya.get_count(); j++)
            {
               const property &prop = methodFull.Props.m_propertya[j];
               if ((atoi(prop.name()) == NCoderPropID::kDictionarySize ||
                  atoi(prop.name()) == NCoderPropID::kUsedMemorySize) && prop.get_value().is_integer())
               {
                  _numSolidBytes = ((uint64_t)prop.get_value().uint64()) << 7;
                  const uint64_t kMinSize = (1 << 24);
                  if (_numSolidBytes < kMinSize)
                     _numSolidBytes = kMinSize;
                  _numSolidBytesDefined = true;
                  break;
               }
            }
         }
      }

      if (!needSolid && !_numSolidBytesDefined)
      {
         _numSolidBytesDefined = true;
         _numSolidBytes  = 0;
      }
      return S_OK;
   }

   #define PROPID int32_t

   static HRes GetTime(::libcompress::archive_update_callback_interface *updateCallback, int32_t index, bool writeTime, PROPID propID, uint64_t &ft, bool &ftDefined)
   {
      ft = 0;
      ftDefined = false;
      if (!writeTime)
         return S_OK;
      var prop;
      RINOK(updateCallback->GetProperty(index, propID, &prop));
      if (prop.get_type() == var::type_filetime)
      {
         ft = prop.m_filetime.dwLowDateTime | ((uint64_t)prop.m_filetime.dwHighDateTime << 32);
         ftDefined = true;
      }
      else if (prop.get_type() != var::type_empty)
         return E_INVALIDARG;
      return S_OK;
   }

   HRes handler::UpdateItems(::file::writer *outStream, uint32_t numItems,
      ::libcompress::archive_update_callback_interface *updateCallback)
   {
         const CArchiveDatabaseEx *db = 0;
#ifdef _7Z_VOL
      if (_volumes.get_count() > 1)
         return E_FAIL;
      const CVolume *volume = 0;
      if (_volumes.get_count() == 1)
      {
         volume = &_volumes.Front();
         db = &volume->Database;
      }
#else
      if (_inStream != NULL)
         db = &_db;
#endif

      smart_pointer_array<CUpdateItem> updateItems;

      for (uint32_t i = 0; i < numItems; i++)
      {
         int32_t newData, newProps;
         uint32_t indexInArchive;
         if (!updateCallback)
            return E_FAIL;
         RINOK(updateCallback->GetUpdateItemInfo(i, &newData, &newProps, &indexInArchive));
         CUpdateItem ui;
         ui.NewProps = IntToBool(newProps);
         ui.NewData = IntToBool(newData);
         ui.IndexInArchive = indexInArchive;
         ui.IndexInClient = i;
         ui.IsAnti = false;
         ui.get_count = 0;

         if (ui.IndexInArchive != -1)
         {
            if (db == 0 || ui.IndexInArchive >= db->Files.get_count())
               return E_INVALIDARG;
            const CFileItem &fi = db->Files[ui.IndexInArchive];
            ui.Name = fi.Name;
            ui.IsDir = fi.IsDir;
            ui.get_count = fi.get_count;
            ui.IsAnti = db->IsItemAnti(ui.IndexInArchive);

            ui.CTimeDefined = db->CTime.GetItem(ui.IndexInArchive, ui.CTime);
            ui.ATimeDefined = db->ATime.GetItem(ui.IndexInArchive, ui.ATime);
            ui.MTimeDefined = db->MTime.GetItem(ui.IndexInArchive, ui.MTime);
         }

         if (ui.NewProps)
         {
            bool nameIsDefined;
            bool folderStatusIsDefined;
            {
               var prop;
               RINOK(updateCallback->GetProperty(i, ::libcompress::kpidAttrib, &prop));
               if (prop.is_empty())
                  ui.AttribDefined = false;
               else if (!prop.is_integer())
                  return E_INVALIDARG;
               else
               {
                  ui.Attrib = prop;
                  ui.AttribDefined = true;
               }
            }

            // we need MTime to sort files.
            RINOK(GetTime(updateCallback, i, WriteCTime, ::libcompress::kpidCTime, ui.CTime, ui.CTimeDefined));
            RINOK(GetTime(updateCallback, i, WriteATime, ::libcompress::kpidATime, ui.ATime, ui.ATimeDefined));
            RINOK(GetTime(updateCallback, i, true,       ::libcompress::kpidMTime, ui.MTime, ui.MTimeDefined));

            {
               var prop;
               RINOK(updateCallback->GetProperty(i, ::libcompress::kpidPath, &prop));
               if (prop.is_empty())
                  nameIsDefined = false;
               else if (prop.get_type() != var::type_string)
                  return E_INVALIDARG;
               else
               {
                  throw "should implement below line";
                  //ui.Name = NItemName::MakeLegalName(prop.bstrVal);
                  nameIsDefined = true;
               }
            }
            {
               var prop;
               RINOK(updateCallback->GetProperty(i, ::libcompress::kpidIsDir, &prop));
               if (prop.is_empty())
                  folderStatusIsDefined = false;
               else if (prop.get_type() != var::type_bool)
                  return E_INVALIDARG;
               else
               {
                  ui.IsDir = prop.m_b;
                  folderStatusIsDefined = true;
               }
            }

            {
               var prop;
               RINOK(updateCallback->GetProperty(i, ::libcompress::kpidIsAnti, &prop));
               if (prop.is_empty())
                  ui.IsAnti = false;
               else if (prop.get_type() != var::type_bool)
                  return E_INVALIDARG;
               else
                  ui.IsAnti = prop.m_b;
            }

            if (ui.IsAnti)
            {
               ui.AttribDefined = false;

               ui.CTimeDefined = false;
               ui.ATimeDefined = false;
               ui.MTimeDefined = false;

               ui.get_count = 0;
            }

            if (!folderStatusIsDefined && ui.AttribDefined)
               ui.SetDirStatusFromAttrib();
         }

         if (ui.NewData)
         {
            var prop;
            RINOK(updateCallback->GetProperty(i, ::libcompress::kpidSize, &prop));
            if (prop.get_type() != var::type_int32) // todo: type_byte
               return E_INVALIDARG;
            ui.get_count = prop;
            if (ui.get_count != 0 && ui.IsAnti)
               return E_INVALIDARG;
         }
         updateItems.add(new CUpdateItem(ui));
      }

      CCompressionMethodMode methodMode, headerMethod;
      RINOK(SetCompressionMethod(methodMode, headerMethod));
#ifndef _7ZIP_ST
      methodMode.NumThreads = _numThreads;
      headerMethod.NumThreads = 1;
#endif

      smart_pointer < ::crypto::get_text_password2_interface > getPassword2;
      getPassword2 = dynamic_cast < ::crypto::get_text_password2_interface * > (updateCallback);

      if (getPassword2)
      {
         string password;
         int32_t passwordIsDefined;
         RINOK(getPassword2->CryptoGetTextPassword2(&passwordIsDefined, password));
         methodMode.PasswordIsDefined = IntToBool(passwordIsDefined);
         if (methodMode.PasswordIsDefined)
            methodMode.Password = password;
      }
      else
         methodMode.PasswordIsDefined = false;

      bool compressMainHeader = _compressHeaders;  // check it

      bool encryptHeaders = false;

      if (methodMode.PasswordIsDefined)
      {
         if (_encryptHeadersSpecified)
            encryptHeaders = _encryptHeaders;
#ifndef _NO_CRYPTO
         else
            encryptHeaders = _passwordIsDefined;
#endif
         compressMainHeader = true;
         if (encryptHeaders)
         {
            headerMethod.PasswordIsDefined = methodMode.PasswordIsDefined;
            headerMethod.Password = methodMode.Password;
         }
      }

      if (numItems < 2)
         compressMainHeader = false;

      CUpdateOptions options;
      options.Method = &methodMode;
      options.HeaderMethod = (_compressHeaders || encryptHeaders) ? &headerMethod : 0;
      options.UseFilters = _level != 0 && _autoFilter;
      options.MaxFilter = _level >= 8;

      options.HeaderOptions.CompressMainHeader = compressMainHeader;
      options.HeaderOptions.WriteCTime = WriteCTime;
      options.HeaderOptions.WriteATime = WriteATime;
      options.HeaderOptions.WriteMTime = WriteMTime;

      options.NumSolidFiles = _numSolidFiles;
      options.NumSolidBytes = _numSolidBytes;
      options.SolidExtension = _solidExtension;
      options.RemoveSfxBlock = _removeSfxBlock;
      options.VolumeMode = _volumeMode;

      COutArchive archive(get_app());
      CArchiveDatabase newDatabase;

      smart_pointer < ::crypto::get_text_password_interface > getPassword;
      getPassword = dynamic_cast < ::crypto::get_text_password_interface * > (updateCallback);

      HRes res = Update(
         _codecsInfo, &_externalCodecs,
#ifdef _7Z_VOL
         volume ? volume->Stream: 0,
         volume ? db : 0,
#else
         _inStream,
         db,
#endif
         updateItems,
         archive, newDatabase, outStream, updateCallback, options
#ifndef _NO_CRYPTO
         , getPassword
#endif
         );

      RINOK(res);

      updateItems.remove_all();

      return archive.WriteDatabase(_codecsInfo, &_externalCodecs, newDatabase, options.HeaderMethod, options.HeaderOptions);
   }

   static HRes GetBindInfoPart(string &srcString, uint32_t &coder, uint32_t &stream)
   {
      stream = 0;
      int32_t index = ParseStringToUInt32(srcString, coder);
      if (index == 0)
         return E_INVALIDARG;
      srcString.Delete(0, index);
      if (srcString[0] == 'S')
      {
         srcString.Delete(0);
         int32_t index = ParseStringToUInt32(srcString, stream);
         if (index == 0)
            return E_INVALIDARG;
         srcString.Delete(0, index);
      }
      return S_OK;
   }

   static HRes GetBindInfo(string &srcString, CBind &bind)
   {
      RINOK(GetBindInfoPart(srcString, bind.OutCoder, bind.OutStream));
      if (srcString[0] != ':')
         return E_INVALIDARG;
      srcString.Delete(0);
      RINOK(GetBindInfoPart(srcString, bind.InCoder, bind.InStream));
      if (!srcString.is_empty())
         return E_INVALIDARG;
      return S_OK;
   }

   HRes handler::SetProperties(const char **names, const var *values, int32_t numProperties)
   {
      _binds.remove_all();
      BeforeSetProperty();

      for (int32_t i = 0; i < numProperties; i++)
      {
         string name = names[i];
         name.make_upper();
         if (name.is_empty())
            return E_INVALIDARG;

         const var &value = values[i];

         if (name[0] == 'B')
         {
            name.Delete(0);
            CBind bind;
            RINOK(GetBindInfo(name, bind));
            _binds.add(bind);
            continue;
         }

         RINOK(SetProperty(name, value));
      }

      return S_OK;
   }

} // namespace n7z

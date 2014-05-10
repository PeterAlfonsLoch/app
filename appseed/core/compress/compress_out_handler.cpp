// HandlerOut.cpp
// from 7-zip on morning of 13/01/2001 - Thursday

#include "framework.h"

/*#include "../../../Common/StringToInt.h"

#include "../../../Windows/PropVariant.h"

#ifndef _7ZIP_ST
#include "../../../Windows/System.h"
#endif

#include "../../ICoder.h"

#include "../Common/ParseProperties.h"

#include "HandlerOut.h"*/

bool StringToBool(const string &s, bool &res);
int32_t ParseStringToUInt32(const string &srcString, uint32_t &number);
uint64_t ConvertStringToUInt64(const char *s, const char **end);

namespace libcompress
{

//   static const char *kCopyMethod = "Copy";
   static const char *kLZMAMethodName = "LZMA";
   static const char *kLZMA2MethodName = "LZMA2";
   static const char *kBZip2MethodName = "BZip2";
   static const char *kPpmdMethodName = "PPMd";
   static const char *kDeflateMethodName = "Deflate";
   static const char *kDeflate64MethodName = "Deflate64";

   static const char *kLzmaMatchFinderX1 = "HC4";
   static const char *kLzmaMatchFinderX5 = "BT4";

   static const uint32_t kLzmaAlgoX1 = 0;
   static const uint32_t kLzmaAlgoX5 = 1;

   static const uint32_t kLzmaDicSizeX1 = 1 << 16;
   static const uint32_t kLzmaDicSizeX3 = 1 << 20;
   static const uint32_t kLzmaDicSizeX5 = 1 << 24;
   static const uint32_t kLzmaDicSizeX7 = 1 << 25;
   static const uint32_t kLzmaDicSizeX9 = 1 << 26;

   static const uint32_t kLzmaFastBytesX1 = 32;
   static const uint32_t kLzmaFastBytesX7 = 64;

   static const uint32_t kPpmdMemSizeX1 = (1 << 22);
   static const uint32_t kPpmdMemSizeX5 = (1 << 24);
   static const uint32_t kPpmdMemSizeX7 = (1 << 26);
   static const uint32_t kPpmdMemSizeX9 = (192 << 20);

   static const uint32_t kPpmdOrderX1 = 4;
   static const uint32_t kPpmdOrderX5 = 6;
   static const uint32_t kPpmdOrderX7 = 16;
   static const uint32_t kPpmdOrderX9 = 32;

   static const uint32_t kDeflateAlgoX1 = 0;
   static const uint32_t kDeflateAlgoX5 = 1;

   static const uint32_t kDeflateFastBytesX1 = 32;
   static const uint32_t kDeflateFastBytesX7 = 64;
   static const uint32_t kDeflateFastBytesX9 = 128;

   static const uint32_t kDeflatePassesX1 = 1;
   static const uint32_t kDeflatePassesX7 = 3;
   static const uint32_t kDeflatePassesX9 = 10;

   static const uint32_t kBZip2NumPassesX1 = 1;
   static const uint32_t kBZip2NumPassesX7 = 2;
   static const uint32_t kBZip2NumPassesX9 = 7;

   static const uint32_t kBZip2DicSizeX1 = 100000;
   static const uint32_t kBZip2DicSizeX3 = 500000;
   static const uint32_t kBZip2DicSizeX5 = 900000;

   static const char *kDefaultMethodName = kLZMAMethodName;

//   static const char *kLzmaMatchFinderForHeaders = "BT2";
//   static const uint32_t kDictionaryForHeaders = 1 << 20;
//   static const uint32_t kNumFastBytesForHeaders = 273;
//   static const uint32_t kAlgorithmForHeaders = kLzmaAlgoX5;

   static bool AreEqual(const string &methodName, const char *s)
   { return (methodName.CompareNoCase(s) == 0); }

   bool COneMethodInfo::IsLzma() const
   {
      return
         AreEqual(MethodName, kLZMAMethodName) ||
         AreEqual(MethodName, kLZMA2MethodName);
   }

   static inline bool IsBZip2Method(const string &methodName)
   { return AreEqual(methodName, kBZip2MethodName); }

   static inline bool IsPpmdMethod(const string &methodName)
   { return AreEqual(methodName, kPpmdMethodName); }

   static inline bool IsDeflateMethod(const string &methodName)
   {
      return
         AreEqual(methodName, kDeflateMethodName) ||
         AreEqual(methodName, kDeflate64MethodName);
   }

   #define PROPID int32_t

   struct CNameToPropID
   {
      PROPID PropID;
      var::e_type VarType;
      const char *Name;
   };

   static CNameToPropID g_NameToPropID[] =
   {
      { NCoderPropID::kBlockSize, var::type_int32, "C" },
      { NCoderPropID::kDictionarySize, var::type_int32, "D" },
      { NCoderPropID::kUsedMemorySize, var::type_int32, "MEM" },

      { NCoderPropID::kOrder, var::type_int32, "O" },
      { NCoderPropID::kPosStateBits, var::type_int32, "PB" },
      { NCoderPropID::kLitContextBits, var::type_int32, "LC" },
      { NCoderPropID::kLitPosBits, var::type_int32, "LP" },
      { NCoderPropID::kEndMarker, var::type_bool, "eos" },

      { NCoderPropID::kNumPasses, var::type_int32, "Pass" },
      { NCoderPropID::kNumFastBytes, var::type_int32, "fb" },
      { NCoderPropID::kMatchFinderCycles, var::type_int32, "mc" },
      { NCoderPropID::kAlgorithm, var::type_int32, "a" },
      { NCoderPropID::kMatchFinder, var::type_string, "mf" },
      { NCoderPropID::kNumThreads, var::type_int32, "mt" },
      { NCoderPropID::kDefaultProp, var::type_int32, "" }
   };

    bool ConvertProperty(var srcProp, var::e_type varType, var &destProp);
    
   bool ConvertProperty(var srcProp, var::e_type varType, var &destProp)
   {
      if (varType == srcProp.get_type())
      {
         destProp = srcProp;
         return true;
      }
      throw "should implement below";
      /*if (varType == VT_UI1)
      {
         if (srcProp.vt == var::type_int32)
         {
            uint32_t value = srcProp.ulVal;
            if (value > 0xFF)
               return false;
            destProp = (byte)value;
            return true;
         }
      }
      else if (varType == var::type_bool)
      {
         bool res;
         if (SetBoolProperty(res, srcProp) != S_OK)
            return false;
         destProp = res;
         return true;
      }*/
      return false;
   }

   static int32_t FindPropIdExact(const string &name)
   {
      for (int32_t i = 0; i < sizeof(g_NameToPropID) / sizeof(g_NameToPropID[0]); i++)
         if (name.CompareNoCase(g_NameToPropID[i].Name) == 0)
            return i;
      return -1;
   }

   static int32_t FindPropIdStart(const string &name)
   {
      for (int32_t i = 0; i < sizeof(g_NameToPropID) / sizeof(g_NameToPropID[0]); i++)
      {
         string t = g_NameToPropID[i].Name;
         if (t.CompareNoCase(name.Left(t.get_length())) == 0)
            return i;
      }
      return -1;
   }

   static void SetMethodProp(COneMethodInfo &m, int32_t propID, var value)
   {
      for (int32_t j = 0; j < m.Props.m_propertya.get_count(); j++)
         if (atoi(m.Props[j].name()) == propID)
            return;
      m.Props[propID] = value;
   }

   out_handler::out_handler(sp(::base::application) papp) :
      element(papp)
   {
   }

   void out_handler::SetCompressionMethod2(COneMethodInfo &oneMethodInfo
#ifndef _7ZIP_ST
      , uint32_t numThreads
#endif
      )
   {
      uint32_t level = _level;
      if (oneMethodInfo.MethodName.is_empty())
         oneMethodInfo.MethodName = kDefaultMethodName;

      if (oneMethodInfo.IsLzma())
      {
         uint32_t dicSize =
            (level >= 9 ? kLzmaDicSizeX9 :
            (level >= 7 ? kLzmaDicSizeX7 :
            (level >= 5 ? kLzmaDicSizeX5 :
            (level >= 3 ? kLzmaDicSizeX3 :
            kLzmaDicSizeX1))));

         uint32_t algo =
            (level >= 5 ? kLzmaAlgoX5 :
            kLzmaAlgoX1);

         uint32_t fastBytes =
            (level >= 7 ? kLzmaFastBytesX7 :
            kLzmaFastBytesX1);

         const char *matchFinder =
            (level >= 5 ? kLzmaMatchFinderX5 :
            kLzmaMatchFinderX1);

         SetMethodProp(oneMethodInfo, NCoderPropID::kDictionarySize, dicSize);
         SetMethodProp(oneMethodInfo, NCoderPropID::kAlgorithm, algo);
         SetMethodProp(oneMethodInfo, NCoderPropID::kNumFastBytes, fastBytes);
         SetMethodProp(oneMethodInfo, NCoderPropID::kMatchFinder, matchFinder);
#ifndef _7ZIP_ST
         SetMethodProp(oneMethodInfo, NCoderPropID::kNumThreads, numThreads);
#endif
      }
      else if (IsDeflateMethod(oneMethodInfo.MethodName))
      {
         uint32_t fastBytes =
            (level >= 9 ? kDeflateFastBytesX9 :
            (level >= 7 ? kDeflateFastBytesX7 :
            kDeflateFastBytesX1));

         uint32_t numPasses =
            (level >= 9 ? kDeflatePassesX9 :
            (level >= 7 ? kDeflatePassesX7 :
            kDeflatePassesX1));

         uint32_t algo =
            (level >= 5 ? kDeflateAlgoX5 :
            kDeflateAlgoX1);

         SetMethodProp(oneMethodInfo, NCoderPropID::kAlgorithm, algo);
         SetMethodProp(oneMethodInfo, NCoderPropID::kNumFastBytes, fastBytes);
         SetMethodProp(oneMethodInfo, NCoderPropID::kNumPasses, numPasses);
      }
      else if (IsBZip2Method(oneMethodInfo.MethodName))
      {
         uint32_t numPasses =
            (level >= 9 ? kBZip2NumPassesX9 :
            (level >= 7 ? kBZip2NumPassesX7 :
            kBZip2NumPassesX1));

         uint32_t dicSize =
            (level >= 5 ? kBZip2DicSizeX5 :
            (level >= 3 ? kBZip2DicSizeX3 :
            kBZip2DicSizeX1));

         SetMethodProp(oneMethodInfo, NCoderPropID::kNumPasses, numPasses);
         SetMethodProp(oneMethodInfo, NCoderPropID::kDictionarySize, dicSize);
#ifndef _7ZIP_ST
         SetMethodProp(oneMethodInfo, NCoderPropID::kNumThreads, numThreads);
#endif
      }
      else if (IsPpmdMethod(oneMethodInfo.MethodName))
      {
         uint32_t useMemSize =
            (level >= 9 ? kPpmdMemSizeX9 :
            (level >= 7 ? kPpmdMemSizeX7 :
            (level >= 5 ? kPpmdMemSizeX5 :
            kPpmdMemSizeX1)));

         uint32_t order =
            (level >= 9 ? kPpmdOrderX9 :
            (level >= 7 ? kPpmdOrderX7 :
            (level >= 5 ? kPpmdOrderX5 :
            kPpmdOrderX1)));

         SetMethodProp(oneMethodInfo, NCoderPropID::kUsedMemorySize, useMemSize);
         SetMethodProp(oneMethodInfo, NCoderPropID::kOrder, order);
      }
   }

   static void SplitParams(const string &srcString, stringa &subStrings)
   {
      subStrings.clear();
      string name;
      strsize len = srcString.get_length();
      if (len == 0)
         return;
      for (int32_t i = 0; i < len; i++)
      {
         char ca = srcString[i];
         if (ca == L':')
         {
            subStrings.add(name);
            name.Empty();
         }
         else
            name += ca;
      }
      subStrings.add(name);
   }

   static void SplitParam(const string &param, string &name, string &value)
   {
      strsize eqPos = param.find(L'=');
      if (eqPos >= 0)
      {
         name = param.Left(eqPos);
         value = param.Mid(eqPos + 1);
         return;
      }
      for(strsize i = 0; i < param.get_length(); i++)
      {
         char ca = param[i];
         if (ca >= '0' && ca <= '9')
         {
            name = param.Left(i);
            value = param.Mid(i);
            return;
         }
      }
      name = param;
   }

   HRes out_handler::SetParam(COneMethodInfo &oneMethodInfo, const string &name, const string &value)
   {
      property prop;
      int32_t index = FindPropIdExact(name);
      if (index < 0)
         return E_INVALIDARG;
      const CNameToPropID &nameToPropID = g_NameToPropID[index];
      prop.set_name(::str::from(nameToPropID.PropID));

      if (atoi(prop.name()) == NCoderPropID::kBlockSize ||
         atoi(prop.name()) == NCoderPropID::kDictionarySize ||
         atoi(prop.name()) == NCoderPropID::kUsedMemorySize)
      {
         throw "should implement below";
         /*
         uint32_t dicSize;
         RINOK(ParsePropDictionaryValue(value, dicSize));
         prop.Value = dicSize;
         */
      }
      else
      {
         var propValue;

         if (nameToPropID.VarType == var::type_string)
            propValue = value;
         else if (nameToPropID.VarType == var::type_bool)
         {
            bool res;
            if (!StringToBool(value, res))
               return E_INVALIDARG;
            propValue = res;
         }
         else
         {
            uint32_t number;
            if (ParseStringToUInt32(value, number) == value.get_length())
               propValue = number;
            else
               propValue = value;
         }

         throw not_implemented(get_app());
         //if (!ConvertProperty(propValue, nameToPropID.VarType, prop.get_value()))
           // return E_INVALIDARG;
      }
      oneMethodInfo.Props.add(prop);
      return S_OK;
   }

   HRes out_handler::SetParams(COneMethodInfo &oneMethodInfo, const string &srcString)
   {
      stringa params;
      SplitParams(srcString, params);
      if (params.get_size() > 0)
         oneMethodInfo.MethodName = params[0];
      for (int32_t i = 1; i < params.get_size(); i++)
      {
         const string &param = params[i];
         string name, value;
         SplitParam(param, name, value);
         RINOK(SetParam(oneMethodInfo, name, value));
      }
      return S_OK;
   }

   HRes out_handler::SetSolidSettings(const string &s)
   {
      string s2 = s;
      s2.make_upper();
      for (int32_t i = 0; i < s2.get_length();)
      {
         const char *start = ((const char *)s2) + i;
         const char *end;
         uint64_t v = ConvertStringToUInt64(start, &end);
         if (start == end)
         {
            if (s2[i++] != 'E')
               return E_INVALIDARG;
            _solidExtension = true;
            continue;
         }
         i += (int32_t)(end - start);
         if (i == s2.get_length())
            return E_INVALIDARG;
         char ca = s2[i++];
         switch(ca)
         {
         case 'F':
            if (v < 1)
               v = 1;
            _numSolidFiles = v;
            break;
         case 'B':
            _numSolidBytes = v;
            _numSolidBytesDefined = true;
            break;
         case 'K':
            _numSolidBytes = (v << 10);
            _numSolidBytesDefined = true;
            break;
         case 'M':
            _numSolidBytes = (v << 20);
            _numSolidBytesDefined = true;
            break;
         case 'G':
            _numSolidBytes = (v << 30);
            _numSolidBytesDefined = true;
            break;
         default:
            return E_INVALIDARG;
         }
      }
      return S_OK;
   }

   HRes out_handler::SetSolidSettings(var value)
   {
      bool isSolid;
      switch(value.get_type())
      {
      case var::type_empty:
         isSolid = true;
         break;
      case var::type_bool:
         isSolid = (value.m_b != false);
         break;
      case var::type_string:
         if(StringToBool(value, isSolid))
            break;
         return SetSolidSettings(value.get_string());
      default:
         return E_INVALIDARG;
      }
      if (isSolid)
         InitSolid();
      else
         _numSolidFiles = 1;
      return S_OK;
   }

   void out_handler::Init()
   {
      _removeSfxBlock = false;
      _compressHeaders = true;
      _encryptHeadersSpecified = false;
      _encryptHeaders = false;

      WriteCTime = false;
      WriteATime = false;
      WriteMTime = true;

#ifndef _7ZIP_ST
      throw "should implement below";
      //_numThreads = NSystem::GetNumberOfProcessors();
#endif

      _level = 5;
      _autoFilter = true;
      _volumeMode = false;
      _crcSize = 4;
      InitSolid();
   }

   void out_handler::BeforeSetProperty()
   {
      Init();
#ifndef _7ZIP_ST
      throw "should implement below";
//      numProcessors = NSystem::GetNumberOfProcessors();
#endif

      mainDicSize = 0xFFFFFFFF;
      mainDicMethodIndex = 0xFFFFFFFF;
      minNumber = 0;
      _crcSize = 4;
   }

   HRes out_handler::SetProperty(const char *nameSpec, var value)
   {
      string name = nameSpec;
      name.make_upper();
      if (name.is_empty())
         return E_INVALIDARG;

      if (name[0] == 'X')
      {
         name.Delete(0);
         _level = 9;
         throw "should implement below";
         //return ParsePropValue(name, value, _level);
      }

      if (name[0] == 'S')
      {
         name.Delete(0);
         if (name.is_empty())
            return SetSolidSettings(value);
         if (!value.is_empty())
            return E_INVALIDARG;
         return SetSolidSettings(name);
      }

      if (name == "CRC")
      {
         _crcSize = 4;
         name.Delete(0, 3);
         throw "should implement below";
         //return ParsePropValue(name, value, _crcSize);
      }

      uint32_t number;
      int32_t index = ParseStringToUInt32(name, number);
      string realName = name.Mid(index);
      if (index == 0)
      {
         if(name.Left(2).CompareNoCase("MT") == 0)
         {
#ifndef _7ZIP_ST
            throw "should implement below";
            //RINOK(ParseMtProp(name.Mid(2), value, numProcessors, _numThreads));
#endif
            return S_OK;
         }
         throw "should implement below";
         /*if (name.CompareNoCase("RSFX") == 0)  return SetBoolProperty(_removeSfxBlock, value);
         if (name.CompareNoCase("F") == 0) return SetBoolProperty(_autoFilter, value);
         if (name.CompareNoCase("HC") == 0) return SetBoolProperty(_compressHeaders, value);
         if (name.CompareNoCase("HCF") == 0)
         {
            bool compressHeadersFull = true;
            RINOK(SetBoolProperty(compressHeadersFull, value));
            if (!compressHeadersFull)
               return E_INVALIDARG;
            return S_OK;
         }
         if (name.CompareNoCase("HE") == 0)
         {
            RINOK(SetBoolProperty(_encryptHeaders, value));
            _encryptHeadersSpecified = true;
            return S_OK;
         }
         if (name.CompareNoCase("TC") == 0) return SetBoolProperty(WriteCTime, value);
         if (name.CompareNoCase("TA") == 0) return SetBoolProperty(WriteATime, value);
         if (name.CompareNoCase("TM") == 0) return SetBoolProperty(WriteMTime, value);
         if (name.CompareNoCase("V") == 0) return SetBoolProperty(_volumeMode, value);
         number = 0;*/
      }
      if (number > 10000)
         return E_FAIL;
      if (number < minNumber)
         return E_INVALIDARG;
      number -= minNumber;
      for(::count j = _methods.get_size(); j <= (int32_t)number; j++)
      {
         _methods.add(new COneMethodInfo);
      }

      COneMethodInfo &oneMethodInfo = _methods[number];

      if (realName.get_length() == 0)
      {
         if (value.get_type() != var::type_string)
            return E_INVALIDARG;
         throw "should implement below";
         //RINOK(SetParams(oneMethodInfo, value.bstrVal));
      }
      else
      {
         int32_t index = FindPropIdStart(realName);
         if (index < 0)
            return E_INVALIDARG;
         const CNameToPropID &nameToPropID = g_NameToPropID[index];
         property prop;
         prop.set_name(::str::from(nameToPropID.PropID));

         if (atoi(prop.name()) == NCoderPropID::kBlockSize ||
            atoi(prop.name()) == NCoderPropID::kDictionarySize ||
            atoi(prop.name()) == NCoderPropID::kUsedMemorySize)
         {
            uint32_t dicSize;
            throw "should implement below";
            //RINOK(ParsePropDictionaryValue(realName.Mid(MyStringLen(nameToPropID.Name)), value, dicSize));
            //prop.Value = dicSize;
            if (number <= mainDicMethodIndex)
               mainDicSize = dicSize;
         }
         else
         {
            int32_t index = FindPropIdExact(realName);
            if (index < 0)
               return E_INVALIDARG;
            const CNameToPropID &nameToPropID = g_NameToPropID[index];
            prop.set_name(::str::from(nameToPropID.PropID));
            throw not_implemented(get_app());
            //if (!ConvertProperty(value, nameToPropID.VarType, prop.get_value()))
              // return E_INVALIDARG;
         }
         oneMethodInfo.Props.add(prop);
      }
      return S_OK;
   }

} // namespace libcompress

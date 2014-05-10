// 7zUpdate.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"

/*#include "../../../../C/CpuArch.h"

#include "../../Common/LimitedStreams.h"
#include "../../Common/ProgressUtils.h"

#include "../../Common/CreateCoder.h"

#include "../../Compress/CopyCoder.h"

#include "../Common/ItemNameUtils.h"
#include "../Common/OutStreamWithCRC.h"

#include "7zDecode.h"
#include "7zEncode.h"
#include "7zFolderInStream.h"
#include "7zHandler.h"
#include "7zOut.h"
#include "7zUpdate.h"*/



namespace n7z
{

   wchar_t MyCharUpper(wchar_t ca);
   wchar_t MyCharLower(wchar_t ca);
   int32_t MyStringCompareNoCase(const wchar_t *s1, const wchar_t *s2);
   int32_t MyStringCompareNoCase(const char *s1, const char *s2);
   int32_t GetExtIndex(const char *ext);


   template <class T> inline int32_t MyCompare(T a, T b)
   {  return a < b ? -1 : (a == b ? 0 : 1); }

   wchar_t MyCharUpper(wchar_t ca)
   {
      return ::str::ch::to_upper_case(ca);
   }

   wchar_t MyCharLower(wchar_t ca)
   {
      return ::str::ch::to_lower_case(ca);
   }


   int32_t MyStringCompareNoCase(const wchar_t *s1, const wchar_t *s2)
   {
      for (;;)
      {
         wchar_t c1 = *s1++;
         wchar_t c2 = *s2++;
         if (c1 != c2)
         {
            wchar_t u1 = MyCharUpper(c1);
            wchar_t u2 = MyCharUpper(c2);
            if (u1 < u2) return -1;
            if (u1 > u2) return 1;
         }
         if (c1 == 0) return 0;
      }
   }

   int32_t MyStringCompareNoCase(const char *s1, const char *s2)
   {
      string str1(s1);
      string str2(s2);
      return str1.CompareNoCase(str2);
   }


   static const uint64_t k_LZMA = 0x030101;
   static const uint64_t k_BCJ  = 0x03030103;
   static const uint64_t k_BCJ2 = 0x0303011B;

   static const wchar_t *kMatchFinderForBCJ2_LZMA = L"BT2";
   static const uint32_t kDictionaryForBCJ2_LZMA = 1 << 20;
   static const uint32_t kAlgorithmForBCJ2_LZMA = 1;
   static const uint32_t kNumFastBytesForBCJ2_LZMA = 64;

#ifdef MY_CPU_X86_OR_AMD64
#define USE_86_FILTER
#endif

   static HRESULT WriteRange(::file::input_stream *inStream, ::file::writer *outStream,
      uint64_t position, uint64_t size, ::libcompress::progress_info_interface *progress)
   {
      inStream->seek(position, ::file::seek_begin);
      ::file::limited_reader *streamSpec = new ::file::limited_reader;
      smart_pointer < ::file::limited_reader > inStreamLimited(streamSpec);
      streamSpec->SetStream(inStream);
      streamSpec->Init(size);

      ::libcompress::copy_coder *copyCoderSpec = new ::libcompress::copy_coder;
      smart_pointer < ::libcompress::coder_interface > copyCoder = copyCoderSpec;
      RINOK(copyCoder->Code(inStreamLimited, outStream, NULL, NULL, progress));
      return (copyCoderSpec->TotalSize == size ? S_OK : E_FAIL);
   }

   static strsize GetReverseSlashPos(const string &name)
   {
      strsize slashPos = name.reverse_find(L'/');
#ifdef _WIN32
      strsize slash1Pos = name.reverse_find(L'\\');
      slashPos = max(slashPos, slash1Pos);
#endif
      return slashPos;
   }

   strsize CUpdateItem::GetExtensionPos() const
   {
      strsize slashPos = GetReverseSlashPos(Name);
      strsize dotPos = Name.reverse_find(L'.');
      if (dotPos < 0 || (dotPos < slashPos && slashPos >= 0))
         return Name.get_length();
      return dotPos + 1;
   }

   string CUpdateItem::GetExtension() const
   {
      return Name.Mid(GetExtensionPos());
   }

#define RINOZ(x) { int32_t __tt = (x); if (__tt != 0) return __tt; }

#define RINOZ_COMP(a, b) RINOZ(MyCompare(a, b))

   static int32_t CompareBuffers(const ::file::byte_buffer &a1, const ::file::byte_buffer &a2)
   {
      size_t c1 = a1.GetCapacity();
      size_t c2 = a2.GetCapacity();
      RINOZ_COMP(c1, c2);
      for (size_t i = 0; i < c1; i++)
         RINOZ_COMP(a1[i], a2[i]);
      return 0;
   }

   static int32_t CompareCoders(const CCoderInfo &c1, const CCoderInfo &c2)
   {
      RINOZ_COMP(c1.NumInStreams, c2.NumInStreams);
      RINOZ_COMP(c1.NumOutStreams, c2.NumOutStreams);
      RINOZ_COMP(c1.MethodID, c2.MethodID);
      return CompareBuffers(c1.Props, c2.Props);
   }

   static int32_t CompareBindPairs(const CBindPair &b1, const CBindPair &b2)
   {
      RINOZ_COMP(b1.InIndex, b2.InIndex);
      return MyCompare(b1.OutIndex, b2.OutIndex);
   }

   static int32_t CompareFolders(const CFolder &f1, const CFolder &f2)
   {

      ::count s1 = f1.Coders.get_count();

      ::count s2 = f2.Coders.get_count();

      RINOZ_COMP(s1, s2);

      index i;

      for(i = 0; i < s1; i++)
         RINOZ(CompareCoders(f1.Coders[i], f2.Coders[i]));

      s1 = f1.BindPairs.get_count();

      s2 = f2.BindPairs.get_count();

      RINOZ_COMP(s1, s2);

      for (i = 0; i < s1; i++)
         RINOZ(CompareBindPairs(f1.BindPairs[i], f2.BindPairs[i]));

      return 0;

   }

   /*
   static int32_t CompareFiles(const CFileItem &f1, const CFileItem &f2)
   {
   return MyStringCompareNoCase(f1.Name, f2.Name);
   }
   */

   struct CFolderRepack
   {
      int32_t FolderIndex;
      int32_t Group;
      CNum NumCopyFiles;
   };

    int32_t CompareFolderRepacks(const CFolderRepack *p1, const CFolderRepack *p2, void *param);
    
   int32_t CompareFolderRepacks(const CFolderRepack *p1, const CFolderRepack *p2, void *param)
   {
      RINOZ_COMP(p1->Group, p2->Group);
      int32_t i1 = p1->FolderIndex;
      int32_t i2 = p2->FolderIndex;
      const CArchiveDatabaseEx &db = *(const CArchiveDatabaseEx *)param;
      RINOZ(CompareFolders(
         db.Folders[i1],
         db.Folders[i2]));
      return MyCompare(i1, i2);
      /*
      RINOZ_COMP(
      db.NumUnpackStreamsVector[i1],
      db.NumUnpackStreamsVector[i2]);
      if (db.NumUnpackStreamsVector[i1] == 0)
      return 0;
      return CompareFiles(
      db.Files[db.FolderStartFileIndex[i1]],
      db.Files[db.FolderStartFileIndex[i2]]);
      */
   }

   ////////////////////////////////////////////////////////////
    int32_t CompareEmptyItems(const int32_t *p1, const int32_t *p2, void *param);

   int32_t CompareEmptyItems(const int32_t *p1, const int32_t *p2, void *param)
   {
      const smart_pointer_array<CUpdateItem> &updateItems = *(const smart_pointer_array<CUpdateItem> *)param;
      const CUpdateItem &u1 = updateItems[*p1];
      const CUpdateItem &u2 = updateItems[*p2];
      if (u1.IsDir != u2.IsDir)
         return (u1.IsDir) ? 1 : -1;
      if (u1.IsDir)
      {
         if (u1.IsAnti != u2.IsAnti)
            return (u1.IsAnti ? 1 : -1);
         int32_t n = MyStringCompareNoCase(u1.Name, u2.Name);
         return -n;
      }
      if (u1.IsAnti != u2.IsAnti)
         return (u1.IsAnti ? 1 : -1);
      return MyStringCompareNoCase(u1.Name, u2.Name);
   }

   static const char *g_Exts =
      " lzma 7z ace arc arj bz bz2 deb lzo lzx gz pak rpm sit tgz tbz tbz2 tgz cab ha lha lzh rar zoo"
      " zip jar ear war msi"
      " 3gp avi mov mpeg mpg mpe wmv"
      " aac ape fla flac la mp3 m4a mp4 ofr ogg pac ra rm rka shn swa tta wv wma wav"
      " swf "
      " chm hxi hxs"
      " gif jpeg jpg jp2 png tiff  bmp ico psd psp"
      " awg ps eps cgm dxf svg vrml wmf emf ai md"
      " cad dwg pps key sxi"
      " max 3ds"
      " iso bin nrg mdf img pdi tar cpio xpi"
      " vfd vhd vud vmc vsv"
      " vmdk dsk nvram vmem vmsd vmsn vmss vmtm"
      " inl inc idl acf asa h hpp hxx ca cpp cxx rc java cs pas bas vb cls ctl frm dlg def"
      " f77 f f90 f95"
      " asm sql manifest dep "
      " mak clw csproj vcproj sln dsp dsw "
      " class "
      " bat cmd"
      " xml xsd xsl xslt hxk hxc htm html xhtml xht mht mhtml htw asp aspx css cgi jsp shtml"
      " awk sed hta js php php3 php4 php5 phptml pl pm py pyo rb sh tcl vbs"
      " text txt tex ans asc srt reg ini doc docx mcw dot rtf hlp xls xlr xlt xlw ppt pdf"
      " sxc sxd sxi sxg sxw stc sti stw stm odt ott odg otg odp otp ods ots odf"
      " abw afp cwk lwp wpd wps wpt wrf wri"
      " abf afm bdf fon mgf otf pcf pfa snf ttf"
      " dbf mdb nsf ntf wdb db fdb gdb"
      " exe dll ocx vbx sfx sys tlb awx com obj lib out o so "
      " pdb pch idb ncb opt";

   int32_t GetExtIndex(const char *ext)
   {
      int32_t extIndex = 1;
      const char *p = g_Exts;
      for (;;)
      {
         char ca = *p++;
         if (ca == 0)
            return extIndex;
         if (ca == ' ')
            continue;
         int32_t pos = 0;
         for (;;)
         {
            char c2 = ext[pos++];
            if (c2 == 0 && (ca == 0 || ca == ' '))
               return extIndex;
            if (ca != c2)
               break;
            ca = *p++;
         }
         extIndex++;
         for (;;)
         {
            if (ca == 0)
               return extIndex;
            if (ca == ' ')
               break;
            ca = *p++;
         }
      }
   }

   struct CRefItem :
      virtual element
   {
      const CUpdateItem *UpdateItem;
      strsize Index;
      strsize ExtensionPos;
      strsize NamePos;
      strsize ExtensionIndex;
      CRefItem(uint32_t index, const CUpdateItem &ui, bool sortByType):
      UpdateItem(&ui),
         Index(index),
         ExtensionPos(0),
         NamePos(0),
         ExtensionIndex(0)
      {
         if (sortByType)
         {

            strsize slashPos = GetReverseSlashPos(ui.Name);

            NamePos = ((slashPos >= 0) ? (slashPos + 1) : 0);

            strsize  dotPos = ui.Name.reverse_find(L'.');

            if (dotPos < 0 || (dotPos < slashPos && slashPos >= 0))
               ExtensionPos = (uint32_t) ui.Name.get_length();
            else
            {
               ExtensionPos = dotPos + 1;
               string us = ui.Name.Mid(ExtensionPos);
               if (!us.is_empty())
               {
                  us.make_lower();
                  int32_t i;
                  string s;
                  for (i = 0; i < us.get_length(); i++)
                  {
                     wchar_t ca = us[i];
                     if (ca >= 0x80)
                        break;
                     s += (char)ca;
                  }
                  if (i == us.get_length())
                     ExtensionIndex = GetExtIndex(s);
                  else
                     ExtensionIndex = 0;
               }
            }
         }
      }
   };

   // implement below
/*   static int32_t CompareUpdateItems(const CRefItem *p1, const CRefItem *p2, void *param)
   {
      const CRefItem &a1 = *p1;
      const CRefItem &a2 = *p2;
      const CUpdateItem &u1 = *a1.UpdateItem;
      const CUpdateItem &u2 = *a2.UpdateItem;
      int32_t n;
      if (u1.IsDir != u2.IsDir)
         return (u1.IsDir) ? 1 : -1;
      if (u1.IsDir)
      {
         if (u1.IsAnti != u2.IsAnti)
            return (u1.IsAnti ? 1 : -1);
         n = MyStringCompareNoCase(u1.Name, u2.Name);
         return -n;
      }
      bool sortByType = *(bool *)param;
      if (sortByType)
      {
         RINOZ_COMP(a1.ExtensionIndex, a2.ExtensionIndex);
         RINOZ(System.file().extension(u1.Name).CompareNoCase(System.file().extension(u2.Name)));
         RINOZ(System.file().name_(u1.Name).CompareNoCase(System.file().name_(u2.Name)));
         if (!u1.MTimeDefined && u2.MTimeDefined) return 1;
         if (u1.MTimeDefined && !u2.MTimeDefined) return -1;
         if (u1.MTimeDefined && u2.MTimeDefined) RINOZ_COMP(u1.MTime, u2.MTime);
         RINOZ_COMP(u1.get_count, u2.get_count);
      }
      return MyStringCompareNoCase(u1.Name, u2.Name);
   }
   */

   struct CSolidGroup : 
      virtual element
   {
      array<uint32_t> Indices;
   };

   static const char *g_ExeExts[] =
   {
      "dll",
      "exe",
      "ocx",
      "sfx",
      "sys"
   };

   static bool IsExeExt(const string &ext)
   {
      for (int32_t i = 0; i < sizeof(g_ExeExts) / sizeof(g_ExeExts[0]); i++)
         if (ext.CompareNoCase(g_ExeExts[i]) == 0)
            return true;
      return false;
   }

#ifdef USE_86_FILTER

   static inline void GetMethodFull(uint64_t methodID, uint32_t numInStreams, CMethodFull &methodResult)
   {
      methodResult.Id = methodID;
      methodResult.NumInStreams = numInStreams;
      methodResult.NumOutStreams = 1;
   }

   static void MakeExeMethod(const CCompressionMethodMode &method,
      bool bcj2Filter, CCompressionMethodMode &exeMethod)
   {
      exeMethod = method;
      if (bcj2Filter)
      {
         CMethodFull methodFull;
         GetMethodFull(k_BCJ2, 4, methodFull);
         exeMethod.Methods.insert_at(0, new CMethodFull(methodFull));
         GetMethodFull(k_LZMA, 1, methodFull);
         methodFull.Props[NCoderPropID::kAlgorithm] = (int64_t)kAlgorithmForBCJ2_LZMA;
         methodFull.Props[NCoderPropID::kMatchFinder] = (int64_t)kMatchFinderForBCJ2_LZMA;
         methodFull.Props[NCoderPropID::kDictionarySize] = (int64_t)kDictionaryForBCJ2_LZMA;
         methodFull.Props[NCoderPropID::kNumFastBytes] = (int64_t)kNumFastBytesForBCJ2_LZMA;
         methodFull.Props[NCoderPropID::kNumThreads] = (int64_t)1;

         exeMethod.Methods.add(new CMethodFull(methodFull));
         exeMethod.Methods.add(new CMethodFull(methodFull));
         CBind bind;

         bind.OutCoder = 0;
         bind.InStream = 0;

         bind.InCoder = 1;
         bind.OutStream = 0;
         exeMethod.Binds.add(bind);

         bind.InCoder = 2;
         bind.OutStream = 1;
         exeMethod.Binds.add(bind);

         bind.InCoder = 3;
         bind.OutStream = 2;
         exeMethod.Binds.add(bind);
      }
      else
      {
         CMethodFull methodFull;
         GetMethodFull(k_BCJ, 1, methodFull);
         exeMethod.Methods.insert_at(0, new CMethodFull(methodFull));
         CBind bind;
         bind.OutCoder = 0;
         bind.InStream = 0;
         bind.InCoder = 1;
         bind.OutStream = 0;
         exeMethod.Binds.add(bind);
      }
   }

#endif

   static void FromUpdateItemToFileItem(const CUpdateItem &ui,
      CFileItem &file, CFileItem2 &file2)
   {
      throw "implement below";
      /*file.Name = NItemName::MakeLegalName(ui.Name);*/
      if (ui.AttribDefined)
         file.SetAttrib(ui.Attrib);

      file2.CTime = ui.CTime;  file2.CTimeDefined = ui.CTimeDefined;
      file2.ATime = ui.ATime;  file2.ATimeDefined = ui.ATimeDefined;
      file2.MTime = ui.MTime;  file2.MTimeDefined = ui.MTimeDefined;
      file2.IsAnti = ui.IsAnti;
      file2.StartPosDefined = false;

      file.get_count = ui.get_count;
      file.IsDir = ui.IsDir;
      file.HasStream = ui.HasStream();
   }

   class CFolderOutStream2:
      public ::file::writer
   {
      ::libcompress::writer_with_crc *_crcStreamSpec;
      smart_pointer < ::file::writer > _crcStream;
      const CArchiveDatabaseEx *_db;
      const bool_array *_extractStatuses;
      smart_pointer < ::file::writer > _outStream;
      uint32_t _startIndex;
      int32_t _currentIndex;
      bool _fileIsOpen;
      uint64_t _rem;

      void OpenFile();
      void CloseFile();
      HRESULT CloseFileAndSetResult();
      HRESULT ProcessEmptyFiles();
   public:
      //MY_UNKNOWN_IMP

         CFolderOutStream2()
      {
         _crcStreamSpec = new ::libcompress::writer_with_crc;
         _crcStream = _crcStreamSpec;
      }

      HRESULT Init(const CArchiveDatabaseEx *db, uint32_t startIndex, const bool_array *extractStatuses, ::file::writer *outStream);
      void ReleaseOutStream();
      HRESULT CheckFinishedState() const { return (_currentIndex == _extractStatuses->get_count()) ? S_OK: E_FAIL; }

      void write(const void *data, ::primitive::memory_size size, ::primitive::memory_size *processedSize);
   };

   HRESULT CFolderOutStream2::Init(const CArchiveDatabaseEx *db, uint32_t startIndex,
      const bool_array *extractStatuses, ::file::writer *outStream)
   {
      _db = db;
      _startIndex = startIndex;
      _extractStatuses = extractStatuses;
      _outStream = outStream;

      _currentIndex = 0;
      _fileIsOpen = false;
      return ProcessEmptyFiles();
   }

   void CFolderOutStream2::ReleaseOutStream()
   {
      ::release(_outStream.m_p);
      _crcStreamSpec->ReleaseStream();
   }

   void CFolderOutStream2::OpenFile()
   {
      _crcStreamSpec->SetStream((*_extractStatuses)[_currentIndex] ? _outStream.m_p : NULL);
      _crcStreamSpec->Init(true);
      _fileIsOpen = true;
      _rem = _db->Files[_startIndex + _currentIndex].get_count;
   }

   void CFolderOutStream2::CloseFile()
   {
      _crcStreamSpec->ReleaseStream();
      _fileIsOpen = false;
      _currentIndex++;
   }

   HRESULT CFolderOutStream2::CloseFileAndSetResult()
   {
      const CFileItem &file = _db->Files[_startIndex + _currentIndex];
      CloseFile();
      return (file.IsDir || !file.CrcDefined || file.Crc == _crcStreamSpec->GetCRC()) ? S_OK: S_FALSE;
   }

   HRESULT CFolderOutStream2::ProcessEmptyFiles()
   {
      while (_currentIndex < _extractStatuses->get_count() && _db->Files[_startIndex + _currentIndex].get_count == 0)
      {
         OpenFile();
         RINOK(CloseFileAndSetResult());
      }
      return S_OK;
   }

   void CFolderOutStream2::write(const void *data, ::primitive::memory_size size, ::primitive::memory_size *processedSize)
   {
      HRESULT hr;
      if (processedSize != NULL)
         *processedSize = 0;
      while (size != 0)
      {
         if (_fileIsOpen)
         {
            ::primitive::memory_size cur = size < _rem ? size : (uint32_t)_rem;
            _crcStream->write(data, cur, &cur);
            if (cur == 0)
               break;
            data = (const byte *)data + cur;
            size -= cur;
            _rem -= cur;
            if (processedSize != NULL)
               *processedSize += cur;
            if (_rem == 0)
            {
               if(FAILED(hr = CloseFileAndSetResult()))
                  throw hr;
               if(FAILED(hr = ProcessEmptyFiles()))
                  throw hr;
               continue;
            }
         }
         else
         {
            if(FAILED(hr = (ProcessEmptyFiles())))
               throw hr;
            if (_currentIndex == _extractStatuses->get_count())
            {
               // we don't support partial extracting
               throw E_FAIL;
            }
            OpenFile();
         }
      }
   }

   class CThreadDecoder: public thread
   {
   public:
      HRESULT Result;
      smart_pointer < ::file::input_stream > InStream;

      CFolderOutStream2 *FosSpec;
      smart_pointer < ::file::writer > Fos;

      uint64_t StartPos;
      const file_size *PackSizes;
      const CFolder *Folder;
#ifndef _NO_CRYPTO
      smart_pointer < ::crypto::get_text_password_interface > GetTextPassword;
#endif

      ///DECL_EXTERNAL_CODECS_VARS
      ::libcompress::codecs_info_interface * _codecsInfo;
      array < ::libcompress::codec_info_ex > _externalCodecs;
         CDecoder Decoder;

#ifndef _7ZIP_ST
      bool MtMode;
      uint32_t NumThreads;
#endif

      CThreadDecoder(sp(::base::application) papp):
      element(papp),
      thread(papp),
      Decoder(papp, true)
      {
#ifndef _7ZIP_ST
         MtMode = false;
         NumThreads = 1;
#endif
         FosSpec = new CFolderOutStream2;
         Fos = FosSpec;
         Result = E_FAIL;
      }
      virtual void Execute();
   };

   void CThreadDecoder::Execute()
   {
      try
      {
#ifndef _NO_CRYPTO
         bool passwordIsDefined;
#endif
         Result = Decoder.Decode(
            _codecsInfo, &_externalCodecs,
            InStream,
            StartPos,
            PackSizes,
            *Folder,
            Fos,
            NULL
#ifndef _NO_CRYPTO
            , GetTextPassword, passwordIsDefined
#endif
#ifndef _7ZIP_ST
            , MtMode, NumThreads
#endif
            );
      }
      catch(...)
      {
         Result = E_FAIL;
      }
      if (Result == S_OK)
         Result = FosSpec->CheckFinishedState();
      FosSpec->ReleaseOutStream();
   }

   bool static Is86FilteredFolder(const CFolder &f)
   {
      for (int32_t i = 0; i < f.Coders.get_count(); i++)
      {
         ::libcompress::method_id m = f.Coders[i].MethodID;
         if (m == k_BCJ || m == k_BCJ2)
            return true;
      }
      return false;
   }

#ifndef _NO_CRYPTO

   class CCryptoGetTextPassword:
      public ::crypto::get_text_password_interface
   {
   public:
      string Password;

      //MY_UNKNOWN_IMP
         HRes CryptoGetTextPassword(string & password);
   };

   HRes CCryptoGetTextPassword::CryptoGetTextPassword(string & password)
   {
      password = Password;
      return S_OK;
   }

#endif

   static const int32_t kNumGroupsMax = 4;

#ifdef USE_86_FILTER
   static bool Is86Group(int32_t group) { return (group & 1) != 0; }
#endif
   static bool IsEncryptedGroup(int32_t group) { return (group & 2) != 0; }
   static int32_t GetGroupIndex(bool encrypted, int32_t bcjFiltered)
   { return (encrypted ? 2 : 0) + (bcjFiltered ? 1 : 0); }

   HRESULT Update(
      ::libcompress::codecs_info_interface * codecsInfo,
      const array < ::libcompress::codec_info_ex > * externalCodecs,
      ::file::input_stream * inStream,
      const CArchiveDatabaseEx * db,
      const smart_pointer_array < CUpdateItem > & updateItems,
      COutArchive & archive,
      CArchiveDatabase & newDatabase,
      ::file::writer * seqOutStream,
      ::libcompress::archive_update_callback_interface * updateCallback,
      const CUpdateOptions & options
#ifndef _NO_CRYPTO
      , ::crypto::get_text_password_interface * getDecoderPassword
#endif
      )
   {
      uint64_t numSolidFiles = options.NumSolidFiles;
      if (numSolidFiles == 0)
         numSolidFiles = 1;
      /*
      smart_pointer<::file::output_stream> outStream;
      RINOK(seqOutStream->QueryInterface(IID_IOutStream, (void **)&outStream));
      if (!outStream)
      return E_NOTIMPL;
      */

      uint64_t startBlockSize = db != 0 ? db->ArchiveInfo.StartPosition: 0;
      if (startBlockSize > 0 && !options.RemoveSfxBlock)
      {
         RINOK(WriteRange(inStream, seqOutStream, 0, startBlockSize, NULL));
      }

      array<int32_t> fileIndexToUpdateIndexMap;
      array<CFolderRepack> folderRefs;
      uint64_t complexity = 0;
      uint64_t inSizeForReduce2 = 0;
      bool needEncryptedRepack = false;
      if (db != 0)
      {
         fileIndexToUpdateIndexMap.allocate(0, db->Files.get_count());
         int32_t i;
         for (i = 0; i < db->Files.get_count(); i++)
            fileIndexToUpdateIndexMap.add(-1);

         for (i = 0; i < updateItems.get_count(); i++)
         {
            int32_t index = updateItems[i].IndexInArchive;
            if (index != -1)
               fileIndexToUpdateIndexMap[index] = i;
         }

         for (i = 0; i < db->Folders.get_count(); i++)
         {
            CNum indexInFolder = 0;
            CNum numCopyItems = 0;
            CNum numUnpackStreams = db->NumUnpackStreamsVector[i];
            uint64_t repackSize = 0;
            for (CNum fi = db->FolderStartFileIndex[i]; indexInFolder < numUnpackStreams; fi++)
            {
               const CFileItem &file = db->Files[fi];
               if (file.HasStream)
               {
                  indexInFolder++;
                  int32_t updateIndex = fileIndexToUpdateIndexMap[fi];
                  if (updateIndex >= 0 && !updateItems[updateIndex].NewData)
                  {
                     numCopyItems++;
                     repackSize += file.get_count;
                  }
               }
            }

            if (numCopyItems == 0)
               continue;

            CFolderRepack rep;
            rep.FolderIndex = i;
            rep.NumCopyFiles = numCopyItems;
            const CFolder &f = db->Folders[i];
            bool isEncrypted = f.IsEncrypted();
            rep.Group = GetGroupIndex(isEncrypted, Is86FilteredFolder(f));
            folderRefs.add(rep);
            if (numCopyItems == numUnpackStreams)
               complexity += db->GetFolderFullPackSize(i);
            else
            {
               complexity += repackSize;
               if (repackSize > inSizeForReduce2)
                  inSizeForReduce2 = repackSize;
               if (isEncrypted)
                  needEncryptedRepack = true;
            }
         }
         throw "should implement below";
         //folderRefs.Sort(CompareFolderRepacks, (void *)db);
      }

      file_size inSizeForReduce = 0;
      int32_t i;
      for (i = 0; i < updateItems.get_count(); i++)
      {
         const CUpdateItem &ui = updateItems[i];
         if (ui.NewData)
         {
            complexity += ui.get_count;
            if (numSolidFiles != 1)
               inSizeForReduce += ui.get_count;
            else if (ui.get_count > inSizeForReduce)
               inSizeForReduce = ui.get_count;
         }
      }

      if (inSizeForReduce2 > inSizeForReduce)
         inSizeForReduce = inSizeForReduce2;

      const uint32_t kMinReduceSize = (1 << 16);
      if (inSizeForReduce < kMinReduceSize)
         inSizeForReduce = kMinReduceSize;

      RINOK(updateCallback->SetTotal(complexity));

      ::libcompress::local_progress *lps = new ::libcompress::local_progress;
      smart_pointer < ::libcompress::progress_info_interface > progress = lps;
      lps->Init(updateCallback, true);

      CThreadDecoder threadDecoder(inStream->get_app());
      if (!folderRefs.is_empty())
      {
#ifdef EXTERNAL_CODECS
         threadDecoder._codecsInfo = codecsInfo;
         threadDecoder._externalCodecs = *externalCodecs;
#endif
         throw "should check/implement below";
         //RINOK(threadDecoder.Create());
      }

      smart_pointer_array<CSolidGroup> groups;
      for (i = 0; i < kNumGroupsMax; i++)
         groups.add(new CSolidGroup());

      {
         // ---------- Split files to 2 groups ----------

         bool useFilters = options.UseFilters;

         const CCompressionMethodMode &method = *options.Method;

         if (method.Methods.get_count() != 1 || method.Binds.get_count() != 0)
            useFilters = false;

         for (i = 0; i < updateItems.get_count(); i++)
         {

            const CUpdateItem &ui = updateItems[i];

            if (!ui.NewData || !ui.HasStream())
               continue;

            bool filteredGroup = false;

            if (useFilters)
            {

               strsize dotPos = ui.Name.reverse_find(L'.');

               if (dotPos >= 0)
                  filteredGroup = IsExeExt(ui.Name.Mid(dotPos + 1));

            }

            groups[GetGroupIndex(method.PasswordIsDefined, filteredGroup)].Indices.add(i);

         }

      }

#ifndef _NO_CRYPTO

      CCryptoGetTextPassword *getPasswordSpec = NULL;
      if (needEncryptedRepack)
      {
         getPasswordSpec = new CCryptoGetTextPassword;
         threadDecoder.GetTextPassword = getPasswordSpec;

         if (options.Method->PasswordIsDefined)
            getPasswordSpec->Password = options.Method->Password;
         else
         {
            if (!getDecoderPassword)
               return E_NOTIMPL;
            string password;
            RINOK(getDecoderPassword->CryptoGetTextPassword(password));
            getPasswordSpec->Password = password;
         }
      }

#endif

      // ---------- Compress ----------

      RINOK(archive.Create(seqOutStream, false));
      RINOK(archive.SkipPrefixArchiveHeader());

      int32_t folderRefIndex = 0;
      lps->ProgressOffset = 0;

      for (int32_t groupIndex = 0; groupIndex < kNumGroupsMax; groupIndex++)
      {
         const CSolidGroup &group = groups[groupIndex];

         CCompressionMethodMode method;
#ifdef USE_86_FILTER
         if (Is86Group(groupIndex))
            MakeExeMethod(*options.Method, options.MaxFilter, method);
         else
#endif
            method = *options.Method;

         if (IsEncryptedGroup(groupIndex))
         {
            if (!method.PasswordIsDefined)
            {
#ifndef _NO_CRYPTO
               if (getPasswordSpec)
                  method.Password = getPasswordSpec->Password;
#endif
               method.PasswordIsDefined = true;
            }
         }
         else
         {
            method.PasswordIsDefined = false;
            method.Password.Empty();
         }

         CEncoder encoder(codecsInfo->get_app(), method);

         for (; folderRefIndex < folderRefs.get_count(); folderRefIndex++)
         {
            const CFolderRepack &rep = folderRefs[folderRefIndex];
            if (rep.Group != groupIndex)
               break;
            int32_t folderIndex = rep.FolderIndex;

            if (rep.NumCopyFiles == db->NumUnpackStreamsVector[folderIndex])
            {
               uint64_t packSize = db->GetFolderFullPackSize(folderIndex);
               RINOK(WriteRange(inStream, archive.SeqStream,
                  db->GetFolderStreamPos(folderIndex, 0), packSize, progress));
               lps->ProgressOffset += packSize;

               const CFolder &folder = db->Folders[folderIndex];
               CNum startIndex = db->FolderStartPackStreamIndex[folderIndex];
               for (int32_t j = 0; j < folder.PackStreams.get_count(); j++)
               {
                  newDatabase.PackSizes.add(db->PackSizes[startIndex + j]);
                  // newDatabase.PackCRCsDefined.add(db.PackCRCsDefined[startIndex + j]);
                  // newDatabase.PackCRCs.add(db.PackCRCs[startIndex + j]);
               }
               newDatabase.Folders.add(new CFolder(folder));
            }
            else
            {
               ::file::stream_binder sb(codecsInfo->get_app());
               RINOK(sb.CreateEvents());
               sp(::file::writer) sbOutStream;
               sp(::file::reader) sbInStream;
               sb.CreateStreams(sbInStream, sbOutStream);
               bool_array extractStatuses;

               CNum numUnpackStreams = db->NumUnpackStreamsVector[folderIndex];
               CNum indexInFolder = 0;

               for (CNum fi = db->FolderStartFileIndex[folderIndex]; indexInFolder < numUnpackStreams; fi++)
               {
                  bool needExtract = false;
                  if (db->Files[fi].HasStream)
                  {
                     indexInFolder++;
                     int32_t updateIndex = fileIndexToUpdateIndexMap[fi];
                     if (updateIndex >= 0 && !updateItems[updateIndex].NewData)
                        needExtract = true;
                  }
                  extractStatuses.add(needExtract);
               }

               RINOK(threadDecoder.FosSpec->Init(db, db->FolderStartFileIndex[folderIndex], &extractStatuses, sbOutStream));
               ::release(sbOutStream.m_p);

               threadDecoder.InStream = inStream;
               threadDecoder.Folder = db->Folders(folderIndex);
               threadDecoder.StartPos = db->GetFolderStreamPos(folderIndex, 0);
               threadDecoder.PackSizes = &db->PackSizes[db->FolderStartPackStreamIndex[folderIndex]];

               threadDecoder.begin();

               ::count startPackIndex = newDatabase.PackSizes.get_count();

               CFolder newFolder;

               RINOK(encoder.Encode(
                  codecsInfo, externalCodecs,
                  sbInStream, NULL, &inSizeForReduce, newFolder,
                  archive.SeqStream, newDatabase.PackSizes, progress));

               throw "should implement below";
//               threadDecoder.WaitFinish();

               RINOK(threadDecoder.Result);

               for (; startPackIndex < newDatabase.PackSizes.get_count(); startPackIndex++)
                  lps->OutSize += newDatabase.PackSizes[startPackIndex];
               lps->InSize += newFolder.GetUnpackSize();

               newDatabase.Folders.add(new CFolder(newFolder));
            }

            newDatabase.NumUnpackStreamsVector.add(rep.NumCopyFiles);

            CNum numUnpackStreams = db->NumUnpackStreamsVector[folderIndex];

            CNum indexInFolder = 0;
            for (CNum fi = db->FolderStartFileIndex[folderIndex]; indexInFolder < numUnpackStreams; fi++)
            {
               CFileItem file;
               CFileItem2 file2;
               db->GetFile(fi, file, file2);
               if (file.HasStream)
               {
                  indexInFolder++;
                  int32_t updateIndex = fileIndexToUpdateIndexMap[fi];
                  if (updateIndex >= 0)
                  {
                     const CUpdateItem &ui = updateItems[updateIndex];
                     if (ui.NewData)
                        continue;
                     if (ui.NewProps)
                     {
                        CFileItem uf;
                        FromUpdateItemToFileItem(ui, uf, file2);
                        uf.get_count = file.get_count;
                        uf.Crc = file.Crc;
                        uf.CrcDefined = file.CrcDefined;
                        uf.HasStream = file.HasStream;
                        file = uf;
                     }
                     newDatabase.AddFile(file, file2);
                  }
               }
            }
         }

         ::count numFiles = group.Indices.get_count();
         if (numFiles == 0)
            continue;
         smart_pointer_array<CRefItem> refItems;
         //refItems.set_size(0, numFiles);
         bool sortByType = (numSolidFiles > 1);
         for (i = 0; i < numFiles; i++)
            refItems.add(new CRefItem(group.Indices[i], updateItems[group.Indices[i]], sortByType));
         throw "should implement below";
         //refItems.Sort(CompareUpdateItems, (void *)&sortByType);

         array<uint32_t> indices;
         indices.allocate(0, numFiles);

         for (i = 0; i < numFiles; i++)
         {
            ::index index = refItems[i].Index;
            indices.add((const uint32_t) index);
            /*
            const CUpdateItem &ui = updateItems[index];
            CFileItem file;
            if (ui.NewProps)
            FromUpdateItemToFileItem(ui, file);
            else
            file = db.Files[ui.IndexInArchive];
            if (file.IsAnti || file.IsDir)
            return E_FAIL;
            newDatabase.Files.add(file);
            */
         }

         for (i = 0; i < numFiles;)
         {
            uint64_t totalSize = 0;
            int32_t numSubFiles;
            string prevExtension;
            for (numSubFiles = 0; i + numSubFiles < numFiles &&
               numSubFiles < numSolidFiles; numSubFiles++)
            {
               const CUpdateItem &ui = updateItems[indices[i + numSubFiles]];
               totalSize += ui.get_count;
               if (totalSize > options.NumSolidBytes)
                  break;
               if (options.SolidExtension)
               {
                  string ext = ui.GetExtension();
                  if (numSubFiles == 0)
                     prevExtension = ext;
                  else
                     if (ext.CompareNoCase(prevExtension) != 0)
                        break;
               }
            }
            if (numSubFiles < 1)
               numSubFiles = 1;

            CFolderInStream *inStreamSpec = new CFolderInStream;
            smart_pointer < ::file::reader > solidInStream(inStreamSpec);
            inStreamSpec->Init(updateCallback, &indices[i], numSubFiles);

            CFolder folderItem;

            ::count startPackIndex = newDatabase.PackSizes.get_count();
            RINOK(encoder.Encode(
               codecsInfo, externalCodecs,
               solidInStream, NULL, &inSizeForReduce, folderItem,
               archive.SeqStream, newDatabase.PackSizes, progress));

            for (; startPackIndex < newDatabase.PackSizes.get_count(); startPackIndex++)
               lps->OutSize += newDatabase.PackSizes[startPackIndex];

            lps->InSize += folderItem.GetUnpackSize();
            // for ()
            // newDatabase.PackCRCsDefined.add(false);
            // newDatabase.PackCRCs.add(0);

            newDatabase.Folders.add(new CFolder(folderItem));

            CNum numUnpackStreams = 0;
            for (int32_t subIndex = 0; subIndex < numSubFiles; subIndex++)
            {
               const CUpdateItem &ui = updateItems[indices[i + subIndex]];
               CFileItem file;
               CFileItem2 file2;
               if (ui.NewProps)
                  FromUpdateItemToFileItem(ui, file, file2);
               else
                  db->GetFile(ui.IndexInArchive, file, file2);
               if (file2.IsAnti || file.IsDir)
                  return E_FAIL;

               /*
               CFileItem &file = newDatabase.Files[
               startFileIndexInDatabase + i + subIndex];
               */
               if (!inStreamSpec->Processed[subIndex])
               {
                  continue;
                  // file.Name += L".locked";
               }

               file.Crc = inStreamSpec->CRCs[subIndex];
               file.get_count = inStreamSpec->Sizes[subIndex];
               if (file.get_count != 0)
               {
                  file.CrcDefined = true;
                  file.HasStream = true;
                  numUnpackStreams++;
               }
               else
               {
                  file.CrcDefined = false;
                  file.HasStream = false;
               }
               newDatabase.AddFile(file, file2);
            }
            // numUnpackStreams = 0 is very bad case for locked files
            // v3.13 doesn't understand it.
            newDatabase.NumUnpackStreamsVector.add(numUnpackStreams);
            i += numSubFiles;
         }
      }

      if (folderRefIndex != folderRefs.get_count())
         return E_FAIL;

      /*
      folderRefs.ClearAndFree();
      fileIndexToUpdateIndexMap.ClearAndFree();
      groups.ClearAndFree();
      */

      {
         // ---------- Write Folders & Empty Files ----------

         array<int32_t> emptyRefs;
         for (i = 0; i < updateItems.get_count(); i++)
         {
            const CUpdateItem &ui = updateItems[i];
            if (ui.NewData)
            {
               if (ui.HasStream())
                  continue;
            }
            else if (ui.IndexInArchive != -1 && db->Files[ui.IndexInArchive].HasStream)
               continue;
            emptyRefs.add(i);
         }
         throw "should implement below";
         //emptyRefs.Sort(CompareEmptyItems, (void *)&updateItems);
         for (i = 0; i < emptyRefs.get_count(); i++)
         {
            const CUpdateItem &ui = updateItems[emptyRefs[i]];
            CFileItem file;
            CFileItem2 file2;
            if (ui.NewProps)
               FromUpdateItemToFileItem(ui, file, file2);
            else
               db->GetFile(ui.IndexInArchive, file, file2);
            newDatabase.AddFile(file, file2);
         }
      }
      throw "should implement below";
      //newDatabase.ReserveDown();
      return S_OK;
   }

} // namespace n7z

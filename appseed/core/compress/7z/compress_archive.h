// archive_.h
// from 7-zip
#pragma once
/*#define __IARCHIVE_H

#include "../IProgress.h"
#include "../IStream.h"
#include "../PropID.h"

*/

struct stat_prop_stg
{
   void *         m_p;
   int32_t            propid;
   var::e_type    vt;
};


namespace libcompress
{

   namespace NFileTimeType
   {
     enum EEnum
     {
       kWindows,
       kUnix,
       kDOS
     };
   }

   namespace archive
   {
     enum
     {
       kName = 0,
       kClassID,
       kExtension,
       kAddExtension,
       kUpdate,
       kKeepName,
       kStartSignature,
       kFinishSignature,
       kAssociate
     };

     namespace extract
     {

       enum e_ask_mode
       {
         ask_mode_extract = 0,
         ask_mode_test,
         ask_mode_skip
       };

       enum e_operation_result
       {
         operation_result_ok = 0,
         operation_result_UnSupportedMethod,
         operation_result_DataError,
         operation_result_CRCError
       };

     }
     namespace NUpdate
     {
       namespace NOperationResult
       {
         enum
         {
           kOK = 0,
           kError
         };
       }
     }
   }

   #define CA2_COMPRESS_INTERFACE_archive_OpenCallback(specifier) \
     virtual ::ca::HRes SetTotal(const uint64 *files, const uint64 *bytes) specifier; \
     virtual ::ca::HRes SetCompleted(const uint64 *files, const uint64 *bytes) specifier; \

   class CLASS_DECL_CORE archive_open_callback_interface :
      virtual public ::ca::object
   {
   public:
     CA2_COMPRESS_INTERFACE_archive_OpenCallback(= 0);
   };


   #define CA2_COMPRESS_INTERFACE_archive_ExtractCallback(specifier) \
     CA2_EX1_progress_interface(specifier) \
     virtual ::ca::HRes GetStream(uint32 index, ::ca::writer **outStream,  int32 askExtractMode) specifier; \
     virtual ::ca::HRes PrepareOperation(int32 askExtractMode) specifier; \
     virtual ::ca::HRes SetOperationResult(int32 resultEOperationResult) specifier; \

   class CLASS_DECL_CORE archive_extract_callback_interface :
      virtual public ::ca::progress_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_ExtractCallback(= 0)
   };

//virtual ::ca::HRes GetStream(const char * name, ::ca::byte_input_stream **inStream) specifier; \ // input stream should be seekable, so by the time using ::ca::file interface
   #define CA2_COMPRESS_INTERFACE_archive_OpenVolumeCallback(specifier) \
     virtual ::ca::HRes GetProperty(int32_t propID, var *value) specifier; \
     virtual ::ca::HRes GetStream(const char * name, ::ca::byte_input_stream **inStream) specifier; \

   class CLASS_DECL_CORE archive_open_volume_callback_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_OpenVolumeCallback(= 0);
   };


   class CLASS_DECL_CORE input_archive_get_stream_interface
   {
   public:
      virtual ::ca::HRes GetStream(uint32 index, ::ca::byte_input_stream **stream) = 0;
   };


   class CLASS_DECL_CORE input_archive_open_set_sub_archive_name_interface
   {
   public:
     virtual ::ca::HRes SetSubArchiveName(const char *name) = 0;
   };


   /*
   IInArchive::Extract:
     indices must be sorted
     numItems = 0xFFFFFFFF means "all files"
     testMode != 0 means "test files without writing to outStream"
   */

     //virtual ::ca::HRes Open(::ca::byte_input_stream * stream, const uint64 *maxCheckStartPosition, ::libcompress::archive_open_callback_interface *openArchiveCallback) specifier; \ // input stream should be seekable, so by the time using ::ca::file interface
   #define CA2_COMPRESS_INTERFACE_input_archive(specifier) \
     virtual ::ca::HRes Open(::ca::byte_input_stream * stream, const file_position_t *maxCheckStartPosition, ::libcompress::archive_open_callback_interface *openArchiveCallback) specifier; \
     virtual ::ca::HRes Close() specifier; \
     virtual ::ca::HRes GetNumberOfItems(uint32 *numItems) specifier; \
     virtual ::ca::HRes GetProperty(uint32 index, int32_t propID, var *value) specifier; \
     virtual ::ca::HRes Extract(const uint32* indices, uint32 numItems, int32 testMode, ::libcompress::archive_extract_callback_interface *extractCallback) specifier; \
     virtual ::ca::HRes GetArchiveProperty(int32_t propID, var *value) specifier; \
     virtual ::ca::HRes GetNumberOfProperties(uint32 *numProperties) specifier; \
     virtual ::ca::HRes GetPropertyInfo(uint32 index, string & name, int32_t *propID, var::e_type *varType) specifier; \
     virtual ::ca::HRes GetNumberOfArchiveProperties(uint32 *numProperties) specifier; \
     virtual ::ca::HRes GetArchivePropertyInfo(uint32 index, string & name, int32_t *propID, var::e_type *varType) specifier;

   class CLASS_DECL_CORE input_archive_interface :
      virtual public ::ca::object
   {
   public:
      CA2_COMPRESS_INTERFACE_input_archive(= 0)
   };

   class CLASS_DECL_CORE archive_open_input_stream :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes open_input_stream(::ca::byte_input_stream *stream) = 0;
   };

   #define CA2_COMPRESS_INTERFACE_archive_update_callback(specifier) \
     CA2_EX1_progress_interface(specifier); \
     virtual ::ca::HRes GetUpdateItemInfo(uint32 index,  \
         int32 *newData, /*1 - new data, 0 - old data */ \
         int32 *newProperties, /* 1 - new properties, 0 - old properties */ \
         uint32 *indexInArchive /* -1 if there is no in archive, or if doesn't matter */ \
         )  specifier; \
     virtual ::ca::HRes GetProperty(uint32 index, int32_t propID, var *value) specifier; \
     virtual ::ca::HRes GetStream(uint32 index, ::ca::byte_input_stream **inStream) specifier; \
     virtual ::ca::HRes SetOperationResult(int32 operationResult) specifier; \

   class CLASS_DECL_CORE archive_update_callback_interface :
      virtual public ::ca::progress_interface
   {
   public:
     CA2_COMPRESS_INTERFACE_archive_update_callback(= 0);
   };

   #define CA2_COMPRESS_INTERFACE_archive_update_callback2(specifier) \
     CA2_COMPRESS_INTERFACE_archive_update_callback(specifier) \
     virtual ::ca::HRes GetVolumeSize(uint32 index, uint64 *size) specifier; \
     virtual ::ca::HRes GetVolumeStream(uint32 index, ::ca::byte_output_stream **volumeStream) specifier; \

   class CLASS_DECL_CORE archive_update_callback2_interface :
      virtual public archive_update_callback_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_update_callback2(= 0);
   };


   #define CA2_COMPRESS_INTERFACE_IOutArchive(specifier) \
     virtual ::ca::HRes UpdateItems(::ca::writer *outStream, uint32 numItems, ::libcompress::archive_update_callback_interface *updateCallback) specifier; \
     virtual ::ca::HRes GetFileTimeType(uint32 *type) specifier;

   class CLASS_DECL_CORE output_archive_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_IOutArchive(= 0)
   };


   class CLASS_DECL_CORE set_properties_interface
   {
   public:
      virtual ::ca::HRes SetProperties(const char **names, const var *values, int32 numProperties) PURE;
   };


   #define IMP_IInArchive_GetProp(k) \
     (uint32 index, string & name, int32_t *propID, var::e_type *varType) \
       { if(index >= sizeof(k) / sizeof(k[0])) return E_INVALIDARG; \
       const stat_prop_stg &srcItem = k[index]; \
       *propID = srcItem.propid; *varType = srcItem.vt; name.Empty(); return S_OK; } \

   #define IMP_IInArchive_GetProp_WITH_NAME(k) \
     (uint32 index, string & name, PROPID *propID, VARTYPE *varType) \
       { if(index >= sizeof(k) / sizeof(k[0])) return E_INVALIDARG; \
       const STATPROPSTG &srcItem = k[index]; \
       *propID = srcItem.propid; *varType = srcItem.vt; \
       if (srcItem.lpwstrName == 0) name.Empty(); else name = ::ca::international::unicode_to_utf8(srcItem.lpwstrName); return S_OK; } \

   #define IMP_IInArchive_Props \
     ::ca::HRes handler::GetNumberOfProperties(uint32 *numProperties) \
       { *numProperties = sizeof(kProps) / sizeof(kProps[0]); return S_OK; } \
     ::ca::HRes handler::GetPropertyInfo IMP_IInArchive_GetProp(kProps)

   #define IMP_IInArchive_Props_WITH_NAME \
     ::ca::HRes CHandler::GetNumberOfProperties(uint32 *numProperties) \
       { *numProperties = sizeof(kProps) / sizeof(kProps[0]); return S_OK; } \
     ::ca::HRes CHandler::GetPropertyInfo IMP_IInArchive_GetProp_WITH_NAME(kProps)


   #define IMP_IInArchive_ArcProps \
     ::ca::HRes handler::GetNumberOfArchiveProperties(uint32 *numProperties) \
       { *numProperties = sizeof(kArcProps) / sizeof(kArcProps[0]); return S_OK; } \
     ::ca::HRes handler::GetArchivePropertyInfo IMP_IInArchive_GetProp(kArcProps)

   #define IMP_IInArchive_ArcProps_WITH_NAME \
     ::ca::HRes CHandler::GetNumberOfArchiveProperties(uint32 *numProperties) \
       { *numProperties = sizeof(kArcProps) / sizeof(kArcProps[0]); return S_OK; } \
     ::ca::HRes CHandler::GetArchivePropertyInfo IMP_IInArchive_GetProp_WITH_NAME(kArcProps)

   #define IMP_IInArchive_ArcProps_NO_Table \
     ::ca::HRes CHandler::GetNumberOfArchiveProperties(uint32 *numProperties) \
       { *numProperties = 0; return S_OK; } \
     ::ca::HRes CHandler::GetArchivePropertyInfo(uint32, string &, int32_t *, var::e_type *) \
       { return E_NOTIMPL; } \

   #define IMP_IInArchive_ArcProps_NO \
     IMP_IInArchive_ArcProps_NO_Table \
     ::ca::HRes CHandler::GetArchiveProperty(PROPID, var *value) \
       { value->vt = VT_EMPTY; return S_OK; }

} // namespace libcompress

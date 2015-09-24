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
     virtual HRes SetTotal(const uint64_t *files, const uint64_t *bytes) specifier; \
     virtual HRes SetCompleted(const uint64_t *files, const uint64_t *bytes) specifier; \

   class CLASS_DECL_CORE archive_open_callback_interface :
      virtual public ::object
   {
   public:
     CA2_COMPRESS_INTERFACE_archive_OpenCallback(= 0);
   };


   #define CA2_COMPRESS_INTERFACE_archive_ExtractCallback(specifier) \
     CA2_EX1_progress_interface(specifier) \
     virtual HRes GetStream(uint32_t index, ::file::writer **outStream,  int32_t askExtractMode) specifier; \
     virtual HRes PrepareOperation(int32_t askExtractMode) specifier; \
     virtual HRes SetOperationResult(int32_t resultEOperationResult) specifier; \

   class CLASS_DECL_CORE archive_extract_callback_interface :
      virtual public ::core::progress_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_ExtractCallback(= 0)
   };

//virtual HRes GetStream(const char * name, ::file::input_stream **inStream) specifier; \ // input stream should be seekable, so by the time using ::file::binary_buffer interface
   #define CA2_COMPRESS_INTERFACE_archive_OpenVolumeCallback(specifier) \
     virtual HRes GetProperty(int32_t propID, var *value) specifier; \
     virtual HRes GetStream(const char * name, ::file::input_stream **inStream) specifier; \

   class CLASS_DECL_CORE archive_open_volume_callback_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_OpenVolumeCallback(= 0);
   };


   class CLASS_DECL_CORE input_archive_get_stream_interface
   {
   public:
      virtual HRes GetStream(uint32_t index, ::file::input_stream **stream) = 0;
   };


   class CLASS_DECL_CORE input_archive_open_set_sub_archive_name_interface
   {
   public:
     virtual HRes SetSubArchiveName(const char *name) = 0;
   };


   /*
   IInArchive::Extract:
     indices must be sorted
     numItems = 0xFFFFFFFF means "all files"
     testMode != 0 means "test files without writing to outStream"
   */

     //virtual HRes Open(::file::input_stream * stream, const uint64_t *maxCheckStartPosition, ::libcompress::archive_open_callback_interface *openArchiveCallback) specifier; \ // input stream should be seekable, so by the time using ::file::binary_buffer interface
   #define CA2_COMPRESS_INTERFACE_input_archive(specifier) \
     virtual HRes Open(::file::input_stream * stream, const file_position_t *maxCheckStartPosition, ::libcompress::archive_open_callback_interface *openArchiveCallback) specifier; \
     virtual HRes Close() specifier; \
     virtual HRes GetNumberOfItems(uint32_t *numItems) specifier; \
     virtual HRes GetProperty(uint32_t index, int32_t propID, var *value) specifier; \
     virtual HRes Extract(const uint32_t* indices, uint32_t numItems, int32_t testMode, ::libcompress::archive_extract_callback_interface *extractCallback) specifier; \
     virtual HRes GetArchiveProperty(int32_t propID, var *value) specifier; \
     virtual HRes GetNumberOfProperties(uint32_t *numProperties) specifier; \
     virtual HRes GetPropertyInfo(uint32_t index, string & name, int32_t *propID, var::e_type *varType) specifier; \
     virtual HRes GetNumberOfArchiveProperties(uint32_t *numProperties) specifier; \
     virtual HRes GetArchivePropertyInfo(uint32_t index, string & name, int32_t *propID, var::e_type *varType) specifier;

   class CLASS_DECL_CORE input_archive_interface :
      virtual public ::object
   {
   public:
      CA2_COMPRESS_INTERFACE_input_archive(= 0)
   };

   class CLASS_DECL_CORE archive_open_input_stream :
      virtual public ::object
   {
   public:
      virtual HRes open_input_stream(::file::input_stream *stream) = 0;
   };

   #define CA2_COMPRESS_INTERFACE_archive_update_callback(specifier) \
     CA2_EX1_progress_interface(specifier); \
     virtual HRes GetUpdateItemInfo(uint32_t index,  \
         int32_t *newData, /*1 - new data, 0 - old data */ \
         int32_t *newProperties, /* 1 - new properties, 0 - old properties */ \
         uint32_t *indexInArchive /* -1 if there is no in archive, or if doesn't matter */ \
         )  specifier; \
     virtual HRes GetProperty(uint32_t index, int32_t propID, var *value) specifier; \
     virtual HRes GetStream(uint32_t index, ::file::input_stream **inStream) specifier; \
     virtual HRes SetOperationResult(int32_t operationResult) specifier; \

   class CLASS_DECL_CORE archive_update_callback_interface :
      virtual public ::core::progress_interface
   {
   public:
     CA2_COMPRESS_INTERFACE_archive_update_callback(= 0);
   };

   #define CA2_COMPRESS_INTERFACE_archive_update_callback2(specifier) \
     CA2_COMPRESS_INTERFACE_archive_update_callback(specifier) \
     virtual HRes GetVolumeSize(uint32_t index, uint64_t *size) specifier; \
     virtual HRes GetVolumeStream(uint32_t index, ::file::output_stream **volumeStream) specifier; \

   class CLASS_DECL_CORE archive_update_callback2_interface :
      virtual public archive_update_callback_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_update_callback2(= 0);
   };


   #define CA2_COMPRESS_INTERFACE_IOutArchive(specifier) \
     virtual HRes UpdateItems(::file::writer *outStream, uint32_t numItems, ::libcompress::archive_update_callback_interface *updateCallback) specifier; \
     virtual HRes GetFileTimeType(uint32_t *type) specifier;

   class CLASS_DECL_CORE output_archive_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_IOutArchive(= 0)
   };


   class CLASS_DECL_CORE set_properties_interface
   {
   public:
      virtual HRes SetProperties(const char **names, const var *values, int32_t numProperties) PURE;
   };


   #define IMP_IInArchive_GetProp(k) \
     (uint32_t index, string & name, int32_t *propID, var::e_type *varType) \
       { if(index >= sizeof(k) / sizeof(k[0])) return E_INVALIDARG; \
       const stat_prop_stg &srcItem = k[index]; \
       *propID = srcItem.propid; *varType = srcItem.vt; name.Empty(); return S_OK; } \

   #define IMP_IInArchive_GetProp_WITH_NAME(k) \
     (uint32_t index, string & name, PROPID *propID, VARTYPE *varType) \
       { if(index >= sizeof(k) / sizeof(k[0])) return E_INVALIDARG; \
       const STATPROPSTG &srcItem = k[index]; \
       *propID = srcItem.propid; *varType = srcItem.vt; \
       if (srcItem.lpwstrName == 0) name.Empty(); else name = ::str::international::unicode_to_utf8(srcItem.lpwstrName); return S_OK; } \

   #define IMP_IInArchive_Props \
     HRes handler::GetNumberOfProperties(uint32_t *numProperties) \
       { *numProperties = sizeof(kProps) / sizeof(kProps[0]); return S_OK; } \
     HRes handler::GetPropertyInfo IMP_IInArchive_GetProp(kProps)

   #define IMP_IInArchive_Props_WITH_NAME \
     HRes CHandler::GetNumberOfProperties(uint32_t *numProperties) \
       { *numProperties = sizeof(kProps) / sizeof(kProps[0]); return S_OK; } \
     HRes CHandler::GetPropertyInfo IMP_IInArchive_GetProp_WITH_NAME(kProps)


   #define IMP_IInArchive_ArcProps \
     HRes handler::GetNumberOfArchiveProperties(uint32_t *numProperties) \
       { *numProperties = sizeof(kArcProps) / sizeof(kArcProps[0]); return S_OK; } \
     HRes handler::GetArchivePropertyInfo IMP_IInArchive_GetProp(kArcProps)

   #define IMP_IInArchive_ArcProps_WITH_NAME \
     HRes CHandler::GetNumberOfArchiveProperties(uint32_t *numProperties) \
       { *numProperties = sizeof(kArcProps) / sizeof(kArcProps[0]); return S_OK; } \
     HRes CHandler::GetArchivePropertyInfo IMP_IInArchive_GetProp_WITH_NAME(kArcProps)

   #define IMP_IInArchive_ArcProps_NO_Table \
     HRes CHandler::GetNumberOfArchiveProperties(uint32_t *numProperties) \
       { *numProperties = 0; return S_OK; } \
     HRes CHandler::GetArchivePropertyInfo(uint32_t, string &, int32_t *, var::e_type *) \
       { return E_NOTIMPL; } \

   #define IMP_IInArchive_ArcProps_NO \
     IMP_IInArchive_ArcProps_NO_Table \
     HRes CHandler::GetArchiveProperty(PROPID, var *value) \
       { value->vt = VT_EMPTY; return S_OK; }

} // namespace libcompress

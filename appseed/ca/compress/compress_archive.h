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
     virtual gen::HRes SetTotal(const uint64_t *files, const uint64_t *bytes) specifier; \
     virtual gen::HRes SetCompleted(const uint64_t *files, const uint64_t *bytes) specifier; \

   class CLASS_DECL_ca archive_open_callback_interface :
      virtual public ::gen::object
   {
   public:
     CA2_COMPRESS_INTERFACE_archive_OpenCallback(= 0);
   };


   #define CA2_COMPRESS_INTERFACE_archive_ExtractCallback(specifier) \
     CA2_EX1_progress_interface(specifier) \
     virtual gen::HRes GetStream(uint32_t index, gen::writer **outStream,  int32_t askExtractMode) specifier; \
     virtual gen::HRes PrepareOperation(int32_t askExtractMode) specifier; \
     virtual gen::HRes SetOperationResult(int32_t resultEOperationResult) specifier; \

   class CLASS_DECL_ca archive_extract_callback_interface :
      virtual public gen::progress_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_ExtractCallback(= 0)
   };

//virtual gen::HRes GetStream(const char * name, gen::byte_input_stream **inStream) specifier; \ // input stream should be seekable, so by the time using gen::file interface
   #define CA2_COMPRESS_INTERFACE_archive_OpenVolumeCallback(specifier) \
     virtual gen::HRes GetProperty(int32_t propID, var *value) specifier; \
     virtual gen::HRes GetStream(const char * name, gen::byte_input_stream **inStream) specifier; \

   class CLASS_DECL_ca archive_open_volume_callback_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_OpenVolumeCallback(= 0);
   };


   class CLASS_DECL_ca input_archive_get_stream_interface
   {
   public:
      virtual gen::HRes GetStream(uint32_t index, gen::byte_input_stream **stream) = 0;
   };


   class CLASS_DECL_ca input_archive_open_set_sub_archive_name_interface
   {
   public:
     virtual gen::HRes SetSubArchiveName(const char *name) = 0;
   };


   /*
   IInArchive::Extract:
     indices must be sorted
     numItems = 0xFFFFFFFF means "all files"
     testMode != 0 means "test files without writing to outStream"
   */

     //virtual gen::HRes Open(::gen::byte_input_stream * stream, const uint64_t *maxCheckStartPosition, ::libcompress::archive_open_callback_interface *openArchiveCallback) specifier; \ // input stream should be seekable, so by the time using gen::file interface
   #define CA2_COMPRESS_INTERFACE_input_archive(specifier) \
     virtual gen::HRes Open(::gen::byte_input_stream * stream, const file_position *maxCheckStartPosition, ::libcompress::archive_open_callback_interface *openArchiveCallback) specifier; \
     virtual gen::HRes Close() specifier; \
     virtual gen::HRes GetNumberOfItems(uint32_t *numItems) specifier; \
     virtual gen::HRes GetProperty(uint32_t index, int32_t propID, var *value) specifier; \
     virtual gen::HRes Extract(const uint32_t* indices, uint32_t numItems, int32_t testMode, ::libcompress::archive_extract_callback_interface *extractCallback) specifier; \
     virtual gen::HRes GetArchiveProperty(int32_t propID, var *value) specifier; \
     virtual gen::HRes GetNumberOfProperties(uint32_t *numProperties) specifier; \
     virtual gen::HRes GetPropertyInfo(uint32_t index, string & name, int32_t *propID, var::e_type *varType) specifier; \
     virtual gen::HRes GetNumberOfArchiveProperties(uint32_t *numProperties) specifier; \
     virtual gen::HRes GetArchivePropertyInfo(uint32_t index, string & name, int32_t *propID, var::e_type *varType) specifier;

   class CLASS_DECL_ca input_archive_interface :
      virtual public ::gen::object
   {
   public:
      CA2_COMPRESS_INTERFACE_input_archive(= 0)
   };

   class CLASS_DECL_ca archive_open_input_stream :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes open_input_stream(gen::byte_input_stream *stream) = 0;
   };

   #define CA2_COMPRESS_INTERFACE_archive_update_callback(specifier) \
     CA2_EX1_progress_interface(specifier); \
     virtual gen::HRes GetUpdateItemInfo(uint32_t index,  \
         int32_t *newData, /*1 - new data, 0 - old data */ \
         int32_t *newProperties, /* 1 - new properties, 0 - old properties */ \
         uint32_t *indexInArchive /* -1 if there is no in archive, or if doesn't matter */ \
         )  specifier; \
     virtual gen::HRes GetProperty(uint32_t index, int32_t propID, var *value) specifier; \
     virtual gen::HRes GetStream(uint32_t index, gen::byte_input_stream **inStream) specifier; \
     virtual gen::HRes SetOperationResult(int32_t operationResult) specifier; \

   class CLASS_DECL_ca archive_update_callback_interface :
      virtual public gen::progress_interface
   {
   public:
     CA2_COMPRESS_INTERFACE_archive_update_callback(= 0);
   };

   #define CA2_COMPRESS_INTERFACE_archive_update_callback2(specifier) \
     CA2_COMPRESS_INTERFACE_archive_update_callback(specifier) \
     virtual gen::HRes GetVolumeSize(uint32_t index, uint64_t *size) specifier; \
     virtual gen::HRes GetVolumeStream(uint32_t index, gen::byte_output_stream **volumeStream) specifier; \

   class CLASS_DECL_ca archive_update_callback2_interface :
      virtual public archive_update_callback_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_archive_update_callback2(= 0);
   };


   #define CA2_COMPRESS_INTERFACE_IOutArchive(specifier) \
     virtual gen::HRes UpdateItems(gen::writer *outStream, uint32_t numItems, ::libcompress::archive_update_callback_interface *updateCallback) specifier; \
     virtual gen::HRes GetFileTimeType(uint32_t *type) specifier;

   class CLASS_DECL_ca output_archive_interface
   {
   public:
      CA2_COMPRESS_INTERFACE_IOutArchive(= 0)
   };


   class CLASS_DECL_ca set_properties_interface
   {
   public:
      virtual gen::HRes SetProperties(const char **names, const var *values, int32_t numProperties) PURE;
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
       if (srcItem.lpwstrName == 0) name.Empty(); else name = gen::international::unicode_to_utf8(srcItem.lpwstrName); return S_OK; } \

   #define IMP_IInArchive_Props \
     gen::HRes handler::GetNumberOfProperties(uint32_t *numProperties) \
       { *numProperties = sizeof(kProps) / sizeof(kProps[0]); return S_OK; } \
     gen::HRes handler::GetPropertyInfo IMP_IInArchive_GetProp(kProps)

   #define IMP_IInArchive_Props_WITH_NAME \
     gen::HRes CHandler::GetNumberOfProperties(uint32_t *numProperties) \
       { *numProperties = sizeof(kProps) / sizeof(kProps[0]); return S_OK; } \
     gen::HRes CHandler::GetPropertyInfo IMP_IInArchive_GetProp_WITH_NAME(kProps)


   #define IMP_IInArchive_ArcProps \
     gen::HRes handler::GetNumberOfArchiveProperties(uint32_t *numProperties) \
       { *numProperties = sizeof(kArcProps) / sizeof(kArcProps[0]); return S_OK; } \
     gen::HRes handler::GetArchivePropertyInfo IMP_IInArchive_GetProp(kArcProps)

   #define IMP_IInArchive_ArcProps_WITH_NAME \
     gen::HRes CHandler::GetNumberOfArchiveProperties(uint32_t *numProperties) \
       { *numProperties = sizeof(kArcProps) / sizeof(kArcProps[0]); return S_OK; } \
     gen::HRes CHandler::GetArchivePropertyInfo IMP_IInArchive_GetProp_WITH_NAME(kArcProps)

   #define IMP_IInArchive_ArcProps_NO_Table \
     gen::HRes CHandler::GetNumberOfArchiveProperties(uint32_t *numProperties) \
       { *numProperties = 0; return S_OK; } \
     gen::HRes CHandler::GetArchivePropertyInfo(uint32_t, string &, int32_t *, var::e_type *) \
       { return E_NOTIMPL; } \

   #define IMP_IInArchive_ArcProps_NO \
     IMP_IInArchive_ArcProps_NO_Table \
     gen::HRes CHandler::GetArchiveProperty(PROPID, var *value) \
       { value->vt = VT_EMPTY; return S_OK; }

} // namespace libcompress

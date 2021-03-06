#pragma once


CLASS_DECL_AURA memory file_as_memory_dup(const char * path);
CLASS_DECL_AURA memory_size_t file_as_memory_dup(const char * path, void * p, memory_size_t s);
CLASS_DECL_AURA string file_as_string_dup(const char * path);
CLASS_DECL_AURA string file_extension_dup(const char * path);
CLASS_DECL_AURA string get_temp_file_name_dup(const char * pszName,const char * pszExtension);
CLASS_DECL_AURA string file_final_extension_dup(const char * path);
CLASS_DECL_AURA string url_dir_name_for_relative(const char * pszPath);
CLASS_DECL_AURA string solve_relative_compressions(const string & str, bool * pbUrl = NULL);
CLASS_DECL_AURA bool solve_relative_compressions_inline(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize * iaSlash, int * piSlashCount); // returns true if original string had trailing slash
CLASS_DECL_AURA string defer_solve_relative_name(const char * pszRelative,const char * pszAbsolute);
CLASS_DECL_AURA string ca2_module_dup();
CLASS_DECL_AURA bool file_append_dup(const string & strFile, const string & str);
CLASS_DECL_AURA bool file_append_dup(const string & strFile, const char * psz, strsize s);
CLASS_DECL_AURA bool file_append_wait_dup(const string & strFile, const string & str, DWORD dwTimeout = INFINITE);
CLASS_DECL_AURA bool file_append_wait_dup(const string & strFile, const char * psz, strsize s, DWORD dwTimeout = INFINITE);



template < class POD >
inline bool file_put_pod(const char * path, const POD & pod)
{
   return file_put_contents_dup(path, &pod, sizeof(pod));
}



template < class POD >
inline bool file_as_pod(POD & pod, const char * path)
{
   return file_as_memory_dup(path, &pod, sizeof(pod)) == sizeof(pod);
}



CLASS_DECL_AURA bool file_copy_dup(const string & strNew,const string & strSrc,bool bOverwrite = true);


#ifdef WINDOWSEX

bool write_memory_to_file(HANDLE hFile,const void * lpBuf,memory_size_t nCount,memory_size_t * puiWritten);

#endif



#include "file_exception.h"


#include "file_status.h"



#include "file_seekable.h"


#include "file_writer_flush.h"


#include "file_file_base.h"


#include "file_stream_base.h"



#include "file_md5.h"



#include "file_reader.h"
#include "file_writer.h"

#include "file_file.h"

#include "file_istream.h"
#include "file_ostream_flush.h"
#include "file_ostream.h"
#include "file_stream.h"

#include "file_byte_istream.h"
#include "file_byte_ostream.h"
#include "file_byte_stream.h"


#include "file_binary_file.h"

#include "file_opened.h"

#include "file_dir.h"

#include "file_path.h"

#include "file_composite.h"

#include "file_serializable.h"

#include "file_buffer.h"

#include "file_text_file.h"


#include "file_folder_watch.h"


#include "file_plain_text_stream_base.h"
#include "file_plain_text_istream.h"
#include "file_plain_text_ostream.h"
#include "file_plain_text_stream.h"

#include "file_simple_binary_file.h"












#include "file_stdio_file.h"


#include "file_file_stream_base.h"
#include "file_file_istream.h"
#include "file_file_ostream.h"
#include "file_file_stream.h"





namespace file
{

   using pos_type = file_position_t;
   using off_type = file_offset_t;

   using iostate = ::file::e_iostate;
   using seekdir = ::file::e_seek;
}


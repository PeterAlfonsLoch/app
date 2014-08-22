#pragma once



CLASS_DECL_AXIS string file_as_string_dup(const char * path);
CLASS_DECL_AXIS string file_extension_dup(const char * path);


#include "file_status.h"



#include "file_seekable.h"


#include "file_writer_flush.h"


#include "file_stream_buffer_base.h"


#include "file_stream_base.h"







#include "file_reader.h"
#include "file_writer.h"

#include "file_stream_buffer.h"

#include "file_input_stream.h"
#include "file_output_stream_flush.h"
#include "file_output_stream.h"
#include "file_stream.h"

#include "file_byte_input_stream.h"
#include "file_byte_output_stream.h"
#include "file_byte_stream.h"


#include "file_binary_buffer.h"

#include "file_byte_input_stream_binary_buffer.h"

#include "file_byte_output_stream_binary_buffer.h"



#include "file_exception.h"

#include "file_opened.h"

#include "file_dir.h"

#include "file_composite.h"

#include "file_serializable.h"

#include "file_simple_binary_buffer.h"



#include "file_buffer.h"


#include "file_text_buffer.h"


#include "file_folder_watch.h"













#include "file_streambuf.h"





namespace file
{

   using pos_type = ::file_position;
   using off_type = ::file_offset;

   using iostate = ::file::e_iostate;
   using seekdir = ::file::e_seek;
}
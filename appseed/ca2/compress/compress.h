#pragma once


#include "int_to_string.h"
#include "item_name.h"
#include "archive.h"
#include "local_progress.h"


#include "reader_with_crc.h"
#include "input_stream_with_crc.h"
#include "writer_with_crc.h"


#include "lz_out_window.h"
#include "huffman_decoder.h"
#include "ppmd.h"
#include "ppmd7.h"
#include "ppmd8.h"




namespace compress
{

   typedef uint64 method_id;

} // namespace compress

#include "prop_id.h"
#include "method_properties.h"
#include "out_handler.h"

// coders
#include "coder.h"
#include "create_coder.h"
#include "copy_coder.h"
#include "filter_coder.h"
#include "coder_mixer.h"
#include "coder_mixer2.h"
#include "coder_mixer2mt.h"

// zlib
#include "gzip_helper.h"

// 7z
#include "7z/7z.h"

// bzip
#include "bzip_helper.h"

// rar
#include "rar/rar.h"

// zip
#include "zip/zip.h"


#include "register_codec.h"

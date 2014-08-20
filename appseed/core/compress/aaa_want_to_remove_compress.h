#pragma once


#include "core/compress/crypto/crypto.h"
#include "core/compress/compress/compress.h"



#include "compress_int_to_string.h"
#include "compress_item_name.h"
#include "compress_archive.h"
#include "compress_local_progress.h"


#include "compress_reader_with_crc.h"
#include "compress_input_stream_with_crc.h"
#include "compress_writer_with_crc.h"


#include "compress_lz_out_window.h"
#include "compress_huffman_decoder.h"
#include "compress_ppmd.h"
#include "compress_ppmd7.h"
#include "compress_ppmd8.h"




namespace libcompress
{

   typedef uint64_t method_id;

} // namespace libcompress

#include "compress_prop_id.h"
#include "compress_method_properties.h"
#include "compress_out_handler.h"

// coders
#include "compress_coder.h"
#include "compress_create_coder.h"
#include "compress_copy_coder.h"
#include "compress_filter_coder.h"
#include "compress_coder_mixer.h"
#include "compress_coder_mixer2.h"
#include "compress_coder_mixer2mt.h"

// 7z
#include "7z/7z.h"

// rar
#include "rar/rar.h"


#include "compress_register_codec.h"

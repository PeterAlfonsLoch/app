#pragma once



extern "C"
{
   
   #include "crypto_kernel.h"
   #include "sha1.h"

} // extern "C"

#ifdef inline
#undef inline
#endif


#include "7z_crc.h"



// compress interface
#include "compress_progress_info_interface.h"
#include "compress_coder_interface.h"
#include "compress_coder2_interface.h"
#include "compress_set_coder_properties_interface.h"
#include "compress_codecs_info_interface.h"
#include "compress_filter_interface.h"
#include "compress_set_decoder_properties2_interface.h"
#include "compress_write_coder_properties_interface.h"
#include "compress_get_input_stream_processed_size_interface.h"
#include "compress_set_coder_mt_interface.h"
#include "compress_get_sub_stream_size_interface.h"
#include "compress_set_input_stream_interface.h"
#include "compress_set_output_stream_interface.h"
#include "compress_set_codecs_info_interface.h"


// crypto interface
#include "crypto_properties_interface.h"
#include "crypto_reset_init_vector_interface.h"
#include "crypto_set_password_interface.h"
#include "crypto_get_text_password_interface.h"
#include "crypto_get_text_password2_interface.h"


// coders
#include "aes_cbc_coder.h"


// hash
#include "crypto_sha1.h"


// compress filters
#include "rar20.h"

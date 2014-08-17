#pragma once

#include "zlib/zconf.h"
#include "zlib/zlib.h"

#include "bsdiff/bsdiff.h"
#include "zip/zip.h"


#include "compress_gzip_stream.h"


#include "compress_bzip_stream.h"


#include "compress_compress.h"





CLASS_DECL_BASE int32_t bzuncompress(LPCSTR lpcszUncompressed, LPCSTR lpcszGzFileCompressed);

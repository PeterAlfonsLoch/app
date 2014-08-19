#pragma once

#include "zlib/zlib.h"

#include "bsdiff/libbsdiff.h"
#include "zip/zip.h"


#include "zlib/gzip_stream.h"


#include "bzip2/bzip_stream.h"


#include "compress_compress.h"





CLASS_DECL_BASE int32_t bzuncompress(LPCSTR lpcszUncompressed, LPCSTR lpcszGzFileCompressed);

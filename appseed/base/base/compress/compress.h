#pragma once

#include "zlib.h"

#include "bsdiff/libbsdiff.h"
#include "zip/zip.h"


#include "compress_compress.h"





CLASS_DECL_BASE int32_t bzuncompress(LPCSTR lpcszUncompressed, LPCSTR lpcszGzFileCompressed);

#ifndef __GNUC__
#pragma once
#endif

extern "C"
{
#include <bzlib.h>
}

#include "zlib.h"

#include "axis/zlib/zutil.h"

#include "zip/zip.h"

#include "gzip_stream.h"

#include "bzip_stream.h"

CLASS_DECL_AXIS int32_t bzuncompress(LPCSTR lpcszUncompressed, LPCSTR lpcszGzFileCompressed);

#include "compress_compress.h"


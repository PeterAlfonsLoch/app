#pragma once


#include "zlib/zconf.h"
#include "zlib/zlib.h"
#include "bsdiff/bsdiff.h"
#define ZLIB_INTERNAL
#include "zip/zip.h"
#undef ZLIB_INTERNAL


#include "compress_gzip_stream.h"


#include "compress_bzip_stream.h"


#include "compress_compress.h"





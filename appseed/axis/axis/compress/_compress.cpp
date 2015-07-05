#include "framework.h"
#include "fiasco_finder.h"


#include "zip/unzip.h"
#ifndef NOUNCRYPT
#define INCLUDECRYPTINGCODE_IFCRYPTALLOWED
#include "zip/crypt.h"
#endif
#include "zip/zipImpl.h"


//O volume na unidade C n∆o tem nome.
 //O N£mero de SÇrie do Volume Ç 72AC-5E14

 //Pasta de C:\nordroid\app\appseed\axis\axis\compress

#include "bzip_stream.cpp"
#include "compress_compress.cpp"
#include "gzip_stream.cpp"
//2015-01-04  19:21                 0 _compress.cpp"
//               4 arquivo(s)         16.402 bytes
//
// Pasta de C:\nordroid\app\appseed\axis\axis\compress\bsdiff
//
//2014-12-28  03:02            10.511 bsdiff.cpp"
//#include "bsdiff/bsdiff_bsdiff.cpp"
//#include "bsdiff/bsdiff_bspatch.cpp"
//2014-12-28  03:02             6.226 bspatch.cpp"
//               4 arquivo(s)         41.983 bytes
//
// Pasta de C:\nordroid\app\appseed\axis\axis\compress\zip

#include "zip/zip_api.cpp"
#include "zip/zip_file.cpp"
#include "zip/zip_in_file.cpp"
#include "zip/zip_ioapi.cpp"
#include "zip/zip_memory_buffer.cpp"
#include "zip/zip_unzip.cpp"
#include "zip/zip_util.cpp"
#include "zip/zip_zip.cpp"
     //          8 arquivo(s)        127.171 bytes

     //Total de Arquivos na Lista:
     //         16 arquivo(s)        185.556 bytes
     //          0 pasta(s)   19.307.741.184 bytes dispon°veis

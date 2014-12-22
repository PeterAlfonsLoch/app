#pragma once

#include "unzip.h"
#include "ioapi.h"

namespace zip
{

   class CLASS_DECL_BASE api  
   {
   public:


      static map < unzFile, unzFile, memory_buffer *, memory_buffer * & > m_mapUnzip;
      
      
      api();
      virtual ~api();


      static unzFile unzipOpen(memory_buffer * pfile);
      static unzFile unzipOpen(File * pfile);

      static zipFile zipOpen(File * pfile);

      


   };


} // namespace zip

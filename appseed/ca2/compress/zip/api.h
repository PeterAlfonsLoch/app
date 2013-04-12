#pragma once

#include "unzip.h"
#include "ioapi.h"

namespace zip
{

   class CLASS_DECL_ca api  
   {
   public:


      static map < unzFile, unzFile, memory_file *, memory_file * & > m_mapUnzip;
      
      
      api();
      virtual ~api();


      static unzFile unzipOpen(memory_file * pfile);
      static unzFile unzipOpen(File * pfile);

      static zipFile zipOpen(File * pfile);

      


   };


} // namespace zip

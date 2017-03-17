#pragma once

#include "unzip.h"
#include "ioapi.h"

namespace zip
{

   class CLASS_DECL_AURA api  
   {
   public:


      //static map < unzFile, unzFile, memory_file *, memory_file * & > m_mapUnzip;
      
      
      api();
      virtual ~api();


	  static_function unzFile unzipOpen(memory_file * pfile);
	  static_function unzFile unzipOpen(File * pfile);

	  static_function zipFile zipOpen(File * pfile);

      


   };


} // namespace zip

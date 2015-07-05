#pragma once

#include "unzip.h"
#include "ioapi.h"

namespace zip
{

   class CLASS_DECL_AXIS api  
   {
   public:


      //static map < unzFile, unzFile, memory_buffer *, memory_buffer * & > m_mapUnzip;
      
      
      api();
      virtual ~api();


	  static_function unzFile unzipOpen(memory_buffer * pfile);
	  static_function unzFile unzipOpen(File * pfile);

	  static_function zipFile zipOpen(File * pfile);

      


   };


} // namespace zip

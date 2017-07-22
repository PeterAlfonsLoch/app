#pragma once


#include "zip_unzip.h"
#include "zip_ioapi.h"


namespace zip
{

   
   class CLASS_DECL_AURA api  
   {
   public:


      api();
      virtual ~api();


      static unzFile unzip_open(memory_file * pfile);
      static unzFile unzip_open(file * pfile);

      static zipFile zip_open(file * pfile);

      


   };


} // namespace zip

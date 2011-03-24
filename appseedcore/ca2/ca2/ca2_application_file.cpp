#include "StdAfx.h"


namespace ca2
{


   namespace file
   {

      application::application()
      {
      }


      string application::as_string(var varFile)
      {
         return System.file().as_string(varFile, m_papp);
      }

      void application::as_memory(var varFile, primitive::memory & mem)
      {
         return System.file().as_memory(varFile, mem, m_papp);
      }
   
      void application::lines(stringa & stra, var varFile)
      {
         return System.file().lines(stra, varFile, m_papp);
      }

   } // namespace file


} // namespace ca2
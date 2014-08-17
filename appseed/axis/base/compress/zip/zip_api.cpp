#include "framework.h"


namespace zip
{

   //map < unzFile, unzFile, memory_buffer *, memory_buffer * & > api::m_mapUnzip;

   api::api()
   {

   }

   api::~api()
   {

   }


   unzFile api::unzipOpen(memory_buffer * pfile)
   {
      unzFile pf = unzOpen2("pad", &pfile->m_filefuncdef);
      if(pf == NULL)
         return NULL;

     // m_mapUnzip.set_at(pf, pfile);

      return pf;

   }


   unzFile api::unzipOpen (File * pfile)
   {
      unzFile pf = unzOpen2("pad", &pfile->m_filefuncdef);
      if(pf == NULL)
         return NULL;

   //   m_mapUnzip.set_at(pf, pfile);

      return pf;

   }

   zipFile api::zipOpen(File * pfile)
   {
      zipFile pf = zipOpen2("pad", APPEND_STATUS_CREATE, NULL, &pfile->m_filefuncdef);
      if(pf == NULL)
         return NULL;

     // m_mapUnzip.set_at(pf, pfile);

      return pf;

   }

} // namespace zip
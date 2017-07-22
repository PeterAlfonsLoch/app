bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);

bool ios1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   static mutex * pmutex = NULL;
   
   if(pmutex == NULL)
   {
      
      pmutex = new mutex(NULL);
      
   }
   
   synch_lock sl(pmutex);
   
   
   return mm1_get_file_image(pcr, cx, cy, iScan, psz);
   
   
}


bool ios_get_file_image(::draw2d::dib * pdib, const char * psz)
{
   
   if(!ios1_get_file_image(pdib->m_pcolorref, pdib->m_size.cx, pdib->m_size.cy, pdib->m_iScan, psz))
   {
      
      return false;
      
   }
   
   return true;
   
}

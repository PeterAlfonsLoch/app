#include "framework.h" 

namespace visual
{
   icon::icon()
   {
      m_hicon = NULL;
      m_bAutoDelete = true;
   }
   icon::~icon()
   {
      if(m_bAutoDelete)
      {
         if(m_hicon != NULL)
         {
            ::DestroyIcon(m_hicon);
         }
      }
   }

   icon::operator HICON()
   {
      return m_hicon;
   }

}

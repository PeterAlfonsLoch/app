#include "StdAfx.h"

namespace html
{

   bool font::create()
   {
      LOGFONT lf;

      memset(&lf, 0, sizeof(lf));


      if(m_strWeight.CompareNoCase("bold") == 0)
      {
         lf.lfWeight = 800;
      }
      else
      {
         lf.lfWeight = 400;
      }
      lf.lfHeight = atoi(m_strSize);
      strcpy(lf.lfFaceName, m_strFamily);

      m_font.CreateFontIndirectA(&lf);

      return true;
   }



} // namespace html
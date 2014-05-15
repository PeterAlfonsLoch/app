#include "framework.h"
#include <X11/Xft/Xft.h>
// Ubuntu apt-get install libxft-dev
// CentOS yum install libXft-devel
// openSUSE zypper install libxft-devel





namespace draw2d_xlib
{


   font::font(sp(::base::application) papp) :
   element(papp)
   {

      m_pdisplay = NULL;
      m_pfont = NULL;
      m_fontset = None;
      m_pft = NULL;

   }


   font::~font()
   {

      if(m_fontset != None && m_pdisplay != NULL)
      {
         XFreeFontSet(m_pdisplay, m_fontset);
         m_fontset = NULL;
      }

      if(m_pfont != NULL && m_pdisplay != NULL)
      {
         XFreeFont(m_pdisplay, m_pfont);
         m_pfont = NULL;
      }

      if(m_pft != NULL && m_pdisplay != NULL)
      {
         XftFontClose(m_pdisplay, m_pft);
         m_pft = NULL;
      }

      m_pdisplay = NULL;

   }


   void font::dump(dump_context & dumpcontext) const
   {

      ::draw2d::font::dump(dumpcontext);

   }


   void * font::get_os_data() const
   {

      return (void *) m_fontset;

   }


} // namespace draw2d_xlib






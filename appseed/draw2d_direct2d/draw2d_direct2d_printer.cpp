#include "framework.h"
#include <WinSpool.h>


namespace draw2d_direct2d
{


   printer::printer(::aura::application * papp) :
      element(papp),
      ::aura::printer(papp),
      m_documentproperties(papp)
   {
   }

   printer::~printer()
   {
   }

   bool printer::open(const char * pszDeviceName)
   {
      if(is_opened())
         close();
#ifndef METROWIN
      return OpenPrinter((LPSTR) (LPCSTR) pszDeviceName, &m_hPrinter, NULL) != FALSE && m_hPrinter != NULL;
#else
      throw todo(get_app());
      return false;
#endif
   }

   bool printer::is_opened()
   {
      return m_hPrinter != NULL;
   }

   ::draw2d::graphics * printer::create_graphics()
   {
      if(!m_documentproperties.initialize(this))
         return NULL;
      return m_documentproperties.create_graphics();
   }


   bool printer::close()
   {
      bool bOk = true;
      if(m_hPrinter != NULL)
      {
#ifndef METROWIN
         bOk = ::ClosePrinter(m_hPrinter) != FALSE;
#else
throw todo(get_app());
return false;
#endif
m_hPrinter = NULL;
      }
      return bOk;
   }


   printer::document_properties::document_properties(::aura::application * papp) :
      element(papp)
   {
      m_hdc = NULL;
      m_pdevmode = NULL;
   }

   printer::document_properties::~document_properties()
   {
      close();
   }

   bool printer::document_properties::initialize(::draw2d_direct2d::printer * pprinter, DEVMODE * pdevmode)
   {
      UNREFERENCED_PARAMETER(pdevmode);
      if(m_pdevmode != NULL)
         return false;
      if(m_hdc != NULL)
         return false;
#ifndef METROWIN
      int iSize = DocumentProperties(NULL, pprinter->m_hPrinter, (LPSTR)(LPCSTR) pprinter->m_strName, NULL, NULL, 0);
      m_pdevmode = (DEVMODE *) malloc(iSize);
      if(!DocumentProperties(NULL, pprinter->m_hPrinter, (LPSTR) (LPCSTR) pprinter->m_strName, m_pdevmode, NULL, DM_OUT_BUFFER))
      {
         throw "failed to get printer DocumentProperties";
         return false;
      }
#else
throw todo(get_app());
return false;
#endif
return true;
   }

   bool printer::document_properties::close()
   {
      throw todo(get_app());
#ifndef METROWIN
      if(m_hdc != NULL)
      {
         ::DeleteDC(m_hdc);
         m_hdc = NULL;
      }
#else
throw todo(get_app());
return false;
#endif
if(m_pdevmode != NULL)
      {
         free(m_pdevmode);
         m_pdevmode = NULL;
      }
      return true;
   }



   ::draw2d::graphics * printer::document_properties::create_graphics()
   {
      if(m_pdevmode == NULL)
         return NULL;
      if(m_hdc != NULL)
         return NULL;
#ifndef METROWIN
      m_hdc = ::CreateDC("WINSPOOL", (LPCSTR) m_pdevmode->dmDeviceName, NULL, m_pdevmode);
::draw2d::graphics_sp g(allocer());
      g->Attach(m_hdc);
      return g.detach();
#else
      throw todo(get_app());
      return NULL;
#endif
   }


} // namespace win2


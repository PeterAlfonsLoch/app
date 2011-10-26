#include "StdAfx.h"
#include <WinSpool.h>

namespace user
{


   printer::printer(::ca::application * papp) :
      ca(papp)
   {
      m_hPrinter = NULL;
   }

   printer::~printer()
   {
      close();
   }

   bool printer::open(const char * pszDeviceName)
   {
      if(m_hPrinter != NULL)
         close();
      return OpenPrinter((LPSTR) (LPCSTR) pszDeviceName, &m_hPrinter, NULL) != FALSE && m_hPrinter != NULL;
   }

   bool printer::close()
   {
      if(m_hPrinter != NULL)
      {
         ::ClosePrinter(m_hPrinter);
      }
   }


   printer::document_properties::document_properties(::user::printer & printer, DEVMODE * pdevmode) :
      ca(printer.get_app())
   {
      m_hdc = NULL;
      int iSize = DocumentProperties(NULL, hPrinter, (LPSTR)(LPCSTR)strPrinter, NULL, NULL, 0);
      m_pdevmode = (PDEVMODE) malloc(iSize);
      memset(pdevmode, 0, iSize);
      if(!DocumentProperties(NULL, hPrinter, (LPSTR)(LPCSTR)strPrinter, pdevmode, NULL, DM_OUT_BUFFER))
      {
         throw simple_exception();
      }
   }

   printer::document_properties::~document_properties()
   {
      ::DeleteDC(m_hdc);
      if(m_pdevmode != NULL)
      {
         free(m_pdevmode);
      }
   }
         
   ::ca::graphics * printer::document_properties::create_graphics()
   {
      m_hdc = ::CreateDC("WINSPOOL", (LPCTSTR) m_pdevmode->dmDeviceName, NULL, m_pdevmode);
      ::ca::graphics * pgraphics = System.get_graphics_from_os_data(m_hdc);
      pgraphics->m_bPrint = true;

   }
      

} // namespace user
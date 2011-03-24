#include "StdAfx.h"
#include "document.h"

namespace vmsp
{

   DocumentDataExchange::DocumentDataExchange(DocumentInterface * pdoc)
   {
      m_pdocument = pdoc;
   }


   DocumentInterface * DocumentDataExchange::get_document()
   {
      return m_pdocument;
   }

   //////////////////////////////////////////////////////////////////////
   // Construction/Destruction
   //////////////////////////////////////////////////////////////////////

   DocumentInterface::DocumentInterface()
   {

   }

   DocumentInterface::~DocumentInterface()
   {

   }

   void DocumentInterface::DocumentDX(DocumentDataExchange * pdx)
   {
   }

////////////////////////////////////////////////
} // namespace vmsp
////////////////////////////////////////////////

#include "StdAfx.h"

namespace musctrl
{

   MusicalPlayerCentral::MusicalPlayerCentral(::ca::application * papp) :
      ca(papp)
   {
      m_pdoctemplate = NULL;
   }

   MusicalPlayerCentral::~MusicalPlayerCentral()
   {

   }

   MusicalPlayerCentral & MusicalPlayerCentral::AppGetMusicalPlayerCentral(::ca::application * papp)
   {
      return MusicalPlayerCentralContainer::AppGetMusicalPlayerCentral(papp);   
   }

   single_document_template * MusicalPlayerCentral::get_document_template()
   {
       return dynamic_cast < single_document_template * > (m_pdoctemplate);
   }


   single_document_template * MusicalPlayerCentral::CreateDocTemplate()
   {
      if(m_pdoctemplate != NULL)
         return m_pdoctemplate;
      single_document_template* pdoctemplate;
      pdoctemplate = new single_document_template(
         dynamic_cast < ::ca::application * > (m_papp),
         m_strMatter,
         m_typeinfoDocument,
         m_typeinfoFrameWnd,
         m_typeinfoView);
      m_pdoctemplate = pdoctemplate;
      return pdoctemplate;
   }

} // namespace musctrl
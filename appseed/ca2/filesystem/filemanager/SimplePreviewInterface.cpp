#include "framework.h"


namespace filemanager
{


   SimplePreviewInterface::SimplePreviewInterface(sp(::ca2::application) papp) :
      ::ca2::ca2(papp),
      ::user::interaction(papp)
   {

   }


   SimplePreviewInterface::~SimplePreviewInterface()
   {
   }


   void SimplePreviewInterface::_001OnDraw(::ca2::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);
      pdc->FillSolidRect(rectClient, RGB(200, 200, 190));


      if(m_iCurFile < 0)
      {
      }
      else if(m_iCurFile == 0 && m_straPath.get_size() == 0)
      {
         pdc->TextOut(10, 10, "No files in this directory");
      }
      else if(m_iCurFile < m_straPath.get_size())
      {
         pdc->TextOut(10, 10, m_straTitle[m_iCurFile]);
      }

   }


} // namespace filemanager





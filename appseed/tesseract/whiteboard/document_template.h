#pragma once

#include "MultiFrameViewSingleDocTemplate.h"

class html_view;

namespace whiteboard
{

   class html_view;

   class CLASS_DECL_CA2_TESSERACT document_template : 
      virtual public MultiFrameViewSingleDocTemplate 
   {
   public:

      
      document_template(::ca::application * cast);
      virtual ~document_template();

      
      html_view * CreateHtmlWnd(bool bMakeVisible);

   };

} // namespace whiteboard

#pragma once

namespace syllomatter
{

   class CLASS_DECL_CA2_TESSERACT filemanager_document :
      public ::filemanager::document
   {
   public:
      filemanager_document(::ca::application * papp);
      virtual ~filemanager_document();

      DECL_GEN_SIGNAL(_001OnCommit_)
   };

}//  namespace syllomatter
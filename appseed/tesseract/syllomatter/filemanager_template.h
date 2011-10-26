#pragma once

namespace syllomatter
{

   class CLASS_DECL_CA2_TESSERACT filemanager_template :
      public FileManagerTemplate
   {
   public:
      filemanager_template(::ca::application * papp);
      virtual ~filemanager_template();

      virtual void Initialize(::ca::application * papp, int iTemplate, const char * pszMatter);
   };

}//  namespace syllomatter
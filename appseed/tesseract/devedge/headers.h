#pragma once

namespace devedge
{

   class CLASS_DECL_CA2_TESSERACT headers :
      virtual public folder
   {
   public:
      headers(::ca::application * papp);

      bool m_bStdAfx;

      void load(project * pproject);
   };

} // namespace devedge
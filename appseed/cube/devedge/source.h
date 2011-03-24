#pragma once

namespace devedge
{

   class CLASS_DECL_CA2_CUBE source :
      virtual public folder
   {
   public:
      source(::ca::application * papp);

      bool m_bStdAfx;

      void load(project * pproject);
   };

} // namespace devedge
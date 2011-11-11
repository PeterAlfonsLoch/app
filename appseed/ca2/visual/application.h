#pragma once

namespace visual
{
   class CLASS_DECL_ca application  :
      virtual public ::ca8::application
   {
   public:
      application();
      virtual ~application();
      virtual class imaging & imaging();
      virtual bool initialize();
      class font_central & font_central();
      class font_central * m_pfontcentral;
   protected:
      class imaging * m_pimaging;
   };

   inline CLASS_DECL_ca application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace visual
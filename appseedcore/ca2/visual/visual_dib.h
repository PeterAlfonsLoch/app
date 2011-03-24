#pragma once

struct FIBITMAP;

namespace visual
{

   class CLASS_DECL_ca dib_sp :
      virtual public ca::dib_sp
   {
   public:
      
      dib_sp();
      dib_sp(::ca::application * papp);
      virtual ~dib_sp();


      virtual bool load_from_file(var varFile);
      virtual bool load_from_matter(const char * pszMatter);
      virtual bool from(::ca::graphics * pgraphics, FIBITMAP * pfibitmap, bool bUnloadFI);

   };

} // namespace visual

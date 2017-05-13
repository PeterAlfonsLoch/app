#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA dibmap :
      virtual public map < class size, class size, ::draw2d::dib_sp >
   {
   public:


      dibmap(::aura::application * papp);


      ::draw2d::dib_sp & operator[](class size key);

      ::draw2d::dib_sp & get(class size key, bool & bExists);

   };


} // namespace draw2d





#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA dibmap :
      virtual public map < class size, class size, ::draw2d::dib_sp, ::draw2d::dib_sp >
   {
   public:


      dibmap(::aura::application * papp) :
         object(papp)
      {
      }


      inline ::draw2d::dib_sp & operator[](class size key)
      {
         ::draw2d::dib_sp & dib = map < class size, class size, ::draw2d::dib_sp, ::draw2d::dib_sp >::operator [](key);
         if (dib.is_null())
         {
            dib.alloc(allocer());
            dib->create(key);
         }
         return dib;
      }


   };


} // namespace draw2d





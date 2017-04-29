
namespace draw2d
{


   dibmap::dibmap(::aura::application * papp) :
      ::object(papp)
   {

   }


   ::draw2d::dib_sp & dibmap::operator[](class size key)
   {

      bool bExists;

      return get(key, bExists);

   }


   ::draw2d::dib_sp & dibmap::get(class size key, bool & bExists)
   {
    
      ::draw2d::dib_sp & dib = map < class size, class size, ::draw2d::dib_sp >::operator [](key);

      if (dib.is_null())
      {

         dib.alloc(allocer());

         dib->create(key);

         bExists = false;

      }
      else
      {

         bExists = true;

      }

      return dib;

   }


} // namespace draw2d







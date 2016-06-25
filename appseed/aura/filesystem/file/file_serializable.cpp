//#include "framework.h"


namespace file
{

      
   //serializable::serializable()
   //{

   //}

   void serializable::write(ostream & ostream)
   {

      ((const serializable *) this)->write(ostream);

   }

   void serializable::write(ostream & ostream) const
   {
      
      ((serializable *) this)->write(ostream);

   }

   void serializable::read(istream & istream)
   {

   }

} // namespace file












CLASS_DECL_AURA bool file_put(const char * path, ::file::serializable & s, ::aura::application * papp)
{

   try
   {

      if (papp == NULL)
      {

         papp = ::get_thread_app();

      }

      if (papp == NULL)
      {

         return false;

      }

      ::file::buffer_sp pfile = App(papp).file().get_file(path, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory | ::file::share_exclusive);

      if (pfile.is_null())
      {

         return false;

      }

      ::file::byte_ostream os(pfile);

      os << s;

      return true;

   }
   catch (...)
   {


   }

   return false;

}


CLASS_DECL_AURA bool file_as(::file::serializable & s, const char * path, ::aura::application * papp)
{

   try
   {

      if (papp == NULL)
      {

         papp = ::get_thread_app();

      }

      if (papp == NULL)
      {

         return false;

      }

      ::file::buffer_sp pfile = App(papp).file().get_file(path, ::file::mode_read | ::file::type_binary | ::file::share_deny_write);

      if (pfile.is_null())
      {

         return false;

      }

      ::file::byte_istream is(pfile);

      is >> s;

      return true;

   }
   catch (...)
   {


   }

   return false;

}







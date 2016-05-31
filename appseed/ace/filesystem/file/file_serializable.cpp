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












CLASS_DECL_ACE bool file_put(const char * path, ::file::serializable & s, ::ace::application * papp)
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

      ::file::buffer_sp pfile = App(papp).file().get_file(path, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);

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


CLASS_DECL_ACE bool file_as(::file::serializable & s, const char * path, ::ace::application * papp)
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

      ::file::buffer_sp pfile = App(papp).file().get_file(path, ::file::mode_read | ::file::type_binary);

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







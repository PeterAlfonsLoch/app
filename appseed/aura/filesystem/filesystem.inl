#pragma once


namespace file
{

//   inline path::path(const var & var,e_path epath): path(var.get_file_path(),epath){}
   inline path::path(const property & property,e_path epath, int iDir): path(property.get_value().get_file_path(),epath, iDir){}
   inline path & path::operator = (const var & var) { return operator = (var.get_string()); }
   inline path & path::operator += (const var & var) { return operator += (var.get_string()); }
   inline path path::operator + (const var & var) const { return operator + (var.get_string()); }
   inline path path::operator + (const property & property) const { return operator + (property.get_string()); }
   inline path path::operator + (const id & id) const { return operator + (id.str()); }
   inline path path::operator / (const property & property) const { return operator /(::file::path(property)); }
   inline path path::operator * (const property & property) const { return operator *(::file::path(property)); }
   inline path & path::operator *= (const property & property) { return operator *=(::file::path(property)); }
   inline path path::folder() const { return ::file::path(::dir::name((const string &)*this),m_epath); }
   inline path path::sibling(const path & path) const   { return ::file::path(::dir::name((const string &)*this) + sep() + ::sz::trim_left_path_sep(path)); }
   inline path path::sibling(const string & str) const   { return ::file::path(::dir::name((const string &)*this) + sep() + ::sz::trim_left_path_sep(str)); }
   inline path path::sibling(const char * psz) const   { return ::file::path(::dir::name((const string &)*this) + sep() + ::sz::trim_left_path_sep(psz)); }
   inline string path::extension() const { return &m_pszData[find_skip_or_length('.', rfind(sep()) + 1)]; }
   inline string path::final_extension() const { return file_final_extension_dup(operator const char *()); }
   inline patha path::ascendants_path() const { patha patha; return ascendants_path(patha); }
   inline patha path::ascendants_name() const { patha patha; return ascendants_name(patha); }
//   inline path path::folder() const { return ::dir::name(*this); }
   inline bool path::operator == (const var & var) const { return operator == (string(var)); }
   inline bool path::operator != (const var & var) const { return operator != (string(var)); }




   template < class T >
   bool ::file::system::output(::aura::application * papp, const ::file::path & pathOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), const ::file::path & pathIn)
   {

      ::file::path pathDownloading;

      try
      {

         ::file::ostream os;

         if (!prepare_output(papp, pathDownloading, pathOut, os))
         {

            return false;

         }

         ::file::istream is;

         if (!prepare_input(papp, is, pathIn))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }


      try
      {

         if (!post_output(papp, pathOut, pathDownloading))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   template < class T >
   bool ::file::system::output(::aura::application * papp, const ::file::path & pathOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::file * pfileIn)
   {

      ::file::path pathDownloading;

      try
      {

         ::file::ostream os;

         if (!prepare_output(papp, pathDownloading, pathOut, os))
         {

            return false;

         }

         ::file::istream is;

         if (!prepare_input(papp, is, pfileIn))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }


      try
      {

         if (!post_output(papp, pathOut, pathDownloading))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   template < class T >
   bool system::output(::aura::application * papp, const ::file::path & pathOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::istream & is)
   {

      ::file::path pathDownloading;

      try
      {

         ::file::ostream os;

         if (!prepare_output(papp, pathDownloading, pathOut, os))
         {

            return false;

         }

         if (!prepare_input(papp, is))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }


      try
      {

         if (!post_output(papp, pathOut, pathDownloading))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;
   }


   template < class T >
   bool ::file::system::output(::aura::application * papp, file * pfileOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), const ::file::path & pathIn)
   {

      ::file::path pathDownloading;

      try
      {

         ostream os(pfileOut);

         if (os.m_spfile.is_null())
         {

            return false;

         }

         ::file::istream is;

         if (!prepare_input(papp, is, pathIn))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   template < class T >
   bool ::file::system::output(::aura::application * papp, file * pfileOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::file * pfileIn)
   {

      ::file::path pathDownloading;

      try
      {

         ostream os(pfileOut);

         if (os.m_spfile.is_null())
         {

            return false;

         }

         ::file::istream is;

         if (!prepare_input(papp, is, pfileIn))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   template < class T >
   bool system::output(::aura::application * papp, file * pfileOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::istream & is)
   {

      ::file::path pathDownloading;

      try
      {

         ostream os(pfileOut);

         if (os.m_spfile.is_null())
         {

            return false;

         }

         if (!prepare_input(papp, is))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }




   template < class T >
   bool ::file::system::output(::aura::application * papp, ostream & os, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), const ::file::path & pathIn)
   {

      ::file::path pathDownloading;

      try
      {

         ::file::istream is;

         if (!prepare_input(papp, is, pathIn))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   template < class T >
   bool ::file::system::output(::aura::application * papp, ostream & os, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::file * pfileIn)
   {

      ::file::path pathDownloading;

      try
      {

         ::file::istream is;

         if (!prepare_input(papp, is, pfileIn))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   template < class T >
   bool system::output(::aura::application * papp, ostream & os, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::istream & is)
   {

      ::file::path pathDownloading;

      try
      {

         if (!prepare_input(papp, is))
         {

            return false;

         }

         if (!(p->*lpfnOuput)(os, is))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   template < class T >
   bool application::output(const ::file::path & pathOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), const ::file::path & pathIn)
   {

      return System.file().output(get_app(), pathOut, p, lpfnOuput, pathIn);

   }


   template < class T >
   bool application::output(const ::file::path & pathOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::file * pfileIn)
   {

      return System.file().output(get_app(), pathOut, p, lpfnOuput, pfileIn);

   }


   template < class T >
   bool application::output(const ::file::path & pathOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::istream & istream)
   {

      return System.file().output(get_app(), pathOut, p, lpfnOuput, istream);

   }

   template < class T >
   bool application::output(file * pfileOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), const ::file::path & pathIn)
   {

      return System.file().output(get_app(), pfileOut, p, lpfnOuput, pathIn);

   }


   template < class T >
   bool application::output(file * pfileOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::file * pfileIn)
   {

      return System.file().output(get_app(), pfileOut, p, lpfnOuput, pfileIn);

   }


   template < class T >
   bool application::output(file * pfileOut, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::istream & istream)
   {

      return System.file().output(get_app(), pfileOut, p, lpfnOuput, istream);

   }


   template < class T >
   bool application::output(ostream & os, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), const ::file::path & pathIn)
   {

      return System.file().output(get_app(), os, p, lpfnOuput, pathIn);

   }


   template < class T >
   bool application::output(ostream & os, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::file * pfileIn)
   {

      return System.file().output(get_app(), os, p, lpfnOuput, pfileIn);

   }


   template < class T >
   bool application::output(ostream & os, T * p, bool (T::*lpfnOuput)(::file::ostream &, ::file::istream &), ::file::istream & istream)
   {

      return System.file().output(get_app(), os, p, lpfnOuput, istream);

   }


} // namespace file


inline ::file::path operator + (const string & str,const ::file::path & path) { return ::file::path(str + string(path)); }
inline ::file::path operator + (const char * psz,const ::file::path & path) {  return ::file::path(psz + string(path)); }
inline ::file::path operator + (const var & var,const ::file::path & path) { return ::file::path(var.get_string() + string(path)); }
inline ::file::path operator / (const string & str,const ::file::path & path) { ::file::path p(str);  return p / path; }
inline ::file::path operator / (const char * psz,const ::file::path & path) { ::file::path p(psz);  return p / path; }
inline ::file::path operator / (const var & var,const ::file::path & path) { ::file::path p(var.get_file_path());  return p / path; }



template < class ARRAY >
bool file_put_array(const char * path, const ARRAY & a, ::aura::application * papp)
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

      ::file::file_sp pfile = App(papp).file().get_file(path, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);

      if (pfile.is_null())
      {

         return false;

      }

      ::file::byte_ostream ostream(pfile);

      ::count count = a.get_count();

      ostream.write_arbitrary(count);

      for (index index = 0; index < count; index++)
      {

         ostream << a.element_at(index);

      }

      return true;

   }
   catch (...)
   {


   }

   return false;

}


template < class ARRAY >
bool file_as_array(ARRAY & a, const char * path, ::aura::application * papp)
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

      ::file::file_sp pfile = App(papp).file().get_file(path, ::file::mode_read | ::file::type_binary);

      if (pfile.is_null())
      {

         return false;

      }

      ::file::byte_istream istream(pfile);

      ::count count;
      //istream >> count;
      istream.read_arbitrary(count);

      if (istream.fail())
      {

         return false;

      }

      a.allocate(count);

      for (index index = 0; index < count; index++)
      {

         istream >> a.element_at(index);

         if (istream.fail())
         {

            return false;

         }

      }

      a.on_after_read();

      return true;

   }
   catch (...)
   {


   }

   return false;

}






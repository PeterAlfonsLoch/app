#pragma once


namespace file
{


   class istream;
   class ostream;


   class CLASS_DECL_AURA serializable
   {
   public:


      virtual void write(ostream & ostream);
      virtual void write(ostream & ostream) const;
      virtual void read(istream & istream);


   };


   namespace array
   {

      template < class ARRAY >
      void write(ostream & ostream,const ARRAY & a)
      {
         ::count count = a.get_count();
         ostream.write_arbitrary(count);
         for(index index = 0; index < count; index++)
         {
            ostream << a.element_at(index);
         }
      }

      template < class ARRAY >
      void read(istream & istream,ARRAY & a)
      {
         ::count count;
         //istream >> count;
         istream.read_arbitrary(count);

         if(istream.fail())
         {
            return;
         }

         a.allocate(count);
         for(index index = 0; index < count; index++)
         {
            istream >> a.element_at(index);
            if(istream.fail())
            {
               return;
            }
         }
         a.on_after_read();
      }


   } // namespace array

   namespace ptra
   {

      template < class ARRAY >
      void write(ostream & ostream,const ARRAY & a)
      {
         ::count count = a.get_count();
         ostream.write_arbitrary(count);
         for(index index = 0; index < count; index++)
         {
            ostream << *a.element_at(index);
         }
      }

      template < class ARRAY >
      void read(istream & istream,ARRAY & a)
      {
         ::count count;
         //istream >> count;
         istream.read_arbitrary(count);

         if(istream.fail())
         {
            return;
         }

         a.allocate(count);
         for(index index = 0; index < count; index++)
         {
            istream >> *a.element_at(index);
            if(istream.fail())
            {
               return;
            }
         }
         a.on_after_read();
      }


   } // namespace array

   namespace map
   {

      template < class type_map >
      void write(ostream & ostream,const type_map & m)
      {
         ::count count = m.get_count();
         ostream.write_arbitrary(count);
         const typename type_map::pair * p = m.PGetFirstAssoc();
         for(index index = 0; index < count; index++)
         {
            ostream << p->m_element1;
            ostream << p->m_element2;
            p = m.PGetNextAssoc(p);
         }
      }

      template < class type_map >
      void read(istream & istream,type_map & m)
      {
         ::count count;
         istream.read_arbitrary(count);
         if(istream.fail())
            return;
         typename type_map::AXIS_KEY key;
         typename type_map::AXIS_VALUE value;
         for(index index = 0; index < count; index++)
         {
            istream >> key;
            istream >> value;
            if(istream.fail())
               return;
            m.set_at(key,value);
         }
         m.on_after_read();
      }

   } // namespace map



} // namespace file


template < class TYPE,class ARG_TYPE = const TYPE &,class DEFCONSTRUCTOR = ::constructor::def < TYPE > >
::file::ostream & operator << (::file::ostream & os,const array < TYPE,ARG_TYPE,DEFCONSTRUCTOR > & a)
{
   ::file::array::write(os,a);
   return os;
}

template < class TYPE,class ARG_TYPE = const TYPE &,class DEFCONSTRUCTOR = ::constructor::def < TYPE > >
::file::istream & operator >> (::file::istream & is,array < TYPE,ARG_TYPE,DEFCONSTRUCTOR > & a)
{
   ::file::array::read(is,a);
   return is;
}





template<class TYPE,class ARG_TYPE = const TYPE &>
::file::ostream & operator << (::file::ostream & os,const raw_array < TYPE,ARG_TYPE> & a)
{
   ::file::array::write(os,a);
   return os;
}

template<class TYPE,class ARG_TYPE = const TYPE &>
::file::istream & operator >> (::file::istream & is,raw_array < TYPE,ARG_TYPE > & a)
{
   ::file::array::read(is,a);
   return is;
}


template < class TYPE,class ARRAY_TYPE = raw_ref_array < TYPE * > >
::file::ostream & operator << (::file::ostream & os,const ref_array < TYPE,ARRAY_TYPE> & a)
{
   ::file::ptra::write(os,a);
   return os;
}

template < class TYPE,class ARRAY_TYPE = raw_ref_array < TYPE * > >
::file::istream & operator >> (::file::istream & is,ref_array < TYPE,ARRAY_TYPE > & a)
{
   ::file::ptra::read(is,a);
   return is;
}


CLASS_DECL_AURA bool file_put(const char * path, ::file::serializable & s, ::aura::application * papp = NULL);
CLASS_DECL_AURA bool file_as(::file::serializable & s, const char * path, ::aura::application * papp = NULL);


template < class ARRAY >
bool file_put_array(const char * path, const ARRAY & a, ::aura::application * papp = NULL)
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
bool file_as_array(ARRAY & a, const char * path, ::aura::application * papp = NULL)
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


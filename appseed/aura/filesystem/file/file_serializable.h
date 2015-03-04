#pragma once


namespace file
{


   class input_stream;
   class output_stream;


   class CLASS_DECL_AURA serializable
   {
   public:


      virtual void write(output_stream & ostream) = 0;
      virtual void read(input_stream & istream) = 0;


   };


   namespace array
   {

      template < class ARRAY >
      void write(output_stream & ostream,const ARRAY & a)
      {
         ::count count = a.get_count();
         ostream.write_arbitrary(count);
         for(index index = 0; index < count; index++)
         {
            ostream << (serializable &) a.element_at(index);
         }
      }

      template < class ARRAY >
      void read(input_stream & istream,ARRAY & a)
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
      void write(output_stream & ostream,const ARRAY & a)
      {
         ::count count = a.get_count();
         ostream.write_arbitrary(count);
         for(index index = 0; index < count; index++)
         {
            ostream << *a.element_at(index);
         }
      }

      template < class ARRAY >
      void read(input_stream & istream,ARRAY & a)
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
      void write(output_stream & ostream,const type_map & m)
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
      void read(input_stream & istream,type_map & m)
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
::file::output_stream & operator << (::file::output_stream & os,const array < TYPE,ARG_TYPE,DEFCONSTRUCTOR > & a)
{
   ::file::array::write(os,a);
   return os;
}

template < class TYPE,class ARG_TYPE = const TYPE &,class DEFCONSTRUCTOR = ::constructor::def < TYPE > >
::file::input_stream & operator >> (::file::input_stream & is,array < TYPE,ARG_TYPE,DEFCONSTRUCTOR > & a)
{
   ::file::array::read(is,a);
   return is;
}





template<class TYPE,class ARG_TYPE = const TYPE &>
::file::output_stream & operator << (::file::output_stream & os,const raw_array < TYPE,ARG_TYPE> & a)
{
   ::file::array::write(os,a);
   return os;
}

template<class TYPE,class ARG_TYPE = const TYPE &>
::file::input_stream & operator >> (::file::input_stream & is,raw_array < TYPE,ARG_TYPE > & a)
{
   ::file::array::read(is,a);
   return is;
}


template < class TYPE,class ARRAY_TYPE = raw_ptr_array < TYPE * > >
::file::output_stream & operator << (::file::output_stream & os,const ptr_array < TYPE,ARRAY_TYPE> & a)
{
   ::file::ptra::write(os,a);
   return os;
}

template < class TYPE,class ARRAY_TYPE = raw_ptr_array < TYPE * > >
::file::input_stream & operator >> (::file::input_stream & is,ptr_array < TYPE,ARRAY_TYPE > & a)
{
   ::file::ptra::read(is,a);
   return is;
}



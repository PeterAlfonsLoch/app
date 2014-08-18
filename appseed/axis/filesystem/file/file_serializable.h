#pragma once


namespace file
{


   class input_stream;
   class output_stream;


   class CLASS_DECL_AXIS serializable :
      virtual public element
   {
   public:

      serializable();
      serializable(const serializable & s);
      #ifdef MOVE_SEMANTICS
      serializable(serializable && s);
      #endif


      virtual void write(output_stream & ostream) = 0;
      virtual void read(input_stream & istream) = 0;


   };


   template < class type_array >
   class serializable_array :
      virtual public type_array,
      virtual public serializable
   {
   public:


   serializable_array() { }

   serializable_array(serializable_array & a) :
      type_array(a)
   {

   }

   inline serializable_array & operator = (const serializable_array & a)
   {

      type_array::operator = (a);

      return *this;

   }

#if defined(MOVE_SEMANTICS)
   serializable_array(serializable_array && a) :
      type_array(a)
   {

   }

   inline serializable_array & operator = (serializable_array && a)
   {

      type_array::operator = (a);

      return *this;

   }

#endif

      virtual void write(output_stream & ostream);
      virtual void read(input_stream & istream);
      virtual void on_after_read();
   };

   template < class type_pointer_array >
   class byte_serializable_pointer_array :
      virtual public type_pointer_array,
      virtual public serializable
   {
   public:


      byte_serializable_pointer_array() { }

#if defined(MOVE_SEMANTICS)
      byte_serializable_pointer_array(byte_serializable_pointer_array && a) :
         type_pointer_array(a)
      {

      }

      inline byte_serializable_pointer_array & operator = (byte_serializable_pointer_array && a)
      {

         type_pointer_array::operator = (a);

         return *this;

      }

#endif

      virtual void write(output_stream & ostream);
      virtual void read(input_stream & istream);
      virtual void on_after_read();
   };

   template < class type_array >
   void serializable_array < type_array >::write(output_stream & ostream)
   {
      ::count count = this->get_count();
      ostream.write_arbitrary(count);
      for(index index = 0; index < count; index++)
      {
         ostream << this->element_at(index);
      }
   }

   template < class type_array >
   void serializable_array < type_array >::read(input_stream & istream)
   {
      ::count count;
      //istream >> count;
      istream.read_arbitrary(count);
      this->allocate(count);
      for(index index = 0; index < count; index++)
      {
         istream >> this->element_at(index);
      }
      on_after_read();
   }

   template < class type_pointer_array >
   void byte_serializable_pointer_array < type_pointer_array >::write(output_stream & ostream)
   {
      ::count count = this->get_count();
      ostream.write_arbitrary(count);
      for(index index = 0; index < count; index++)
      {
         ostream << *this->element_at(index);
      }
   }

   template < class type_pointer_array >
   void byte_serializable_pointer_array < type_pointer_array >::read(input_stream & istream)
   {
      ::count count;
      //istream >> count;
      istream.read_arbitrary(count);
      this->set_size_create(count);
      for(index index = 0; index < count; index++)
      {
         istream >> *this->element_at(index);
      }
      on_after_read();
   }

   template < class type_array >
   void serializable_array < type_array >::on_after_read()
   {
   }

   template < class type_pointer_array >
   void byte_serializable_pointer_array < type_pointer_array >::on_after_read()
   {
   }

   template < class type_map >
   class byte_serializable_map :
      virtual public type_map,
      virtual public serializable
   {
   public:


      byte_serializable_map(sp(::base::application) papp = NULL, ::count nBlockSize = 10);
      byte_serializable_map(const byte_serializable_map & map);


      virtual void write(output_stream & ostream);
      virtual void read(input_stream & istream);
      virtual void on_after_read();


      byte_serializable_map & operator = (const byte_serializable_map & map);

   };

   template < class type_map >
   byte_serializable_map < type_map >::byte_serializable_map(sp(::base::application) papp, ::count nBlockSize) :
      type_map(papp, nBlockSize)
   {
   }

   template < class type_map >
   byte_serializable_map < type_map >::byte_serializable_map(const byte_serializable_map & map) :
      type_map(dynamic_cast < const type_map & > (map))
   {
   }

   template < class type_map >
   void byte_serializable_map < type_map >::write(output_stream & ostream)
   {
      ::count count = this->get_count();
      ostream.write_arbitrary(count);
      typename type_map::pair * p = this->PGetFirstAssoc();
      for(index index = 0; index < count; index++)
      {
         ostream << p->m_element1;
         ostream << p->m_element2;
         p = this->PGetNextAssoc(p);
      }
   }

   template < class type_map >
   void byte_serializable_map < type_map >::read(input_stream & istream)
   {
      ::count count;
      istream.read_arbitrary(count);
      typename type_map::AXIS_KEY key;
      typename type_map::AXIS_VALUE value;
      for(index index = 0; index < count; index++)
      {
         istream >> key;
         istream >> value;
         this->set_at(key, value);
      }
      on_after_read();
   }

   template < class type_map >
   void byte_serializable_map < type_map >::on_after_read()
   {
   }

   template < class type_map >
   byte_serializable_map < type_map > & byte_serializable_map < type_map >::operator = (const byte_serializable_map & map)
   {

      if(this != &map)
      {

         type_map::m_nBlockSize = map.type_map::m_nBlockSize;
         type_map::operator = (map);

      }

      return *this;

   }


} // namespace file



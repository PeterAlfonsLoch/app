// Common/Buffer.h
// from 7-zip
#pragma once


template <class T>
class buffer :
   virtual public raw_array < T >
{
public:


   buffer()
   {
   
   }

   buffer(const buffer & buffer) :
      array(buffer)
   {
   
   }

   buffer(size_t size)
   {
   
      SetCapacity(size);

   }
   
   virtual ~buffer()
   {
   
   }

   operator T *()
   { 
   
      return get_data();

   }

   operator const T *() const
   { 
      
      return get_data();
   
   }


   size_t GetCapacity() const
   { 
      
      return  get_size();
   
   }

   void SetCapacity(size_t newCapacity)
   {

      allocate(newCapacity);

   }

   buffer & operator = (const buffer &buffer)
   {

      SetCapacity(buffer._capacity);
      
      if (buffer._capacity > 0)
      {
         memmove(_items, buffer._items, buffer._capacity * sizeof(T));
      }

      return *this;

   }


   bool operator == (const buffer < T > & b) const
   {

      if(GetCapacity() != b.GetCapacity())
         return false;

      for (size_t i = 0; i < GetCapacity(); i++)
         if (operator[](i) != b[i])
            return false;

      return true;

   }


   bool operator != (const buffer < T > & b) const
   {
      return !(*this == b);
   }

};



typedef CLASS_DECL_c buffer < char >      char_buffer;
typedef CLASS_DECL_c buffer < wchar_t >   wchar_buffer;
typedef CLASS_DECL_c buffer < byte >      byte_buffer;

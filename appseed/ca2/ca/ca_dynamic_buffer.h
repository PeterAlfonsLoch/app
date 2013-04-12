// Common/DynamicBuffer.h
#pragma once

namespace ca
{

   template <class T> class dynamic_buffer: public buffer<T>
   {
     void GrowLength(size_t size)
     {
       size_t delta;
       if (this->_capacity > 64)
         delta = this->_capacity / 4;
       else if (this->_capacity > 8)
         delta = 16;
       else
         delta = 4;
       delta = MyMax(delta, size);
       size_t newCap = this->_capacity + delta;
       if (newCap < delta)
         newCap = this->_capacity + size;
         buffer < T > ::SetCapacity(newCap);
     }
   public:
     dynamic_buffer(): buffer<T>() {};
     dynamic_buffer(const dynamic_buffer &buffer): ::ca::buffer<T>(buffer) {};
     dynamic_buffer(size_t size): buffer<T>(size) {};
     dynamic_buffer& operator=(const dynamic_buffer &buffer)
     {
       this->Free();
       if (buffer._capacity > 0)
       {
         this->SetCapacity(buffer._capacity);
         memmove(this->_items, buffer._items, buffer._capacity * sizeof(T));
       }
       return *this;
     }
     void EnsureCapacity(size_t capacity)
     {
       if (this->_capacity < capacity)
         GrowLength(capacity - this->_capacity);
     }
   };

   typedef dynamic_buffer < char >     char_dynamic_buffer;
   typedef dynamic_buffer < wchar_t > wchar_dynamic_buffer;
   typedef dynamic_buffer < byte >     byte_dynamic_buffer;

} // namespace ca

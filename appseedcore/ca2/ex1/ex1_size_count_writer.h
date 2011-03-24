#pragma once

namespace ex1
{


   class size_count_writer:
      virtual public writer
   {
   public:
      sp(writer)     _stream;
      uint64         _size;
      
      void SetStream(writer * stream)
      {
         _stream = stream; 
      }

      void Init()
      { 
         _size = 0; 
      }
      
      uint64 get_size() const
      { 
         return _size;
      }

      void write(const void *data, DWORD_PTR size, DWORD_PTR * processedSize);

   };


} // namespace ex1
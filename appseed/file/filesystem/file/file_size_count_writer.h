#pragma once


namespace file
{


   class size_count_writer:
      virtual public writer
   {
   public:
      buffer_sp     _stream;
      file_size         _size;

      void SetStream(writer * stream)
      {
         _stream = stream;
      }

      void Init()
      {
         _size = 0;
      }

      file_size get_size() const
      {
         return _size;
      }

      void write(const void *data, ::primitive::memory_size size, ::primitive::memory_size * processedSize);

   };


} // namespace file

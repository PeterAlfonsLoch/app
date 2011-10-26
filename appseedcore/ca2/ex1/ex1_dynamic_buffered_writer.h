#pragma once


namespace ex1
{


   class dynamic_buffered_writer:
      virtual public writer
   {
   public:


      byte_dynamic_buffer _buffer;
      size_t _size;


      dynamic_buffered_writer() :
      _size(0)
      {
      }

      void Init()
      {
         _size = 0;  
      }
      
      size_t GetSize() const
      {
         return _size; 
      }
      
      const byte *GetBuffer() const
      {
         return _buffer; 
      }

      void CopyToBuffer(byte_buffer &dest) const;
      
      byte *GetBufPtrForWriting(size_t addSize);
      
      void UpdateSize(size_t addSize)
      {
         _size += addSize; 
      }

      using ::ex1::writer::write;
      void write(const void *data, DWORD_PTR size, DWORD_PTR *processedSize);


   };

} // namespace ex1
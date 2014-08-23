#pragma once


namespace file
{


   class CLASS_DECL_AXIS stream_get_size :
      virtual public ::object
   {
   public:
      virtual int32_t GetSize(uint64_t * psize) const = 0;
   };

   enum e_seek
   {
      seek_begin     = 0x0,
      seek_current   = 0x1,
      seek_end       = 0x2,
      beg = seek_begin,
      cur = seek_current,
      end=seek_end
   };


   class CLASS_DECL_AXIS seekable :
      virtual public ::object
   {
   public:

      virtual void seek_to_begin();
      virtual file_position seek_to_end();


      virtual file_position seek_from_begin(file_position position);
      virtual file_position seek(file_offset offset, e_seek seekOrigin);
      virtual file_position get_position() const;

   };


} // namespace file



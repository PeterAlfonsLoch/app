// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{

   class limited_istream:
      public istream
   {
      istream *    _stream;
      uint64_t            _virtPos;
      uint64_t            _physPos;
      uint64_t            _size;
      uint64_t         _startOffset;

      uint64_t SeekToPhys()
      { 
         return _stream->seek((int_ptr) _physPos, seek_begin); 
      }
   public:
      void SetStream(istream *stream)
      { 
         _stream = stream; 
      }

      //HRESULT InitAndSeek(uint64_t startOffset, uint64_t size)
      uint64_t InitAndSeek(uint64_t startOffset, uint64_t size)
      {
         _startOffset = startOffset;
         _physPos = startOffset;
         _virtPos = 0;
         _size = size;
         return SeekToPhys();
      }

      ::primitive::memory_size read(void * data, ::primitive::memory_size size);
      file_position seek(file_offset offset, e_seek seekOrigin);

   };

   reader * create_limited_istream(istream *inStream, uint64_t pos, uint64_t size);


} // namespace file





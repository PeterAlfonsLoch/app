// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{

   class limited_writer:
      public writer
   {
      writer *    _stream;
      uint64_t      _size;
      bool        _overflow;
      bool        _overflowIsAllowed;
   public:
      void write(const void * data, ::primitive::memory_size size, ::primitive::memory_size * processedSize);
      void SetStream(writer * stream) { _stream = stream; }
      void ReleaseStream() 
      { 
         //_stream.Release(); 
      }
      void Init(uint64_t size, bool overflowIsAllowed = false)
      {
         _size = size;
         _overflow = false;
         _overflowIsAllowed = overflowIsAllowed;
      }
      bool IsFinishedOK() const { return (_size == 0 && !_overflow); }
      uint64_t GetRem() const { return _size; }
   };

} // namespace file

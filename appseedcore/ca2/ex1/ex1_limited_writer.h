// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace ex1
{

   class limited_writer:
      public writer
   {
      writer *    _stream;
      uint64      _size;
      bool        _overflow;
      bool        _overflowIsAllowed;
   public:
      void write(const void * data, DWORD_PTR size, DWORD_PTR * processedSize);
      void SetStream(writer * stream) { _stream = stream; }
      void ReleaseStream() 
      { 
         //_stream.Release(); 
      }
      void Init(uint64 size, bool overflowIsAllowed = false)
      {
         _size = size;
         _overflow = false;
         _overflowIsAllowed = overflowIsAllowed;
      }
      bool IsFinishedOK() const { return (_size == 0 && !_overflow); }
      uint64 GetRem() const { return _size; }
   };

} // namespace ex1
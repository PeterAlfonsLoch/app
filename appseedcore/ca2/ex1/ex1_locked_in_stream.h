// LockedStream.h
// at sector8J on afternoon of 13/01/2011 - Thursday
#pragma once


namespace ex1
{

   class locked_in_stream
   {
   public:

      
      sp(input_stream)     _stream;
      critical_section     _criticalSection;


      void Init(input_stream *stream)
      { 
         _stream = stream; 
      }
      
      DWORD_PTR read(uint64 startPos, void * data, DWORD_PTR size);

   };

   class locked_reader :
      virtual public ex1::reader
   {
   public:


      locked_in_stream *_lockedInStream;
      uint64 _pos;


      void Init(locked_in_stream *lockedInStream, uint64 startPos)
      {
         _lockedInStream = lockedInStream;
         _pos = startPos;
      }

      DWORD_PTR read(void *data, DWORD_PTR size);

   };

} // namespace ex1
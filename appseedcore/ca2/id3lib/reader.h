#pragma once

#include "globals.h" //has <stdlib.h> "sized_types.h"

class CLASS_DECL_ca ID3_Reader :
   virtual public ::radix::object
{
 public:
  typedef file_size size_type;
  typedef file_position pos_type;
  typedef file_offset off_type;
  
  /** close the reader.  Any further actions on the reader should fail.
   **/
  virtual void close() = 0;

  /** Return the beginning position in the reader */
  virtual file_position getBeg() { return static_cast<pos_type>(0); }

  /** Return the ending position in the reader */
  virtual file_position getEnd() { return static_cast<pos_type>(-1); }

  /** Return the current position in the reader */
  virtual file_position getCur() = 0;

  /** Set the value of the current position for reading.
   **/
  virtual file_position setCur(file_position pos) = 0;

  /**
   ** read a single character and advance the internal position.  Note that the
   ** interal position may advance more than one byte for a single character 
   ** read.  Returns END_OF_READER if there isn't a character to read.
   **/
  virtual bool read(char * pch) 
  {
    if (this->atEnd())
    { 
      return false; 
    }
    readChars(pch, 1);
    return true;
  }

  /**
   ** Return the next character to be read without advancing the internal 
   ** position.  Returns END_OF_READER if there isn't a character to read.
   **/
  virtual bool peek(char * pch) = 0;
  
  /** read up to \c len characters into buf and advance the internal position
   ** accordingly.  Returns the number of characters read into buf.  Note that
   ** the value returned may be less than the number of bytes that the internal
   ** position advances, due to multi-byte characters.
   **/
  virtual ::primitive::memory_size readChars(char buf[], ::primitive::memory_size len) = 0;
  
  /** Skip up to \c len chars in the stream and advance the internal position
   ** accordingly.  Returns the number of characters actually skipped (may be 
   ** less than requested).
   **/
  virtual ::primitive::memory_size skipChars(::primitive::memory_size len)
  {
    const ::primitive::memory_size::TYPE SIZE = 1024;
    char bytes[SIZE];
    ::primitive::memory_size remaining = len;
    while (!atEnd() && remaining > 0)
    {
      remaining -= readChars(bytes, (remaining < SIZE ? remaining : SIZE));
    }
    return len - remaining;
  }

  virtual ::primitive::memory_size remainingBytes()
  {
    pos_type end = getEnd(), cur = getCur();
    if (end == pos_type(-1))
    {
      return ::primitive::memory_size(-1);
    }
    
    if (end >= cur)
    {
      return (::primitive::memory_size)(end - cur);
    }
    
    return 0;
  }
  
  virtual bool atEnd() { return this->getCur() >= this->getEnd(); }
};



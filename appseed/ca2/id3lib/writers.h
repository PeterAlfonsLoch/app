//
//
// id3lib: a software library for creating and manipulating id3v1/v2 tags
// Copyright 1999, 2000  Scott Thomas Haug
// http://download.sourceforge.net/id3lib/
//
//

#pragma once

#include "writer.h"
#include "id3lib_streams.h"

class CLASS_DECL_ca ID3_FileWriter : 
   public ID3_Writer
{
   ex1::byte_output_stream _stream;
   pos_type  _beg;
protected:
   ex1::byte_output_stream & getWriter() const { return const_cast < ID3_FileWriter * > (this)->_stream; }
public:
   ID3_FileWriter(ex1::file & writer) : _stream(&writer), _beg((pos_type) _stream.get_position()) {}
   virtual ~ID3_FileWriter() {}

   virtual void close() {_stream.close();}
   virtual void flush() {_stream.Flush();}
  
   virtual int_type writeChar(char_type ch)
   {
      _stream << ch;
      return ch;
   }

  /** write up to \c len chars into buf and advance the internal position
   ** accordingly.  Returns the number of characters write into buf.
   **/
  virtual ::primitive::memory_size writeChars(const char buf[], ::primitive::memory_size len)
  { 
    _stream.write(buf, len);
    return len;
  }

  virtual ::primitive::memory_size writeChars(const char_type buf[], ::primitive::memory_size len)
  {
    _stream.write(reinterpret_cast<const char*>(buf), len);
    return len;
  }

  virtual file_position getBeg() { return _beg; }
  virtual file_position getCur() { return (file_position) _stream.get_position(); }
};

  
class CLASS_DECL_ca ID3_MemoryWriter : 
   public ID3_Writer
{
   const char_type * _beg;
         char_type * _cur;
   const char_type * _end;
protected:
   
   void setBuffer(char_type* buf, size_t size)
   {
      _beg = buf;
      _cur = buf;
      _end = buf + size;
   }

public:

   ID3_MemoryWriter()
   {
      this->setBuffer(NULL, 0);
   }
  
   ID3_MemoryWriter(char_type buf[], size_t size)
   {
      this->setBuffer(buf, size);
   }
  
   virtual ~ID3_MemoryWriter() {}
   virtual void close() {}
   virtual void flush() {}
    
   /** write up to \c len chars from buf and advance the internal position
   ** accordingly.  Returns the number of characters written from buf.
   **/
   virtual ::primitive::memory_size writeChars(const char buf[], ::primitive::memory_size len)
   { 
      return writeChars(reinterpret_cast<const char_type *>(buf), len);
   }

   virtual ::primitive::memory_size writeChars(const char_type buf[], ::primitive::memory_size len)
   {
      ::primitive::memory_size remaining = (::primitive::memory_size) (_end - _cur);
      ::primitive::memory_size size = (::primitive::memory_size) ((remaining > len) ? len : remaining);
      ::memcpy(_cur, buf, size);
      _cur += size;
      return size;
   }
    
   virtual file_position getCur() 
   { 
      return _cur - _beg; 
   }
    
   virtual file_position getBeg()
   {
      return _beg - _beg;
   }
    
   virtual file_position getEnd()
   {
      return _end - _beg;
   }
};


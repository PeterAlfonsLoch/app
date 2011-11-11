// -*- C++ -*-
// $Id: io_decorators.h,v 1.5 2002/07/02 22:10:51 t1mpy Exp $

// id3lib: a software library for creating and manipulating id3v1/v2 tags
// Copyright 1999, 2000  Scott Thomas Haug

// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
// License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

// The id3lib authors encourage improvements and optimisations to be sent to
// the id3lib coordinator.  Please see the README file for details on where to
// send such submissions.  See the AUTHORS file for a list of people who have
// contributed to id3lib.  See the ChangeLog file for a list of changes to
// id3lib.  These files are distributed with id3lib at
// http://download.sourceforge.net/id3lib/

#ifndef _ID3LIB_READER_DECORATORS_H_
#define _ID3LIB_READER_DECORATORS_H_

#include "readers.h"
#include "io_helpers.h"
#include "utils.h" // has <config.h> "id3lib_streams.h" "globals.h" "id3lib_strings.h"

namespace dami
{
  namespace io
  {
    /**
     * Set a window on the buffer.  Characters can only be read within this
     * window.
     */
    class CLASS_DECL_ca WindowedReader : public ID3_Reader
    {
      typedef ID3_Reader SUPER;

      ID3_Reader& _reader;
      pos_type _beg, _end;

      bool inWindow(pos_type cur)
      { return this->getBeg() <= cur && cur < this->getEnd(); }

     public:
      explicit WindowedReader(ID3_Reader& reader)
        : _reader(reader), _beg(reader.getBeg()), _end(reader.getEnd()) { ; }

      WindowedReader(ID3_Reader& reader, size_type size)
        : _reader(reader), _beg(reader.getBeg()), _end(reader.getEnd())
      { this->setWindow(this->getCur(), size); }

      WindowedReader(ID3_Reader& reader, pos_type beg, size_type size)
        : _reader(reader), _beg(reader.getBeg()), _end(reader.getEnd())
      { this->setWindow(beg, size); }

      void setWindow(pos_type beg, size_type size);

      file_position setBeg(file_position);
      file_position setCur(file_position cur)
      {
        return _reader.setCur(mid(this->getBeg(), cur, this->getEnd()));
      }
      file_position setEnd(file_position);

      file_position getCur() { return _reader.getCur(); }
      file_position getBeg() { return _beg; }
      file_position getEnd() { return _end; }

      bool inWindow() { return this->inWindow(this->getCur()); }

      bool read(char * pch);
      bool peek(char * pch);

      ::primitive::memory_size readChars(char buf[], ::primitive::memory_size len);

      void close() { ; }
    };

    class CLASS_DECL_ca CharReader : public ID3_Reader
    {
      typedef ID3_Reader SUPER;

     protected:
      ID3_Reader& _reader;

    public:

      CharReader(ID3_Reader& reader) : _reader(reader) { }
      virtual ~CharReader() { ; }

      /**
       * read \c len characters into the array \c buf.  Since the stream needs
       * might have been unsynced, this function copies the characters one at a
       * time.
       */
      ::primitive::memory_size readChars(char buf[], ::primitive::memory_size len);

      void close() { ; }
      bool peek(char * pch) { return _reader.peek(pch); }

      file_position getBeg() { return _reader.getBeg(); }
      file_position getCur() { return _reader.getCur(); }
      file_position getEnd() { return _reader.getEnd(); }

      file_position setCur(file_position cur) { return _reader.setCur(cur); }
    };


    class CLASS_DECL_ca LineFeedReader : public CharReader
    {
      typedef CharReader SUPER;

     public:
      LineFeedReader(ID3_Reader& reader) : SUPER(reader) { ; }
      bool read(char * pch);
    };

    class CLASS_DECL_ca UnsyncedReader : public CharReader
    {
      typedef CharReader SUPER;

     public:
      UnsyncedReader(ID3_Reader& reader) : SUPER(reader) { }
      bool read(char * pch);
    };

    class CLASS_DECL_ca CompressedReader : public ID3_MemoryReader
    {
      char * _uncompressed;
     public:
      CompressedReader(ID3_Reader& reader, ::primitive::memory_size newSize);
      virtual ~CompressedReader();
    };

    class CLASS_DECL_ca UnsyncedWriter : public ID3_Writer
    {
      typedef ID3_Writer SUPER;

      ID3_Writer& _writer;
      int_type _last;
      size_type _numSyncs;

     public:
      UnsyncedWriter(ID3_Writer& writer)
        : _writer(writer), _last('\0'), _numSyncs(0)
      { ; }

      size_type getNumSyncs() const { return _numSyncs; }
      int_type writeChar(char_type ch);
      void flush();

      /**
       * write \c len characters into the array \c buf.  Since the stream needs
       * might have been unsynced, this function copies the characters one at a
       * time.
       */
      ::primitive::memory_size writeChars(const char_type[], ::primitive::memory_size len);
      ::primitive::memory_size writeChars(const char buf[], ::primitive::memory_size len)
      {
        return this->writeChars(reinterpret_cast<const char_type *>(buf), len);
      }

      void close() { ; }

      file_position getBeg() { return _writer.getBeg(); }
      file_position getCur() { return _writer.getCur(); }
      file_position getEnd() { return _writer.getEnd(); }
    };

    class CompressedWriter : public ID3_Writer
    {
      typedef ID3_Writer SUPER;

      ID3_Writer& _writer;
      primitive::memory _data;
      size_type _origSize;
     public:

      explicit CompressedWriter(ID3_Writer& writer)
        : _writer(writer), _data(), _origSize(0)
      { ; }
      virtual ~CompressedWriter() { this->flush(); }

      size_type getOrigSize() const { return _origSize; }

      void flush();

      ::primitive::memory_size writeChars(const char_type buf[], ::primitive::memory_size len);
      ::primitive::memory_size writeChars(const char buf[], ::primitive::memory_size len)
      {
        return this->writeChars(reinterpret_cast<const char_type*>(buf), len);
      }

      file_position getCur() { return (file_position) _data.get_size(); }
      void close() { ; }
    };
  };
};

#endif /* _ID3LIB_READER_DECORATORS_H_ */


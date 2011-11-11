// $Id: io_helpers.cpp,v 1.13 2002/07/02 22:13:56 t1mpy Exp $

// id3lib: a C++ library for creating and manipulating id3v1/v2 tags
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

#include "StdAfx.h"

#include "io_decorators.h" //has "readers.h" "io_helpers.h" "utils.h"

using namespace dami;

string io::readstring(ID3_Reader& reader)
{
  string str;
  char ch;
  while (!reader.read(&ch))
  {
    if (ch == '\0')
    {
      break;
    }
    str += static_cast<char>(ch);
  }
  return str;
}

string io::readText(ID3_Reader& reader, size_t len)
{
  string str;
  const size_t SIZE = 1024;
  char buf[SIZE];
  size_t remaining = len;
  while (remaining > 0 && !reader.atEnd())
  {
    size_t numRead = reader.readChars(buf, min(remaining, SIZE));
    remaining -= numRead;
    str += string(reinterpret_cast<const char *>(buf), numRead);
  }
  return str;
}

namespace
{
  bool isNull(unsigned char ch1, unsigned char ch2)
  {
    return ch1 == '\0' && ch2 == '\0';
  }

  int isBOM(unsigned char ch1, unsigned char ch2)
  {
  // The following is taken from the following URL:
  // http://community.roxen.com/developers/idocs/rfc/rfc2781.html
  /* The Unicode Standard and ISO 10646 define the character "ZERO WIDTH
     NON-BREAKING SPACE" (0xFEFF), which is also known informally as
     "BYTE ORDER MARK" (abbreviated "BOM"). The latter name hints at a
     second possible usage of the character, in addition to its normal
     use as a genuine "ZERO WIDTH NON-BREAKING SPACE" within text. This
     usage, suggested by Unicode section 2.4 and ISO 10646 Annex F
     (informative), is to prepend a 0xFEFF character to a stream of
     Unicode characters as a "signature"; a receiver of such a serialized
     stream may then use the initial character both as a hint that the
     stream consists of Unicode characters and as a way to recognize the
     serialization order. In serialized UTF-16 prepended with such a
     signature, the order is big-endian if the first two octets are 0xFE
     followed by 0xFF; if they are 0xFF followed by 0xFE, the order is
     little-endian. Note that 0xFFFE is not a Unicode character,
     precisely to preserve the usefulness of 0xFEFF as a byte-order
     mark. */

    if (ch1 == 0xFE && ch2 == 0xFF)
    {
      return 1;
    }
    else if (ch1 == 0xFF && ch2 == 0xFE)
    {
      return -1;
    }
    return 0;
  }

  bool readTwoChars(ID3_Reader& reader,
                    char& ch1,
                    char& ch2)
  {
    if (reader.atEnd())
    {
      return false;
    }
    io::ExitTrigger et(reader);
    reader.read(&ch1);
    if (reader.atEnd())
    {
      return false;
    }
    et.release();
    reader.read(&ch2);
    return true;
  }
}

string io::readUnicodestring(ID3_Reader& reader)
{
  string unicode;
  char ch1, ch2;
  if (!readTwoChars(reader, ch1, ch2) || isNull(ch1, ch2))
  {
    return unicode;
  }
  int bom = isBOM(ch1, ch2);
  if (!bom)
  {
    unicode += static_cast<char>(ch1);
    unicode += static_cast<char>(ch2);
  }
  while (!reader.atEnd())
  {
    if (!readTwoChars(reader, ch1, ch2) || isNull(ch1, ch2))
    {
      break;
    }
    if (bom == -1)
    {
      unicode += static_cast<char>(ch2);
      unicode += static_cast<char>(ch1);
    }
    else
    {
      unicode += static_cast<char>(ch1);
      unicode += static_cast<char>(ch2);
    }
  }
  return unicode;
}

string io::readUnicodeText(ID3_Reader& reader, size_t len)
{
  gen::byte_stream_memory_file unicode(reader.get_app());
  wchar_t wch;
  char ch1, ch2;
  if (!readTwoChars(reader, ch1, ch2))
  {
    return "";
  }
  len -= 2;
  int bom = isBOM(ch1, ch2);
  if (!bom)
  {
     string str;
     str = ch1;
     str += ch2;
     str += readText(reader, len);
     return str;
  }
  else if (bom == -1)
  {
    for (size_t i = 0; i < len; i += 2)
    {
      if (!readTwoChars(reader, ch1, ch2))
      {
        break;
      }
      wch = static_cast < unsigned char > (ch1);
      wch |= static_cast < unsigned char > (ch2) << 8;

      unicode << wch;
    }
  }
  else
  {
    for (size_t i = 0; i < len; i += 2)
    {
      if (!readTwoChars(reader, ch1, ch2))
      {
        break;
      }
      wch = static_cast < unsigned char > (ch2);
      wch |= static_cast < unsigned char > (ch1) << 8;

      unicode << wch;
    }
  }
  unicode << L'\0';
  return gen::international::unicode_to_utf8((const wchar_t *) unicode.get_data());
}

primitive::memory io::readAllBinary(ID3_Reader& reader)
{
  return readBinary(reader, reader.remainingBytes());
}

primitive::memory io::readBinary(ID3_Reader& reader, size_t len)
{
  primitive::memory binary;


  size_t remaining = len;
  const size_t SIZE = 1024;
  char buf[SIZE];
  while (!reader.atEnd() && remaining > 0)
  {
    size_t numRead = reader.readChars(buf, min(remaining, SIZE));
    remaining -= numRead;
    binary.allocate_add_up(numRead);
    memcpy(&binary.get_data()[binary.get_size() - numRead], reinterpret_cast<char *>(buf), numRead);
  }

  return binary;
}

uint32 io::readLENumber(ID3_Reader& reader, size_t len)
{
  uint32 val = 0;
  unsigned char uch;
  for (size_t i = 0; i < len; i++)
  {
    if (reader.atEnd())
    {
      break;
    }
    reader.read((char *) &uch);
    val += (static_cast<uint32>(0xFF & uch) << (i * 8));
  }
  return val;
}

uint32 io::readBENumber(ID3_Reader& reader, size_t len)
{
  uint32 val = 0;
  unsigned char uch;
  for (size_t i = 0; i < len && !reader.atEnd(); ++i)
  {
     reader.read((char *) &uch);
    val *= 256; // 2^8
    val += static_cast<uint32>(0xFF & uch);
  }
  return val;
}

string io::readTrailingSpaces(ID3_Reader& reader, size_t len)
{
  io::WindowedReader wr(reader, len);
  string str;
  string spaces;
  char ch;
  while (!wr.read(&ch))
  {
    if (ch == '\0' || ch == ' ')
    {
      spaces += ch;
    }
    else
    {
      str += spaces + (char) ch;
      spaces.Empty();
    }
  }
  return str;
}

uint32 io::readUInt28(ID3_Reader& reader)
{
  uint32 val = 0;
  const unsigned short BITSUSED = 7;
  const uint32 MAXVAL = ID3LIB_MASK(BITSUSED * sizeof(uint32));
  unsigned char uch;
  // For each byte of the first 4 bytes in the string...
  for (size_t i = 0; i < sizeof(uint32); ++i)
  {
    if (reader.atEnd())
    {
      break;
    }
    reader.read((char *) &uch);
    // ...append the last 7 bits to the end of the temp integer...
    val = (val << BITSUSED) | static_cast<uint32>(uch) & ID3LIB_MASK(BITSUSED);
  }

  // We should always parse 4 characters
  return min(val, MAXVAL);
}

size_t io::writeBENumber(ID3_Writer& writer, uint32 val, size_t len)
{
  ID3_Writer::char_type bytes[sizeof(uint32)];
  ID3_Writer::size_type size = min(len, sizeof(uint32));
  renderNumber(bytes, val, (size_t) size);
  return writer.writeChars(bytes, (::primitive::memory_size) size);
}

size_t io::writeTrailingSpaces(ID3_Writer& writer, string buf, size_t len)
{
  ID3_Writer::pos_type beg = writer.getCur();
  ID3_Writer::size_type strLen = buf.get_length();
  ID3_Writer::size_type size = min((unsigned int)len, (unsigned int)strLen);
  writer.writeChars(buf, (::primitive::memory_size) size);
  for (; size < len; ++size)
  {
    writer.writeChar('\0');
  }
  return (size_t) (writer.getCur() - beg);
}

size_t io::writeUInt28(ID3_Writer& writer, uint32 val)
{
  uchar data[sizeof(uint32)];
  const unsigned short BITSUSED = 7;
  const uint32 MAXVAL = ID3LIB_MASK(BITSUSED * sizeof(uint32));
  val = min(val, MAXVAL);
  // This loop renders the value to the character buffer in reverse order, as
  // it is easy to extract the last 7 bits of an integer.  This is why the
  // loop shifts the value of the integer by 7 bits for each iteration.
  for (size_t i = 0; i < sizeof(uint32); ++i)
  {
    // Extract the last BITSUSED bits from val and put it in its appropriate
    // place in the data buffer
    data[sizeof(uint32) - i - 1] = static_cast<uchar>(val & ID3LIB_MASK(BITSUSED));

    // The last BITSUSED bits were extracted from the val.  So shift it to the
    // right by that many bits for the next iteration
    val >>= BITSUSED;
  }

  // Should always to 4 bytes
  return writer.writeChars(data, sizeof(uint32));
}

size_t io::writestring(ID3_Writer& writer, const stringa & data)
{
  size_t size = writeText(writer, data);
  if(size == 0)
  {
   writer.writeChar('\0');
  }
  return size + 1;
}

size_t io::writeText(ID3_Writer& writer, const stringa & data)
{
  ID3_Writer::pos_type beg = writer.getCur();
  for(int i = 0; i < data.get_count(); i++)
  {
      writer.writeChars(data[i], data[i].get_length());
      writer.writeChar('\0');
  }
  return (size_t) (writer.getCur() - beg);
}

/*
size_t io::writeUnicodestring(ID3_Writer& writer, const stringa & data, bool bom)
{
  size_t size = writeUnicodeText(writer, data, bom);
  if(size == 0)
  {
   wchar_t null = NULL_UNICODE;
   writer.writeChars((const unsigned char*) &null, 2);
  }
  return size + 2;
}

size_t io::writeUnicodeText(ID3_Writer& writer, const stringa & data, bool bom)
{
  ID3_Writer::pos_type beg = writer.getCur();
  size_t size = (data.get_length() / 2) * 2;
  if (size == 0)
  {
    return 0;
  }
  if (bom)
  {
    // write the BOM: 0xFEFF
    wchar_t BOM = 0xFEFF;
    writer.writeChars((const unsigned char*) &BOM, 2);
    for (size_t i = 0; i < size; i += 2)
    {
      wchar_t ch = (data[i] << 8) | data[i+1];
      writer.writeChars((const unsigned char*) &ch, 2);
    }
  }
  return writer.getCur() - beg;
}

*/

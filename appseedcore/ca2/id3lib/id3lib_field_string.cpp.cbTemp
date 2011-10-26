// $Id: field_string_ascii.cpp,v 1.29 2003/03/02 14:23:58 t1mpy Exp $

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
#include "field_impl.h"
#include "utils.h" // has <config.h> "id3lib_streams.h" "globals.h" "id3lib_strings.h"
#include "io_helpers.h"

using namespace dami;

/** \fn ID3_Field& ID3_Field::operator=(const char* data)
 ** \brief Shortcut for the Set operator.
 ** \param data The string to assign to this field
 ** \sa Set(const char*)
 **/

/** \brief Copies the supplied string to the field.
 ** You may dispose of the source string after a call to this method.
 ** \code
 **   myFrame.GetField(ID3FN_TEXT)->Set("ID3Lib is very cool!");
 ** \endcode
 **/
size_t ID3_FieldImpl::Set(const char* data)
{
  size_t len = 0;
  if ((this->GetType() == ID3FTY_TEXTstring) && data)
  {
    string str(data);
    len = this->SetText_i(str);
  }
  return len;
}


string ID3_FieldImpl::GetText() const
{
  string data;
  if (this->GetType() == ID3FTY_TEXTstring)
  {
    data = m_stra[0];
  }
  return data;
}

string ID3_FieldImpl::GetTextItem(size_t index) const
{
  string data;
  if (this->GetType() == ID3FTY_TEXTstring &&
      this->GetEncoding() == ID3TE_ASCII)
  {
    const char* raw = this->GetRawTextItem(index);
    if (raw != NULL)
    {
      data = raw;
    }
  }
  return data;
}



size_t ID3_FieldImpl::SetText_i(string data)
{
  this->clear();
  //if (_fixed_size > 0)
  {
    //_text = getFixed(data, _fixed_size);
  }
  //else
  {
     m_stra.remove_all();
     if(data.has_char())
     {
        m_stra.add(data);
     }
  }
  ID3D_NOTICE( "SetText_i: text = \"" << _text << "\"" );
  _changed = true;


  return m_stra.get_size() <= 0 ? 0 : m_stra[0].get_length();
}

size_t ID3_FieldImpl::SetText(string data)
{
  size_t len = 0;
  if (this->GetType() == ID3FTY_TEXTstring)
  {
    len = this->SetText_i(data);
  }
  return len;
}


/** For fields which support this feature, adds a string to the list of
 ** strings currently in the field.
 **
 ** This is useful for using id3v2 frames such as the involved people list,
 ** composer, and part of setp.  You can use the GetNumTextItems() method to
 ** find out how many such items are in a list.
 **
 ** \code
 **   myFrame.GetField(ID3FN_TEXT)->add("this is a test");
 ** \endcode
 **
 ** \param string The string to add to the field
 **/
size_t ID3_FieldImpl::AddText_i(string data)
{
  size_t len = 0;  // how much of str we copied into this field (max is strLen)
  ID3D_NOTICE ("ID3_FieldImpl::AddText_i: Adding \"" << data << "\"" );
  if (this->GetNumTextItems() == 0)
  {
    // there aren't any text items in the field so just assign the string to
    // the field
    len = this->SetText_i(data);
  }
  else
  {

    // ASSERT(_fixed_size == 0)
    //_text += '\0';
    if (this->GetEncoding() == ID3TE_UNICODE)
    {
      //_text += '\0';
    }
    m_stra.add(data);
    len = data.get_length();
  }

  return len;
}

size_t ID3_FieldImpl::AddText(string data)
{
  size_t len = 0;
  if (this->GetType() == ID3FTY_TEXTstring)
  {
    len = this->AddText_i(data);
  }
  return len;
}

size_t ID3_FieldImpl::add(const char* data)
{
  size_t len = 0;
  if (this->GetType() == ID3FTY_TEXTstring)
  {
    string str(data);
    len = this->AddText_i(str);
  }
  return len;
}

string ID3_FieldImpl::GetRawText() const
{
   if(m_stra.get_count() == 0)
      return "";
  return m_stra[0];
}

string ID3_FieldImpl::GetRawTextItem(size_t index) const
{
  string text;
  if(index < this->GetNumTextItems())
  {
    text = m_stra[index];
  }
  return text;
}

namespace
{
  string readEncodedText(ID3_Reader& reader, size_t len, ID3_TextEnc enc)
  {
    if (enc == ID3TE_ASCII)
    {
      return io::readText(reader, len);
    }
    return io::readUnicodeText(reader, len);
  }

  string readEncodedstring(ID3_Reader& reader, ID3_TextEnc enc)
  {
    if (enc == ID3TE_ASCII)
    {
      return io::readstring(reader);
    }
    return io::readUnicodestring(reader);
  }

  size_t writeEncodedText(ID3_Writer& writer, const stringa & data, ID3_TextEnc enc)
  {
     UNREFERENCED_PARAMETER(enc);
    //if (enc == ID3TE_ASCII)
    {
      return io::writeText(writer, data);
    }
    //return io::writeUnicodeText(writer, data);
  }

  size_t writeEncodedstring(ID3_Writer& writer, const stringa & data, ID3_TextEnc enc)
  {
     UNREFERENCED_PARAMETER(enc);
    //if (enc == ID3TE_ASCII)
    {
      return io::writestring(writer, data);
    }
    //return io::writeUnicodestring(writer, data);
  }
}

bool ID3_FieldImpl::ParseText(ID3_Reader& reader)
{
  ID3D_NOTICE( "ID3_Field::ParseText(): reader.getBeg() = " << reader.getBeg() );
  ID3D_NOTICE( "ID3_Field::ParseText(): reader.getCur() = " << reader.getCur() );
  ID3D_NOTICE( "ID3_Field::ParseText(): reader.getEnd() = " << reader.getEnd() );
  this->clear();

  ID3_TextEnc enc = this->GetEncoding();
  size_t fixed_size = this->size();
  if (fixed_size)
  {
    ID3D_NOTICE( "ID3_Field::ParseText(): fixed size string" );
    // The string is of fixed length
    string text = readEncodedText(reader, fixed_size, enc);
    this->SetText(text);
    ID3D_NOTICE( "ID3_Field::ParseText(): fixed size string = " << text );
  }
  else if (_flags & ID3FF_LIST)
  {
    ID3D_NOTICE( "ID3_Field::ParseText(): text list" );
    // lists are always the last field in a frame.  parse all remaining
    // characters in the reader
    while (!reader.atEnd())
    {
      string text = readEncodedstring(reader, enc);
      this->AddText(text);
      ID3D_NOTICE( "ID3_Field::ParseText(): adding string = " << text );
    }
  }
  else if (_flags & ID3FF_CSTR)
  {
    ID3D_NOTICE( "ID3_Field::ParseText(): null terminated string" );
    string text = readEncodedstring(reader, enc);
    this->SetText(text);
    ID3D_NOTICE( "ID3_Field::ParseText(): null terminated string = " << text );
  }
  else
  {
    ID3D_NOTICE( "ID3_Field::ParseText(): last field string" );
    string text = readEncodedText(reader, reader.remainingBytes(), enc);
    // not null terminated.
    this->AddText(text);
    ID3D_NOTICE( "ID3_Field::ParseText(): last field string = " << text );
  }

  _changed = false;
  return true;
}

void ID3_FieldImpl::RenderText(ID3_Writer& writer) const
{
  ID3_TextEnc enc = this->GetEncoding();

  if (_flags & ID3FF_CSTR)
  {
    writeEncodedstring(writer, m_stra, enc);
  }
  else
  {
    writeEncodedText(writer, m_stra, enc);
  }
  _changed = false;
};

/** Returns the number of items in a text list.
 **
 ** \code
 **   size_t numItems = myFrame.GetField(ID3FN_UNICODE)->GetNumItems();
 ** \endcode
 **
 ** \return The number of items in a text list.
 **/
size_t ID3_FieldImpl::GetNumTextItems() const
{
  return m_stra.get_count();
}


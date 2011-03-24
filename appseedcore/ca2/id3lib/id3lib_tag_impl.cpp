// $Id: tag_impl.cpp,v 1.13 2002/09/21 17:23:32 t1mpy Exp $

// id3lib: a C++ library for creating and manipulating id3v1/v2 tags
// Copyright 1999, 2000  Scott Thomas Haug
// Copyright 2002 Thijmen Klok (thijmen@id3lib.org)

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
#if defined HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#include "tag_impl.h" //has <stdio.h> "tag.h" "header_tag.h" "frame.h" "field.h" "spec.h" "id3lib_strings.h" "utils.h"
//#include "io_helpers.h"
#include "io_strings.h"

using namespace dami;

size_t ID3_TagImpl::IsV2Tag(ID3_Reader& reader)
{
  io::ExitTrigger et(reader);
  size_t tagSize = 0;
  string id = io::readText(reader, ID3_TagHeader::ID_SIZE);
  string ver = io::readText(reader, 2);
  char flags;
  reader.read(&flags);
  string size = io::readText(reader, 4);

  if (id == ID3_TagHeader::ID &&
      (uchar) ver [0] < 0xFF   &&      (uchar) ver [1] < 0xFF   &&
      (uchar) size[0] < 0x80   &&      (uchar) size[1] < 0x80   &&
      (uchar) size[2] < 0x80   &&      (uchar) size[3] < 0x80)
  {
    io::stringReader sr(size);
    tagSize = io::readUInt28(sr) + ID3_TagHeader::SIZE;
  }
  else if (id != ID3_TagHeader::ID)
  {
    // clog << "*** IsV2Tag: Not an id3v2 tag header" << endl;
  }
  else if ((uchar)ver[0] >= 0xFF)
  {
    // clog << "*** IsV2Tag: Major offset" << endl;
  }
  else if ((uchar)ver[1] >= 0xFF)
  {
    // clog << "*** ISV2Tag: Minor offset" << endl;
  }
  else if ((uchar)size[0] >= 0x80)
  {
    // clog << "*** ISV2Tag: 1st size offset" << endl;
  }
  else if ((uchar)size[1] >= 0x80)
  {
    // clog << "*** ISV2Tag: 2nd size offset" << endl;
  }
  else if ((uchar)size[2] >= 0x80)
  {
    // clog << "*** ISV2Tag: 3rd size offset" << endl;
  }
  else if ((uchar)size[3] >= 0x80)
  {
    // clog << "*** ISV2Tag: 4th size offset" << endl;
  }
  else
  {
    // clog << "*** shouldn't get here!" << endl;
  }

  return tagSize;
}

ID3_TagImpl::ID3_TagImpl(const char *name)
  : _frames(),
    _cursor(0),
    _file_name(),
    _file_size(0),
    _prepended_bytes(0),
    _appended_bytes(0),
    _is_file_writable(false),
    _mp3_info(NULL) // need to do this before this->clear()
{
  this->clear();
  if (name)
  {
    this->Link(name);
  }
}

ID3_TagImpl::ID3_TagImpl(const ID3_Tag &tag)
  : _frames(),
    _cursor(0),
    _file_name(),
    _file_size(0),
    _prepended_bytes(0),
    _appended_bytes(0),
    _is_file_writable(false),
    _mp3_info(NULL) // need to do this before this->clear()
{
  *this = tag;
}

ID3_TagImpl::~ID3_TagImpl()
{
  this->clear();
}

void ID3_TagImpl::clear()
{
  _frames.remove_all();
  _cursor = 0;
  _is_padded = true;

  _hdr.clear();
  _hdr.SetSpec(ID3V2_LATEST);

  _tags_to_parse.clear();
  if (_mp3_info)
    delete _mp3_info; // Also deletes _mp3_header

  _mp3_info = NULL;

  _changed = true;
}


void ID3_TagImpl::AddFrame(const ID3_Frame& frame)
{
  this->AddFrame(&frame);
}

void ID3_TagImpl::AddFrame(const ID3_Frame* frame)
{
  if (frame)
  {
    ID3_Frame* frm = new ID3_Frame(*frame);
    this->AttachFrame(frm);
  }
}

bool ID3_TagImpl::AttachFrame(ID3_Frame *frame)
{

  if (NULL == frame)
  {
    // log this
    return false;
    //ID3_THROW(ID3E_NoData);
  }

  _frames.add(frame);
  _cursor = 0;

  _changed = true;
  return true;
}


ID3_Frame* ID3_TagImpl::RemoveFrame(const ID3_Frame *frame)
{
   ID3_Frame *frm = NULL;

   if(_frames.remove((ID3_Frame *) frame) > 0)
   {
      _cursor = 0;
      _changed = true;
   }

   return frm;
}


bool ID3_TagImpl::HasChanged() const
{
   bool changed = _changed;

   if(!changed)
   {
      for(index fi = 0; fi != _frames.get_count(); ++fi)
      {
         if(_frames.ptr_at(fi) != NULL)
         {
            changed = _frames[fi].HasChanged();
         }

         if (changed)
         {
            break;
         }
    }
  }

  return changed;
}

bool ID3_TagImpl::SetSpec(ID3_V2Spec spec)
{
  bool changed = _hdr.SetSpec(spec);
  _changed = _changed || changed;
  return changed;
}

ID3_V2Spec ID3_TagImpl::GetSpec() const
{
  return _hdr.GetSpec();
}

bool ID3_TagImpl::SetUnsync(bool b)
{
  bool changed = _hdr.SetUnsync(b);
  _changed = changed || _changed;
  return changed;
}

bool ID3_TagImpl::SetExtended(bool ext)
{
  bool changed = _hdr.SetExtended(ext);
  _changed = changed || _changed;
  return changed;
}

bool ID3_TagImpl::SetExperimental(bool exp)
{
  bool changed = _hdr.SetExperimental(exp);
  _changed = changed || _changed;
  return changed;
}

bool ID3_TagImpl::GetUnsync() const
{
  return _hdr.GetUnsync();
}

bool ID3_TagImpl::GetExtended() const
{
  return _hdr.GetExtended();
}

bool ID3_TagImpl::GetExperimental() const
{
  return _hdr.GetExperimental();
}

bool ID3_TagImpl::GetFooter() const
{
  return _hdr.GetFooter();
}

size_t ID3_TagImpl::GetExtendedBytes() const
{
  if (this->GetExtended())
    if (this->GetSpec() == ID3V2_4_0)
      return 6; //minimal ID3v2.4 ext header size
    else if (this->GetSpec() == ID3V2_3_0)
      return 10; //minimal ID3v2.3 ext header size
    else
      return 0; //not implemented
  else
    return 0;;
}

bool ID3_TagImpl::SetPadding(bool pad)
{
  bool changed = (_is_padded != pad);
  _changed = changed || _changed;
  if (changed)
  {
    _is_padded = pad;
  }

  return changed;
}


ID3_TagImpl & ID3_TagImpl::operator=( const ID3_Tag &rTag )
{
  clear();

  SetUnsync(rTag.GetUnsync());
  SetExtended(rTag.GetExtendedHeader());
  SetExperimental(rTag.GetExperimental());

  for(index i = 0; i < rTag.NumFrames(); i++)
  {
    AttachFrame(new ID3_Frame(((ID3_Tag &) rTag).frames()[i]));
  }
  return *this;
}

size_t ID3_GetDataSize(const ID3_TagImpl& tag)
{
  return tag.GetFileSize() - tag.GetPrependedBytes() - tag.GetAppendedBytes();
}


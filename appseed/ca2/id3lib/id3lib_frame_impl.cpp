// $Id: frame_impl.cpp,v 1.9 2002/07/02 22:12:38 t1mpy Exp $

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

#include "tag.h"
#include "frame_impl.h"
#include "field_impl.h"
#include "frame_def.h"
#include "field_def.h"

ID3_FrameImpl::ID3_FrameImpl(ID3_FrameID id) :
m_bChanged(false),
   m_bita(),
   m_fields(),
   m_uchEncryptionId('\0'),
   m_uchGroupingId('\0')
{
   this->SetSpec(ID3V2_LATEST);
   this->SetID(id);
}

ID3_FrameImpl::ID3_FrameImpl(const ID3_FrameHeader &hdr)
   : m_bChanged(false),
   m_bita(),
   m_fields(),
   m_header(hdr),
   m_uchEncryptionId('\0'),
   m_uchGroupingId('\0')
{
   this->_InitFields();
}

ID3_FrameImpl::ID3_FrameImpl(const ID3_Frame& frame)
   : m_bChanged(false),
   m_bita(),
   m_fields(),
   m_uchEncryptionId('\0'),
   m_uchGroupingId('\0')
{
   *this = frame;
}

ID3_FrameImpl::~ID3_FrameImpl()
{
   clear();
}

bool ID3_FrameImpl::_ClearFields()
{
   m_fields.remove_all();
   m_bita.set_size(0);

   m_bChanged = true;
   return true;
}

void ID3_FrameImpl::clear()
{
   _ClearFields();
   m_header.clear();
   m_uchEncryptionId   = '\0';
   m_uchGroupingId     = '\0';
}

void ID3_FrameImpl::_InitFields()
{
   const ID3_FrameDef* info = m_header.GetFrameDef();
   if (NULL == info)
   {
      // log this
      ID3_Field* fld = new ID3_FieldImpl(ID3_FieldDef::DEFAULT[0]);
      m_fields.add(fld);
      m_bita.set_bit(fld->GetID());
   }
   else
   {

      for (size_t i = 0; info->aeFieldDefs[i]._id != ID3FN_NOFIELD; ++i)
      {
         ID3_Field* fld = new ID3_FieldImpl(info->aeFieldDefs[i]);
         m_fields.add(fld);
         m_bita.set_bit(fld->GetID());
      }

      m_bChanged = true;
   }
}

bool ID3_FrameImpl::SetID(ID3_FrameID id)
{
   bool changed = (this->GetID() != id);
   if (changed)
   {
      this->_SetID(id);
      m_bChanged = true;
   }
   return changed;
}

bool ID3_FrameImpl::_SetID(ID3_FrameID id)
{
   bool changed = this->_ClearFields();
   changed = m_header.SetFrameID(id) || changed;
   this->_InitFields();
   return changed;
}

bool ID3_FrameImpl::SetSpec(ID3_V2Spec spec)
{
   return m_header.SetSpec(spec);
}

ID3_V2Spec ID3_FrameImpl::GetSpec() const
{
   return m_header.GetSpec();
}

ID3_Field & ID3_FrameImpl::GetField(ID3_FieldID fieldName) const
{
   if(Contains(fieldName))
   {
      for (int i = 0; i < m_fields.get_count(); i++)
      {
         if(m_fields[i].GetID() == fieldName)
         {
            return ((ID3_FrameImpl *) this)->m_fields[i];
         }
      }
   }
   return *((ID3_Field *) NULL);
}

size_t ID3_FrameImpl::NumFields() const
{
   return m_fields.get_count();
}

size_t ID3_FrameImpl::size()
{
   size_t bytesUsed = m_header.size();

   if (this->GetEncryptionID())
   {
      bytesUsed++;
   }

   if (this->GetGroupingID())
   {
      bytesUsed++;
   }

   ID3_TextEnc enc = ID3TE_ASCII;
   for (int i = 0; i < m_fields.get_count(); i++)
   {
      if(m_fields[i].InScope(GetSpec()))
      {
         if(m_fields[i].GetID() == ID3FN_TEXTENC)
         {
            enc = (ID3_TextEnc) m_fields[i].get();
         }
         else
         {
            m_fields[i].SetEncoding(enc);
         }
         bytesUsed += m_fields[i].BinSize();
      }
   }

   return bytesUsed;
}


bool ID3_FrameImpl::HasChanged() const
{
   bool changed = m_bChanged;

   for(int i = 0; i < m_fields.get_count(); i)
   {
      if(m_fields[i].InScope(GetSpec()))
      {
         changed = m_fields[i].HasChanged();
      }
   }

   return changed;
}

ID3_FrameImpl & ID3_FrameImpl::operator=( const ID3_Frame &rFrame )
{

   m_fields = rFrame.fields();

   SetID(rFrame.GetID());
   SetEncryptionID(rFrame.GetEncryptionID());
   SetGroupingID(rFrame.GetGroupingID());
   SetCompression(rFrame.GetCompression());
   SetSpec(rFrame.GetSpec());
   m_bChanged = false;

   return *this;
}

const char* ID3_FrameImpl::GetDescription(ID3_FrameID id)
{
   ID3_FrameDef* myFrameDef = ID3_FindFrameDef(id);
   if (myFrameDef != NULL)
   {
      return myFrameDef->sDescription;
   }
   return NULL;
}

const char* ID3_FrameImpl::GetDescription() const
{
   const ID3_FrameDef* def = m_header.GetFrameDef();
   if (def)
   {
      return def->sDescription;
   }
   return NULL;
}


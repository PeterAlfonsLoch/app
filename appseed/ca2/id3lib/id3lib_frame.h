//
//
//
// id3lib: a C++ library for creating and manipulating id3v1/v2 tags
// Copyright 1999, 2000  Scott Thomas Haug
// http://download.sourceforge.net/id3lib/
//
//
//

#pragma once

#include "globals.h" //has <stdlib.h> "sized_types.h"

class ID3_Field;
class ID3_Fields;
class ID3_FrameImpl;
class ID3_Reader;
class ID3_Writer;

class CLASS_DECL_ca ID3_Frame
{
  ID3_FrameImpl * _impl;
public:


  ID3_Frame(ID3_FrameID id = ID3FID_NOFRAME);
  ID3_Frame(const ID3_Frame&);

  virtual ~ID3_Frame();
  
  void        clear();

  bool        SetID(ID3_FrameID id);
  ID3_FrameID GetID() const;
  
  ID3_Field & GetField(ID3_FieldID name) const;

  size_t      NumFields() const;
  
  const char* GetDescription() const;
  static const char* GetDescription(ID3_FrameID);

  const char* GetTextID() const;

  ID3_Frame&  operator=(const ID3_Frame &);
  bool        HasChanged() const;
  bool        Parse(ID3_Reader&);
  void        to(ID3_Writer&) const;
  size_t      size();
  bool        Contains(ID3_FieldID fld) const;
  bool        SetSpec(ID3_V2Spec);
  ID3_V2Spec  GetSpec() const;

  bool        SetCompression(bool b);
  bool        GetCompression() const;
  size_t      GetDataSize() const;

  bool        SetEncryptionID(uchar id);
  uchar       GetEncryptionID() const;
  
  bool        SetGroupingID(uchar id);
  uchar       GetGroupingID() const;

  ID3_Field &           field(ID3_FieldID name) const;
  ID3_Field &           field(size_t) const;
  ID3_Fields &          fields();
  const ID3_Fields &    fields() const;

};

class CLASS_DECL_ca ID3_Frames :
   virtual public array_del_ptr < ID3_Frame >
{
public:
};
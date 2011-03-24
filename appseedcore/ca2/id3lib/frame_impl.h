//
//
// id3lib: a C++ library for creating and manipulating id3v1/v2 tags
// Copyright 1999, 2000  Scott Thomas Haug
// Copyright 2002 Thijmen Klok (thijmen@id3lib.org)
// http://download.sourceforge.net/id3lib/
//
//

#pragma once


#include "id3lib_frame.h"
#include "header_frame.h"

class ID3_FrameImpl
{
private:
   
   
   mutable bool       m_bChanged;          // frame bChanged since last parse/to?
   bit_array          m_bita;              // which fields are present?
   ID3_Fields         m_fields;
   ID3_FrameHeader    m_header;            // 
   uchar              m_uchEncryptionId;   // encryption id
   uchar              m_uchGroupingId;     // grouping id


public:
   
   
   ID3_FrameImpl(ID3_FrameID id = ID3FID_NOFRAME);
   ID3_FrameImpl(const ID3_FrameHeader&);
   ID3_FrameImpl(const ID3_Frame&);
   virtual ~ID3_FrameImpl();
  

   void        clear();

   bool        SetID(ID3_FrameID id);
   ID3_FrameID GetID() const { return m_header.GetFrameID(); }
  
   ID3_Field & GetField(ID3_FieldID name) const;

   size_t      NumFields() const;
  
   const char* GetDescription() const;
   static const char* GetDescription(ID3_FrameID);

   const char* GetTextID() const { return m_header.GetTextID(); }

   ID3_FrameImpl&  operator=(const ID3_Frame &);
   bool        HasChanged() const;
   bool        Parse(ID3_Reader&);
   void        to(ID3_Writer&) const;
   size_t      size();
   bool        Contains(ID3_FieldID fld) const { return m_bita.get_bit(fld); }
   bool        SetSpec(ID3_V2Spec);
   ID3_V2Spec  GetSpec() const;

   /** Sets the compression flag within the frame.  When the compression flag is
   ** is set, compression will be attempted.  However, the frame might not
   ** actually be compressed after it is rendered if the "compressed" data is
   ** no smaller than the "uncompressed" data.
   **/
   bool        SetCompression(bool b)  { return m_header.SetCompression(b); }
   /** Returns whether or not the compression flag is set.  After parsing a tag,
   ** this will indicate whether or not the frame was compressed.  After
   ** rendering a tag, however, it does not actually indicate if the frame is
   ** compressed rendering.  It only indicates whether or not compression was
   ** attempted.  A frame will not be compressed, even whent the compression
   ** flag is set, if the "compressed" data is no smaller than the
   ** "uncompressed" data.
   **/
   bool        GetCompression() const  { return m_header.GetCompression(); }
   size_t      GetDataSize() const { return m_header.GetDataSize(); }

   bool SetEncryptionID(uchar uchEncryptionId)
   {
      bool bChanged = uchEncryptionId != m_uchEncryptionId;
      m_uchEncryptionId = uchEncryptionId;
      m_bChanged = m_bChanged || bChanged;
      m_header.SetEncryption(true);
      return bChanged;
   }
   uchar GetEncryptionID() const { return m_uchEncryptionId; }
   bool SetGroupingID(uchar uchGroupingId)
   {
      bool bChanged = uchGroupingId != m_uchGroupingId;
      m_uchGroupingId = uchGroupingId;
      m_bChanged = m_bChanged || bChanged;
      m_header.SetGrouping(true);
      return bChanged;
   }
   uchar GetGroupingID() const { return m_uchGroupingId; }

   ID3_Fields & fields() { return m_fields; }
   const ID3_Fields & fields() const { return m_fields; }
  
protected:
   bool        _SetID(ID3_FrameID);
   bool        _ClearFields();
   void        _InitFields();
   void        _InitFieldBits();
   void        _UpdateFieldDeps();

};

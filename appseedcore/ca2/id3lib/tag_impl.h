//
//
// id3lib: a software library for creating and manipulating id3v1/v2 tags
// Copyright 1999, 2000  Scott Thomas Haug
// Copyright 2002 Thijmen Klok (thijmen@id3lib.org)
// http://download.sourceforge.net/id3lib/
//
//

#pragma once

#include "tag.h" // has frame.h, field.h
#include "header_tag.h"
#include "mp3_header.h" //has io_decorators.h

class ID3_Reader;
class ID3_Writer;

namespace dami
{
  namespace id3
  {
    namespace v1
    {
      bool parse(ID3_TagImpl&, ID3_Reader&);
      void to(ID3_Writer&, const ID3_TagImpl&);
    };
    namespace v2
    {
      bool parse(ID3_TagImpl& tag, ID3_Reader& rdr);
      void to(ID3_Writer& writer, const ID3_TagImpl& tag);
    };
  };
  namespace lyr3
  {
    namespace v1
    {
      bool parse(ID3_TagImpl&, ID3_Reader&);
    };
    namespace v2
    {
      bool parse(ID3_TagImpl&, ID3_Reader&);
    };
  };
  namespace mm
  {
    bool parse(ID3_TagImpl&, ID3_Reader&);
  };
};

class ID3_TagImpl
{
private:


  ID3_TagHeader _hdr;          // information relevant to the tag header
  bool       _is_padded;       // add padding to tags?

  ID3_Frames     _frames;

  mutable int   _cursor;  // which frame in list are we at
  mutable bool       _changed; // has tag changed since last parse or to?

  // file-related member variables
  string _file_name;       // name of the file we are linked to
  size_t     _file_size;       // the size of the file (without any tag(s))
  size_t     _prepended_bytes; // number of tag bytes at start of file
  size_t     _appended_bytes;  // number of tag bytes at end of file
  bool       _is_file_writable;// is the associated file (via Link) writable?
  ID3_Flags  _tags_to_parse;   // which tag types should attempt to be parsed
  ID3_Flags  _file_tags;       // which tag types does the file contain
  Mp3Info    *_mp3_info;   // class used to retrieve _mp3_header


public:

   ID3_TagImpl(const char *name = NULL);
   ID3_TagImpl(const ID3_Tag &tag);
   virtual ~ID3_TagImpl();

   void       clear();
   bool       HasChanged() const;
   void       SetChanged(bool b) { _changed = b; }
   size_t     size() const;

   bool       SetUnsync(bool);
   bool       SetExtended(bool);
   bool       SetExperimental(bool);
   bool       SetPadding(bool);

   bool       GetUnsync() const;
   bool       GetExtended() const;
   bool       GetExperimental() const;
   bool       GetFooter() const;

   size_t     GetExtendedBytes() const;

   void       AddFrame(const ID3_Frame&);
   void       AddFrame(const ID3_Frame*);
   bool       AttachFrame(ID3_Frame*);
   ID3_Frame* RemoveFrame(const ID3_Frame *);

   size_t     Link(const char *fileInfo, flags_t = (flags_t) ID3TT_ALL);
   size_t     Link(ID3_Reader &reader, flags_t = (flags_t) ID3TT_ALL);
   flags_t    Update(flags_t = (flags_t) ID3TT_ALL);
   flags_t    Strip(flags_t = (flags_t) ID3TT_ALL);

   size_t     GetPrependedBytes() const { return _prepended_bytes; }
   size_t     GetAppendedBytes() const { return _appended_bytes; }
   size_t     GetFileSize() const { return _file_size; }
   string GetFileName() const { return _file_name; }

   ID3_Frame* Find(ID3_FrameID id) const;
   ID3_Frame* Find(ID3_FrameID id, ID3_FieldID fld, uint32 data) const;
   ID3_Frame* Find(ID3_FrameID id, ID3_FieldID fld, string) const;
   //  ID3_Frame* Find(ID3_FrameID id, ID3_FieldID fld, string) const;

   count     NumFrames() const { return _frames.get_count(); }
   ID3_TagImpl&   operator=( const ID3_Tag & );

   bool       HasTagType(ID3_TagType tt) const { return _file_tags.test((ID3_Flags::TYPE) tt); }
   ID3_V2Spec GetSpec() const;
   bool       SetSpec(ID3_V2Spec);

   static size_t IsV2Tag(ID3_Reader&);

   const Mp3_Headerinfo* GetMp3HeaderInfo() const { if (_mp3_info) return _mp3_info->GetMp3HeaderInfo(); else return NULL; }
   
   ID3_Frames & frames() { return _frames; }
   const ID3_Frames & frames() const { return _frames; }

   /* Deprecated! */
   void       AddNewFrame(ID3_Frame* f) { this->AttachFrame(f); }
   size_t     Link(const char *fileInfo, bool parseID3v1, bool parseLyrics3);
   void       SetCompression(bool) { ; }
   void       AddFrames(const ID3_Frame *, size_t);
   bool       HasLyrics() const { return this->HasTagType(ID3TT_LYRICS); }
   bool       HasV2Tag()  const { return this->HasTagType(ID3TT_ID3V2); }
   bool       HasV1Tag()  const { return this->HasTagType(ID3TT_ID3V1); }
   size_t     PaddingSize(size_t) const;

protected:
   index Find(const ID3_Frame *) const;

   void       RenderExtHeader(uchar *);

   void       ParseFile();
   void       ParseReader(ID3_Reader &reader);

};

size_t     ID3_GetDataSize(const ID3_TagImpl&);

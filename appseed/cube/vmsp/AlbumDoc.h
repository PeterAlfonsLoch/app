#pragma once

class CLASS_DECL_CA2_CUBE AlbumDoc : public ::userbase::document
{
public:


   AlbumDoc(::ca::application * papp);
   virtual ~AlbumDoc();


   virtual BOOL on_new_document();


   
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

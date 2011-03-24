#pragma once

class CLASS_DECL_CA2_CUBE CVmsTextDoc : public ::userbase::document
{
public:
   CVmsTextDoc(::ca::application * papp); 

   virtual BOOL on_new_document();

   virtual ~CVmsTextDoc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

#pragma once

class CLASS_DECL_CA2_CUBE OptionsDoc : 
   public ::filemanager::document
{
public:


   OptionsDoc(::ca::application * papp);
   virtual ~OptionsDoc();


   virtual BOOL on_new_document();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};


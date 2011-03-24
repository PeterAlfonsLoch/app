#pragma once

class CLASS_DECL_CA2_CUBE AudioSpectrumDoc :
   public ::userbase::document
{
public:
   
   
   AudioSpectrumDoc(::ca::application * papp); 
   virtual ~AudioSpectrumDoc();


   virtual BOOL on_new_document();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

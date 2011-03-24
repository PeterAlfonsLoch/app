#pragma once

class CLASS_DECL_CA2_CUBE syllomatter_document :
   public form_document
{
public:
   syllomatter_document(::ca::application * papp);

   DECL_GEN_VSIGNAL(data_on_after_change)

   bool open_commit_message();

   virtual BOOL on_new_document();
   virtual ~syllomatter_document();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   bool on_open_document(var varFile);

};


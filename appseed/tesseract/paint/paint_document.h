#pragma once

class CLASS_DECL_CA2_TESSERACT paint_document :
   public ::userbase::document
{
public:
   paint_document(::ca::application * papp);

   virtual ::paint::document * get_document();
   DECL_GEN_VSIGNAL(data_on_after_change)


   paint::document   m_document;


   virtual BOOL on_new_document();
public:
   virtual ~paint_document();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   bool on_open_document(var varFile);

};


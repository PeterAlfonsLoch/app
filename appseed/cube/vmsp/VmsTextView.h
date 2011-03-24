#pragma once

class CLASS_DECL_CA2_CUBE CVmsTextView : public ::userbase::edit_plain_text_view
{
protected:
   CVmsTextView(::ca::application * papp);           
   virtual void OnDraw(::ca::graphics * pgraphics);

   virtual ~CVmsTextView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};


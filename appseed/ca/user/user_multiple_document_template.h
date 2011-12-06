#pragma once

// MDI support (zero or more documents)
class CLASS_DECL_ca multiple_document_template : 
   virtual public document_template
{
public:
   multiple_document_template(::ca::application * papp, const char * pszMatter, ::ca::type_info pDocClass, ::ca::type_info pFrameClass, ::ca::type_info pViewClass);

   virtual ~multiple_document_template();
   virtual void load_template();
   virtual void add_document(document * pDoc);
   virtual void remove_document(document * pDoc);
   virtual count get_document_count() const;
   virtual document * get_document(index index) const;
   virtual void request(::ca::create_context * pcreatecontext);
   virtual void set_default_title(document * pdocument);

#ifdef _DEBUG
   virtual void dump(dump_context&) const;
   virtual void assert_valid() const;
#endif //_DEBUG

protected:  // standard implementation
   comparable_array < document * > m_docptra;          // open documents of this type
   UINT m_nUntitledCount;   // start at 0, for "Document1" title
};

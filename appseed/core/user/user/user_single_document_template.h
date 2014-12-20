#pragma once


namespace user
{


   class CLASS_DECL_CORE single_document_template :
      virtual public impact_system
   {
   public:


      sp(::aura::document) m_pdocument;


      single_document_template(::aura::application * papp, const char * pszMatter, sp(type) pDocClass, sp(type) pFrameClass, sp(type) pViewClass);
      virtual ~single_document_template();

      virtual void add_document(::aura::document * pDoc);
      virtual void remove_document(::aura::document * pDoc);
      virtual ::count get_document_count() const;
      virtual ::aura::document * get_document(index index = 0) const;
      virtual void request_create(sp(::create) pcreatecontext);
      virtual void set_default_title(::aura::document * pdocument);

      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;



   };



} // namespace user







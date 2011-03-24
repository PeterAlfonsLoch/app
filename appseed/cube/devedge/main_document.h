#pragma once

class CLASS_DECL_CA2_CUBE MainDoc :
   public ::userbase::document
{
public:
   MainDoc(::ca::application * papp);

   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);

   gen::memory_file *      m_pmemfile;
   ex1::filesp *         m_pfile;
   
public:

   public:
//   virtual void Serialize(CArchive& ar);   // overridden for document i/o
   protected:
   virtual BOOL on_new_document();

public:
   virtual ~MainDoc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};

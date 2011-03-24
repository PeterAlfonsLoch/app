#pragma once

class _declspec(dllexport) main_document :
   public ::userbase::document
{
public:
   main_document(::ca::application * papp);

   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);

   gen::memory_file         m_memfile;
   ex1::filesp           m_file;
   
   
   DECL_GEN_VSIGNAL(data_on_after_change);

   virtual BOOL on_new_document();

   virtual ~main_document();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};


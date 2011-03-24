#pragma once

namespace devedge
{

class solution_view;

class CLASS_DECL_CA2_CUBE solution_document :
   public ::userbase::document
{
public:
   solution_document(::ca::application * papp);           

   virtual bool on_open_document(var varFile);
   virtual BOOL on_save_document(const char * lpszPathName);

   ex1::filesp           m_file;
   ex1::filesp           m_fileSave;
   int               m_iBranch;
   solution_view *   m_pview;
   xml::node         m_node;

   void reload();

   xml::node * node_get_projects();


   array_app_alloc < devedge::project, devedge::project & > m_projecta;

   
   
public:

   DECL_GEN_SIGNAL(_001OnUpdateFileNew)
   DECL_GEN_SIGNAL(_001OnUpdateFileSave)
   DECL_GEN_SIGNAL(_001OnUpdateFilePut)
   DECL_GEN_SIGNAL(_001OnUpdateEditCut)
   DECL_GEN_SIGNAL(_001OnUpdateEditCopy)
   DECL_GEN_SIGNAL(_001OnUpdateEditPaste)
   DECL_GEN_SIGNAL(_001OnFileNew)
   DECL_GEN_SIGNAL(_001OnFileSave)
   DECL_GEN_SIGNAL(_001OnFilePut)
   DECL_GEN_SIGNAL(_001OnEditCut)
   DECL_GEN_SIGNAL(_001OnEditCopy)
   DECL_GEN_SIGNAL(_001OnEditPaste)

   void Put();
   void FtpPut(const char * lpcszLocal, const char * lpcszRemote);

   public:
//   virtual void Serialize(CArchive& ar);   
   protected:
   virtual BOOL on_new_document();

public:
   virtual ~solution_document();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

protected:
   ()
};

} // namespace devedge
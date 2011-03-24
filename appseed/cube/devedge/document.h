#pragma once

namespace devedge
{

   class view;

   class CLASS_DECL_CA2_CUBE document :
      public ::userbase::document
   {
   public:
      document(::ca::application * papp);           

      virtual bool on_open_document(var varFile);
      virtual BOOL on_save_document(const char * lpszPathName);

      ex1::filesp          m_file;
      ex1::filesp          m_fileSave;
      int                  m_iBranch;
      view *               m_pview;


      view * get_edit_view();

      void reload();
   
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
      virtual ~document();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };


} // namespace devedge
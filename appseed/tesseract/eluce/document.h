#pragma once

namespace eluce
{

   class CLASS_DECL_CA2_TESSERACT document:
      public ::userbase::document
   {
   public:


      visual::dib_sp      m_spdib;


      
      document(::ca::application * papp);

      virtual BOOL on_new_document();

   public:
      virtual ~document();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      bool on_open_document(var varFile);

      BOOL on_save_document(const char * lpszPathName);

      DECL_GEN_SIGNAL(_001OnGoToPrevious)
      DECL_GEN_SIGNAL(_001OnGoToNext)
      DECL_GEN_SIGNAL(_001OnFileNewPaste)
      DECL_GEN_SIGNAL(_001OnUpdateFileSaveAs)
      DECL_GEN_SIGNAL(_001OnFileSaveAs)


   };

} // namespace eluce 
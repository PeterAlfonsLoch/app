#pragma once


namespace fs
{


   class CLASS_DECL_ca2 document :
      public ::userbase::document
   {
   public:


      string                                    m_strFolder;
      ::fs::set                                 m_fsset;


      document(::ca::applicationsp papp);
      virtual ~document();

      sp(document)                                get_document();


   //#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   //#endif

      bool file_manager_browse(const char * pszFolder);

      inline ::fs::set & set()
      {


         return m_fsset;


      }

   };


} // namespace filemanager


#pragma once


namespace fs
{


   class CLASS_DECL_ca document :
      virtual public ::userbase::document
   {
   public:


      data *         m_pfsdata;
      string         m_strFolder;


      document(::ca::application * papp);
      virtual ~document();

      document * get_document();
      virtual data *       get_fs_data();


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool file_manager_browse(const char * pszFolder);

   };


} // namespace filemanager


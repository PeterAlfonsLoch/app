#pragma once


namespace userfs
{


   class CLASS_DECL_CORE document :
      virtual public ::user::document
   {
   public:


      string                                    m_strFolder;

      sp(::fs::set)                             m_fsset;

      ::file::listing                           m_straRootPath;

      ::file::listing                           m_straPath;


      document(::aura::application * papp);
      virtual ~document();

      ::user::document *                                get_document();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual bool browse(const char * pszDir, ::action::context actioncontext);

      inline sp(::fs::set) get_fs_data()
      {


         return m_fsset;


      }

   };


} // namespace userfs


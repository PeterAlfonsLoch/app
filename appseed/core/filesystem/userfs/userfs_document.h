#pragma once


namespace userfs
{


   class CLASS_DECL_CORE document :
      virtual public ::user::document
   {
   public:


      string                                    m_strFolder;
      sp(::fs::set)                             m_fsset;


      document(sp(::base::application) papp);
      virtual ~document();

      sp(::user::document)                                get_document();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      bool browse(const char * pszFolder, ::action::context actioncontext);

      inline sp(::fs::set) get_fs_data()
      {


         return m_fsset;


      }

   };


} // namespace userfs


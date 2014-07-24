#pragma once


namespace userfs
{


   class CLASS_DECL_CORE document :
      virtual public ::user::document
   {
   public:


      string                                    m_strFolder;
      ::fs::set                                 m_fsset;


      document(sp(::base::application) papp);
      virtual ~document();

      sp(::user::document)                                get_document();


   //#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   //#endif

      bool file_manager_browse(const char * pszFolder, ::action::context actioncontext);

      inline ::fs::set & set()
      {


         return m_fsset;


      }

   };


} // namespace userfs


//#include "framework.h"


namespace userfs
{


   document::document(::aura::application * papp) :
      object(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {

      m_fsset = canew(::fs::set(papp));

      //m_fsset.m_p->m_pcontainerbase = this;

   }

   document::~document()
   {
   }

   void document::assert_valid() const
   {
      ::aura::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::aura::document::dump(dumpcontext);
   }

   bool document::browse(const char * pszFolder, ::action::context actioncontext)
   {

      {
         synch_lock sl(get_fs_data()->data_mutex());
         m_strFolder = pszFolder;
      }

      if(m_straRootPath.is_empty())
      {

         ::file::patha patha;
         ::file::patha straTitle;
         get_fs_data()->root_ones(patha,straTitle);
         {
            synch_lock sl(get_fs_data()->data_mutex());
            m_straRootPath=patha;
            m_straRootTitle=straTitle;
         }

      }

      if(strlen(pszFolder) == 0)
      {
         synch_lock sl(get_fs_data()->data_mutex());
         m_straPath = m_straRootPath;

         m_straTitle = m_straRootTitle;

         m_iaSize.set_size(m_straPath.get_count());

         m_baDir.set_size(m_straPath.get_count());

         for(index i = 0; i < m_straPath.get_count(); i++)
         {
            m_iaSize[i] = 0;
            m_baDir[i] = true;
         }

      }
      else
      {
         ::file::patha patha;
         ::file::patha straTitle;
         int64_array iaSize;
         bool_array baDir;
         //get_fs_data()->ls(pszFolder,&m_straPath,&m_straTitle,&m_iaSize, &m_baDir);
         get_fs_data()->ls(pszFolder,&patha,&straTitle,&iaSize,&baDir);
         {
            synch_lock sl(get_fs_data()->data_mutex());
            m_straPath = patha;
            m_straTitle = straTitle;
            m_iaSize = iaSize;
            m_baDir = baDir;

         }
      }

      update_hint uh;

      uh.set_type(update_hint::type_synchronize_path);
      uh.m_strPath = pszFolder;
      uh.m_actioncontext = ::action::source::sync(actioncontext);

      update_all_views(NULL, 0, &uh);

      return true;

   }



} // namespace userfs




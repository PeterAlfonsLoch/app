#include "framework.h"


namespace userfs
{


   document::document(sp(::base::application) papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::user::document(papp)
   {

      m_fsset = canew(::fs::set(papp));

   }

   document::~document()
   {
   }

   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }

   bool document::browse(const char * pszFolder, ::action::context actioncontext)
   {
      
      m_strFolder = pszFolder;

      m_straPath.remove_all();
      m_straTitle.remove_all();
      m_iaSize.remove_all();
      m_baDir.remove_all();

      if(m_straRootPath.is_empty())
      {
         
         get_fs_data()->root_ones(m_straRootPath,m_straRootTitle);

      }

      if(strlen(pszFolder) == 0)
      {

         m_straPath = m_straRootPath;

         m_straTitle = m_straRootTitle;

         m_iaSize.set_size(m_straPath.get_count());

         for(index i = 0; i < m_straPath.get_count(); i++)
         {
            m_baDir.add(true);
         }

      }
      else
      {
         stringa straPath;
         stringa straTitle;
         int64_array iaSize;
         bool_array baDir;
         //get_fs_data()->ls(pszFolder,&m_straPath,&m_straTitle,&m_iaSize, &m_baDir);
         get_fs_data()->ls(pszFolder,&straPath,&straTitle,&iaSize,&baDir);
         m_straPath = straPath;
         m_straTitle = straTitle;
         m_iaSize = iaSize;
         m_baDir = baDir;
      }




      //m_straPath.trim_right("/\\");
      //m_straTitle.trim_right("/\\");



      update_hint uh;

      uh.set_type(update_hint::type_synchronize_path);
      uh.m_strPath = pszFolder;
      uh.m_actioncontext = ::action::source::sync(actioncontext);

      update_all_views(NULL, 0, &uh);

      return true;

   }



} // namespace userfs




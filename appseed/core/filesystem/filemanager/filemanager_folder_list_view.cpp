//#include "framework.h"
//#include "framework.h"




namespace filemanager
{

   folder_list_view::folder_list_view(::aura::application * papp):
      object(papp),
      simple_list_view(papp)
   {
         m_bRecursive = true;
      }

   folder_list_view::~folder_list_view()
   {
   }


   void folder_list_view::Initialize(::database::id  datakey,bool bRecursive)
   {
      m_bRecursive = bRecursive;
      if(bRecursive)
      {
         SetDataInterface(new folder_list_data(get_app()));
         sp(folder_list_data) pdata = m_plistdata.cast <folder_list_data > ();
         pdata->m_dataid = datakey;
         pdata->initialize_data_client(Application.simpledb().get_data_server());
      }
      else
      {
         SetDataInterface(new databaseuser::data_key_list_data(get_app()));
         sp(databaseuser::data_key_list_data) pdata = m_plistdata.cast  < ::databaseuser::data_key_list_data >();
         pdata->m_dataid = datakey;
         pdata->initialize_data_client(Application.simpledb().get_data_server());
      }
   }

   void folder_list_view::_001InsertColumns()
   {

      ::user::list_column column;

      column.m_iWidth               = 400;
      column.m_iSubItem             = 0;
      _001AddColumn(column);

      if(m_bRecursive)
      {
         column.m_iWidth               = 80;
         column.m_iSubItem             = 0;
         _001AddColumn(column);
      }

   }

   bool folder_list_view::add_unique(const stringa & stra)
   {
      if(m_bRecursive)
         throw "incorrect usage of this class object";
      if(stra.get_size() == 0)
         return true;

      sp(databaseuser::data_key_list_data) pdata = m_plistdata.cast <databaseuser::data_key_list_data >();

      if(!pdata->add_unique(stra))
         return false;

      _001OnUpdateItemCount();

      return true;

   }


   bool folder_list_view::add_unique(const stringa & stra,bool_array & baRecursive)
   {
      if(!m_bRecursive)
         throw "incorrect usage of this class object";
      if(stra.get_size() == 0)
         return true;
      sp(folder_list_data) pdata = m_plistdata.cast <folder_list_data> ();
      if(!pdata->add_unique(stra,baRecursive))
         return false;
      _001OnUpdateItemCount();

      return true;

   }


   bool folder_list_view::remove(const stringa & stra)
   {
      
      if(stra.get_size() == 0)
         return true;

      if(m_bRecursive)
      {
         
         sp(folder_list_data) pdata = m_plistdata.cast <folder_list_data >();

         if(!pdata->remove(stra))
            return false;

      }
      else
      {
         
         sp(databaseuser::data_key_list_data) pdata = m_psimplelistdata.cast <databaseuser::data_key_list_data > ();

         if(!pdata->remove(stra))
            return false;

      }

      _001OnUpdateItemCount();

      return true;

   }


   void folder_list_view::GetSel(stringa & stra)
   {
      
      if(m_bRecursive)
      {
         
         sp(folder_list_data) pdata = m_plistdata.cast <folder_list_data >();
         pdata->GetSel(this,stra);

      }
      else
      {
         
         sp(databaseuser::data_key_list_data) pdata = m_psimplelistdata.cast <databaseuser::data_key_list_data >();
         pdata->GetSel(this,stra);

      }

   }

} // namespace filemanager
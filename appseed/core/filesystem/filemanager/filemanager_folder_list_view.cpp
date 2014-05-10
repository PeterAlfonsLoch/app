#include "framework.h"


folder_list_view::folder_list_view(sp(::base::application) papp) :
   element(papp),
   ::filemanager::data_interface(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form(papp),
   ::user::form_list(papp),
   simple_list_view(papp)
{
   ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
   m_bRecursive = true;
}

folder_list_view::~folder_list_view()
{
}


void folder_list_view::Initialize(::database::id  datakey, bool bRecursive)
{
   m_bRecursive = bRecursive;
   if(bRecursive)
   {
      SetDataInterface(new filemanager::folder_list_data(get_app()));
      filemanager::folder_list_data * pdata = dynamic_cast < filemanager::folder_list_data * > (m_pdata);
      pdata->m_dataid = datakey;
      pdata->initialize_data_client(Application.simpledb().get_data_server());
   }
   else
   {
      SetDataInterface(new databaseuser::data_key_list_data(get_app()));
      databaseuser::data_key_list_data* pdata = dynamic_cast < databaseuser::data_key_list_data * > (m_pdata);
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
   databaseuser::data_key_list_data* pdata = dynamic_cast < databaseuser::data_key_list_data * > (m_pdata);
   if(!pdata->add_unique(stra))
      return false;
   _001OnUpdateItemCount();
   return true;
}


bool folder_list_view::add_unique(const stringa & stra, bool_array & baRecursive)
{
   if(!m_bRecursive)
      throw "incorrect usage of this class object";
   if(stra.get_size() == 0)
      return true;
   filemanager::folder_list_data * pdata = dynamic_cast < filemanager::folder_list_data * > (m_pdata);
   if(!pdata->add_unique(stra, baRecursive))
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
      filemanager::folder_list_data * pdata = dynamic_cast < filemanager::folder_list_data * > (m_pdata);
      if(!pdata->remove(stra))
         return false;
   }
   else
   {
      databaseuser::data_key_list_data* pdata = dynamic_cast < databaseuser::data_key_list_data * > (m_pdata);
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
      filemanager::folder_list_data * pdata = dynamic_cast < filemanager::folder_list_data * > (m_pdata);
      pdata->GetSel(this, stra);
   }
   else
   {
      databaseuser::data_key_list_data* pdata = dynamic_cast < databaseuser::data_key_list_data * > (m_pdata);
      pdata->GetSel(this, stra);
   }
}

#pragma once

#include "guibase/data_key_list_data.h"

class  CLASS_DECL_CORE folder_list_view :
   virtual public SimpleListView,
   virtual public FileManagerViewInterface
{
public:
   folder_list_view(application * papp);
public:
   virtual ~folder_list_view(void);

   void _001InsertColumns();

   bool add_unique(const AStrArray & stra);
   bool remove(const AStrArray & stra);

   data_key_list_data m_data;
public:
   void Initialize(data_id  datakey);
};

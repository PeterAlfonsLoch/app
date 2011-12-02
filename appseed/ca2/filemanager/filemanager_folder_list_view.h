#pragma once

class  CLASS_DECL_ca folder_list_view :
   virtual public simple_list_view,
   virtual public FileManagerViewInterface
{
public:


   bool m_bRecursive;

   bool                             m_bRecursiveColumn;


   folder_list_view(::ax::application * papp);
   virtual ~folder_list_view(void);


   void Initialize(::database::id  datakey, bool bRecursive);

   void _001InsertColumns();

   bool add_unique(const stringa & stra);
   bool add_unique(const stringa & stra, bool_array & baRecursive);
   bool remove(const stringa & stra);


   void GetSel(stringa & stra);


};

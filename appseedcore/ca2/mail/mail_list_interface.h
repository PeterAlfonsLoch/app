#pragma once

namespace mail
{

   class CLASS_DECL_ca list_interface :
      virtual public ::user::list
   {
   public:
      list_interface(::ca::application * appp);
      virtual ~list_interface();

      account * m_paccount;

      class CLASS_DECL_ca data :
         virtual public ::user::list_data
      {
      public:

         list_interface * m_plist;
         stringa   m_straId;


         data(::ca::application * papp);

         void update();

         virtual bool _001GetItemText(
            ::user::list * plist,
            string &str,
            INT_PTR iItem,
            INT_PTR iSubItem, 
            INT_PTR iListItem);

         virtual INT_PTR _001GetItemCount();

      };

      data * m_pdata;

      virtual void   _001InsertColumns();

      virtual bool _001OnUpdateItemCount(DWORD dwFlags = 0);

      


   };

} // namespace mail
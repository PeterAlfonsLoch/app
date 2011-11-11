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

         virtual void _001GetItemText(::user::list_item * pitem);

         virtual INT_PTR _001GetItemCount();

      };

      data * m_pdata;

      virtual void   _001InsertColumns();

      virtual bool _001OnUpdateItemCount(DWORD dwFlags = 0);

      


   };

} // namespace mail
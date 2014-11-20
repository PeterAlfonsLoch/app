#pragma once


namespace usermail
{


   class CLASS_DECL_CORE list_interface :
      virtual public ::user::list
   {
   public:

      class CLASS_DECL_CORE data :
         virtual public ::user::list_data
      {
      public:

         list_interface * m_plist;
         stringa   m_straId;


         data(::aura::application * papp);

         void update();

         virtual void _001GetItemText(::user::list_item * pitem);

         virtual int_ptr _001GetItemCount();

      };


      data * m_pdata;

      account * m_paccount;


      list_interface(::aura::application * papp);
      virtual ~list_interface();

      virtual void   _001InsertColumns();

      virtual bool _001OnUpdateItemCount(uint32_t dwFlags = 0);


   };


} // namespace usermail




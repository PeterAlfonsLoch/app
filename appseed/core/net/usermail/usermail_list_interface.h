#pragma once


namespace usermail
{


   class CLASS_DECL_CORE list_interface :
      virtual public ::user::list
   {
   public:
      list_interface(sp(::axis::application) appp);
      virtual ~list_interface();

      account * m_paccount;

      class CLASS_DECL_CORE data :
         virtual public ::user::list_data
      {
      public:

         list_interface * m_plist;
         stringa   m_straId;


         data(sp(::axis::application) papp);

         void update();

         virtual void _001GetItemText(::user::list_item * pitem);

         virtual int_ptr _001GetItemCount();

      };

      data * m_pdata;

      virtual void   _001InsertColumns();

      virtual bool _001OnUpdateItemCount(uint32_t dwFlags = 0);


   };


} // namespace usermail




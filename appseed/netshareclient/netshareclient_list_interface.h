#pragma once


namespace netshareclient
{

   class CLASS_DECL_CA2_NETSHARECLIENT list_interface :
      virtual public ::user::list
   {
   public:


      ::fontopus::user *    m_pprofile;



      list_interface(::ca::application * appp);
      virtual ~list_interface();


      class CLASS_DECL_CA2_NETSHARECLIENT data :
         public ::user::list_data
      {
      public:

         list_interface *     m_plist;
         stringa              m_straId;
         var                  m_varCache;
         int                  m_iCachePage;
         int                  m_iCachePageSize;
         int                  m_iMessageCount;


         data(::ca::application * papp);
         virtual ~data();

         void update();

         virtual bool _001GetItemText(
            ::user::list * plist,
	         string &str,
	         INT_PTR iItem,
	         INT_PTR iSubItem, 
	         INT_PTR iListItem);

         bool get_record(int iItem, var & var);

         virtual INT_PTR _001GetItemCount();

      };

      data * m_pdata;

      virtual void	_001InsertColumns();

      virtual bool _001OnUpdateItemCount(DWORD dwFlags = 0);

      
      var get_selected_message();

   };

} // namespace netshareclient

namespace user
{


   list_view::list_view(::aura::application * papp) :
      object(papp),
      ::user::scroll_view(papp),
      ::user::list(papp)
   {

   }


   list_view::~list_view()
   {

   }


   void list_view::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::scroll_view::install_message_handling(pdispatch);
      ::user::list::install_message_handling(pdispatch);

   }


   //void list::_001OnInitialUpdate(signal_details * pobj)
   //{

   //   scroll_view::_001OnInitialUpdate(pobj);

   //   //_001UpdateColumns();

   //}


} // namespace user





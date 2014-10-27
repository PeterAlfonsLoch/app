#pragma once


namespace userex
{


   class CLASS_DECL_CORE weekday_list_view:
      virtual public ::simple_list_view
   {
   public:


      weekday_list_view(sp(::aura::application) papp);
      virtual ~weekday_list_view();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001GetItemText(::user::list_item * pitem);
      virtual count _001GetItemCount();
      virtual void _001InsertColumns();

      virtual void _001OnSelectionChange();


      int_array get_weekday();
      void set_weekday(const int_array & iaWeekday);


      DECL_GEN_SIGNAL(_001OnCreate);





   };


} // namespace userex


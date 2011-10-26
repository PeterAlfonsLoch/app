#pragma once


namespace querydb
{

   class document;

   class CLASS_DECL_CA2_QUERYDB view :
      virtual public ::simple_list_view
   {
   public:


	   view(::ca::application * papp);
      virtual ~view();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);


      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      document * get_document();


      virtual count _001GetItemCount();
      virtual void _001InsertColumns();



      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void _001GetItemText(::user::list_item * pitem);



   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace querydb
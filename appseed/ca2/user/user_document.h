#pragma once


class CLASS_DECL_ca2 document :
   virtual public user::document_interface,
   public ::ca::data_container,
   virtual public ::database::client
{
public:


   document(sp(::ca::application) papp);
   virtual ~document();


   virtual bool set_data(::ca::data * pdata);

   using ::ca::data_container::get_data;
   using ::ca::data_container_base::get_data;


   
      document(sp(::ca::application) papp);
      virtual ~document();


      virtual void on_alloc(sp(::ca::application) papp);

   #ifdef DEBUG
      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;
   #endif //DEBUG

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         
      friend class ::userbase::document_template;



};



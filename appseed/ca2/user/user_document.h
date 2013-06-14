#pragma once


namespace user
{


   class CLASS_DECL_ca2 document :
      virtual public ::user::document_interface,
      virtual public ::ca2::data_container,
      virtual public ::database::client
   {
   public:


      document(sp(::ca2::application) papp);
      virtual ~document();


      virtual bool set_data(::ca2::data * pdata);

      using ::ca2::data_container::get_data;
      using ::ca2::data_container_base::get_data;





      virtual void on_alloc(sp(::ca2::application) papp);

      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);




   };




} // namespace user






#pragma once


namespace user
{


   class CLASS_DECL_CORE document :
      virtual public ::user::document_interface,
      virtual public ::data::data_container,
      virtual public ::database::client
   {
   public:


      document(sp(base_application) papp);
      virtual ~document();


      virtual bool set_data(::data::data * pdata);

      using ::data::data_container::get_data;
      using ::data::data_container_base::get_data;





      virtual void on_alloc(sp(base_application) papp);

      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);




   };




} // namespace user






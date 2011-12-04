#pragma once


namespace user
{


   class CLASS_DECL_ca2 document_interface :
      virtual public command_target,
      virtual public ex1::byte_serializable,
      virtual public ::ca::data_container
   {
   public:


      document_interface(::ca::application * papp);
      virtual ~document_interface();


      virtual void update_title();


   };


} // namespace user


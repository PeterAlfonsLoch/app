#pragma once


class CLASS_DECL_ca document :
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

};



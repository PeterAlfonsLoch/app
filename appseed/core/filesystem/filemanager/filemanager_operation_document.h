#pragma once


class CLASS_DECL_CORE file_manager_operation_document :
   public ::user::object
{
public:


   file_manager_operation_thread  m_thread;
   
   
   file_manager_operation_document(sp(::base::application) papp);

   
   virtual bool on_new_document();

   
   


};
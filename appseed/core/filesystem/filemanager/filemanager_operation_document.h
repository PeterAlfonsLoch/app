#pragma once


class CLASS_DECL_ca2 file_manager_operation_document :
   public ::user::document
{
public:


   file_manager_operation_thread  m_thread;
   
   
   file_manager_operation_document(sp(base_application) papp);

   
   virtual bool on_new_document();

   
   


};
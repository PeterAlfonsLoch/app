#pragma once


class CLASS_DECL_ca2 file_manager_operation_document :
   public ::userbase::document
{
public:


   file_manager_operation_thread  m_thread;
   
   
   file_manager_operation_document(::ca::applicationsp papp);

   
   virtual bool on_new_document();

   
   


};
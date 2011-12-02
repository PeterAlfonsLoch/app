#pragma once


class CLASS_DECL_ca file_manager_operation_document :
   public ::userbase::document
{
public:
   file_manager_operation_document(::ax::application * papp);

   virtual BOOL on_new_document();

   file_manager_operation_thread  m_thread;

};
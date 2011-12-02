#pragma once

class CLASS_DECL_ca file_manager_operation_info_view :
   virtual public ::userbase::view
   
{
public:

   double m_dAnime;

   file_manager_operation_info_view(::ax::application * papp);

   virtual void OnDraw(::ax::graphics * pdc);

   virtual void _001OnDraw(::ax::graphics * pdc);

   file_manager_operation_document * get_document();

   void OnFileOperationStep(int iOperation, bool bFinal);

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnTimer)
   virtual void install_message_handling(::gen::message::dispatch * pdispatch);

   void assert_valid() const;
   void dump(dump_context & context) const;
};

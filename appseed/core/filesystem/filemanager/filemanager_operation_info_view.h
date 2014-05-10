#pragma once

class CLASS_DECL_CORE file_manager_operation_info_view :
   virtual public ::user::impact
   
{
public:

   double m_dAnime;

   file_manager_operation_info_view(sp(::base::application) papp);

   virtual void OnDraw(::draw2d::graphics * pdc);

   virtual void _001OnDraw(::draw2d::graphics * pdc);

   sp(file_manager_operation_document) get_document();

   void OnFileOperationStep(int32_t iOperation, bool bFinal);

   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnTimer);
   virtual void install_message_handling(::message::dispatch * pdispatch);

   void assert_valid() const;
   void dump(dump_context & context) const;
};

#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_list_view:
      virtual public ::user::show < ::user::list >
   {
   public:


      ::user::list_cache               m_listcache;
      uint32_t                         m_dwLast123Update;


      operation_list_view(::aura::application * papp);

      virtual void install_message_handling(::message::dispatch * pinterface);

      void _001InsertColumns();

      virtual void OnDraw(::draw2d::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(timer * ptimer);

      virtual count _001GetItemCount();
      virtual void _001GetItemText(::user::mesh_item * pitem);

      void OnFileOperationStep(int32_t iOperation,bool bFinal);


      virtual void _001OnInitialUpdate();

      
      void on_update(::user::impact * pSender,LPARAM lHint,object * pHint);
      sp(operation_document) get_document();


   };


} // namespace filemanager















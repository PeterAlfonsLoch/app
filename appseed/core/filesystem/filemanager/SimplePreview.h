#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE SimplePreview :
      virtual public ::filemanager::SimplePreviewInterface
   {
   public:
      SimplePreview(sp(base_application) papp);
      virtual ~SimplePreview();

      virtual void install_message_handling(::message::dispatch * pdispatch);
      virtual void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);
   };


} // namespace filemanager




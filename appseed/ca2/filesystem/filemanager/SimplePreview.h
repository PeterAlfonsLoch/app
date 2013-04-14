#pragma once


namespace filemanager
{


   class CLASS_DECL_ca2 SimplePreview :
      virtual public ::filemanager::SimplePreviewInterface
   {
   public:
      SimplePreview(sp(::ca::application) papp);
      virtual ~SimplePreview();

      virtual void install_message_handling(::ca::message::dispatch * pdispatch);
      virtual void on_update(sp(::user::view) pSender, LPARAM lHint, ::ca::object* pHint);
   };


} // namespace filemanager




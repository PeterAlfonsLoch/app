#pragma once


namespace filemanager
{


   class CLASS_DECL_ca2 SimplePreview :
      virtual public ::filemanager::SimplePreviewInterface
   {
   public:
      SimplePreview(sp(::ca2::application) papp);
      virtual ~SimplePreview();

      virtual void install_message_handling(::ca2::message::dispatch * pdispatch);
      virtual void on_update(sp(::user::view) pSender, LPARAM lHint, ::ca2::object* pHint);
   };


} // namespace filemanager




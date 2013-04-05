#pragma once


namespace filemanager
{


   class CLASS_DECL_ca2 SimplePreview :
      virtual public ::filemanager::SimplePreviewInterface
   {
   public:
      SimplePreview(::ca::applicationsp papp);
      virtual ~SimplePreview();

      virtual void install_message_handling(::ca::message::dispatch * pdispatch);
      virtual void on_update(::view * pSender, LPARAM lHint, ::ca::object* pHint);
   };


} // namespace filemanager




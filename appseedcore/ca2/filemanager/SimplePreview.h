#pragma once


namespace filemanager
{

class CLASS_DECL_ca SimplePreview :
   virtual public ::userbase::view,
   virtual public filemanager::SimplePreviewInterface
{
public:
   SimplePreview(::ca::application * papp);
   virtual ~SimplePreview();

   virtual void install_message_handling(::user::win::message::dispatch * pdispatch);
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
};


} // namespace filemanager
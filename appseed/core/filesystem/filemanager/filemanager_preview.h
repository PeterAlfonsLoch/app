#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE preview :
      virtual public ::user::view,
      virtual public data_interface
   {
   public:

      string      m_strPath;
      stringa     m_straPath;
      stringa     m_straTitle;
      int32_t         m_iCurFile;

      preview(sp(base_application) papp);
      virtual ~preview();

      virtual void install_message_handling(::message::dispatch * pdispatch);
      virtual void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

   };


} // namespace filemanager




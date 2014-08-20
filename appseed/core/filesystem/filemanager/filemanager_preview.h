#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE preview :
      virtual public ::user::impact,
      virtual public impact
   {
   public:

      string         m_strPath;
      //stringa        m_straPath;
      //stringa        m_straTitle;
      //int64_array    m_iaSize;
      int32_t        m_iCurFile;

      preview(sp(::axis::application) papp);
      virtual ~preview();

      virtual void install_message_handling(::message::dispatch * pdispatch);
      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

   };


} // namespace filemanager




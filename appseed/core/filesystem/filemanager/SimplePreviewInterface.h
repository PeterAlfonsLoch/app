#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE SimplePreviewInterface :
      virtual public ::user::view,
      virtual public FileManagerViewInterface
   {
   public:


      string      m_strPath;
      stringa     m_straPath;
      stringa     m_straTitle;
      int32_t         m_iCurFile;


      SimplePreviewInterface(sp(base_application) papp);
      virtual ~SimplePreviewInterface();


      virtual void _001OnDraw(::draw2d::graphics * pdc);

   };


} // namespace filemanager



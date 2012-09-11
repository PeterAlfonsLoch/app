#pragma once


namespace filemanager
{


   class CLASS_DECL_ca2 SimplePreviewInterface :
      virtual public ::userbase::view,
      virtual public FileManagerViewInterface
   {
   public:


      string      m_strPath;
      stringa     m_straPath;
      stringa     m_straTitle;
      int         m_iCurFile;


      SimplePreviewInterface(::ca::application * papp);
      virtual ~SimplePreviewInterface();


      virtual void _001OnDraw(::ca::graphics * pdc);

   };


} // namespace filemanager



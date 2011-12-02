#pragma once

namespace filemanager
{

class CLASS_DECL_ca SimplePreviewInterface :
   virtual public ::user::interaction,
   virtual public FileManagerViewInterface
{
public:
   SimplePreviewInterface(::ax::application * papp);
   virtual ~SimplePreviewInterface();


   virtual void _001OnDraw(::ax::graphics * pdc);

   string m_strPath;
   stringa m_straPath;
   stringa m_straTitle;
   int m_iCurFile;
};

} // namespace filemanager
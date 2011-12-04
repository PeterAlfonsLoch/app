#pragma once

namespace filemanager
{

class CLASS_DECL_ca2 SimplePreviewInterface :
   virtual public ::user::interaction,
   virtual public FileManagerViewInterface
{
public:
   SimplePreviewInterface(::ca::application * papp);
   virtual ~SimplePreviewInterface();


   virtual void _001OnDraw(::ca::graphics * pdc);

   string m_strPath;
   stringa m_straPath;
   stringa m_straTitle;
   int m_iCurFile;
};

} // namespace filemanager
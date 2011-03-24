// MusicalPlayerLightFileListCallback.h: interface for the MusicalPlayerLightFileListCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICALPLAYERLIGHTFILELISTCALLBACK_H__34446B67_E2BA_4D84_9D40_A4A1E8C9FA54__INCLUDED_)
#define AFX_MUSICALPLAYERLIGHTFILELISTCALLBACK_H__34446B67_E2BA_4D84_9D40_A4A1E8C9FA54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class BaseButton;
class FileManagerItem;

class MusicalPlayerLightFileListCallback :
   public FileManagerFileListCallback
{
public:
	MusicalPlayerLightFileListCallback();
	virtual ~MusicalPlayerLightFileListCallback();

   ImageList            m_imagelistSubItemHover;
   ImageList            m_imagelistItemHover;
   ImageList            m_imagelistNormal;


   virtual int GetActionButtonCount();
   virtual void InitializeActionButton(int i, BaseButtonControl * pbutton);
   virtual void OnButtonAction(int i, FileManagerItem & item);

   virtual void OnMenuItemAction(int iId);
   virtual bool GetMenuItemCallback(int iId);
   virtual void GetMenuItemUpdate(int iId, CCmdUI * pcmdui);

};

#endif // !defined(AFX_MUSICALPLAYERLIGHTFILELISTCALLBACK_H__34446B67_E2BA_4D84_9D40_A4A1E8C9FA54__INCLUDED_)

#pragma once

#include "AlbumSongList.h"

class CLASS_DECL_CA2_CUBE AlbumSongCheckList :
   public AlbumSongList
{
public:
   
   
   dword_array    m_dwaState;
   dword_array    m_dwaGroup;


   AlbumSongCheckList(::ca::application * papp);
   virtual ~AlbumSongCheckList();


   VMSRESULT GetCheckedPaths(stringa * pstraPaths);
   virtual VMSRESULT UpdateList(dword_array * pdwaKeys = NULL);

   static UINT ThreadProcUpdateList(LPVOID lpParameter);

   virtual void _001InsertColumns();
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs) ;
   virtual int StdGetItemImage(int iItem);

   VMSRESULT UpdateList_();
   afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnFileAutodeleteduplicates();
   afx_msg void OnUpdateFileAutodeleteduplicates(cmd_ui * pcmdui);
   afx_msg void OnHeaderCtrlItemChanging(NMHDR* pNMHDR, LRESULT* pResult);

};


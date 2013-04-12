#pragma once


class CLASS_DECL_ca2 FileManagerViewUpdateHint :
   public ::ca::object  
{
public:
   
   enum e_type
   {
      TypeInitialize,
      TypeSynchronizePath,
      TypeSynchronizeLocations,
      TypeSynchronizeFolderSelection,
      TypeCreateBars,
      TypePop,
      TypeCreateViews,
      TypeFilter,
      TypeGetActiveViewSelection,
      TypeOpenSelectionProperties,
      TypeSaveAsStart,
      TypeSaveAsCancel,
      TypeSaveAsOK,
      TypeSaveAsSaveFailed,
      TypeSaveAsSaved,
   };


public:
   void set_type(e_type e_type);
   bool is_type_of(e_type e_type);
   FileManagerViewUpdateHint();
   virtual ~FileManagerViewUpdateHint();

   ::fs::item_array       m_itemaSelected;
   string                     m_wstrFilter;
   sp(FileManagerInterface)     m_pmanager;
   sp(FileManagerInterface)     m_pmanagerMain;
   sp(::view)               m_pview;
   UINT                       m_uiId;
   string                     m_strPath;

protected:
   e_type    m_etype;

};


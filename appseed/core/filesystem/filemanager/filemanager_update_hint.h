#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE update_hint :
      public object
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
         TypeFilter,
         TypeGetActiveViewSelection,
         TypeOpenSelectionProperties,
         TypeSaveAsStart,
         TypeSaveAsCancel,
         TypeSaveAsOK,
         TypeSaveAsSaveFailed,
         TypeSaveAsSaved,
      };



      ::fs::item_array              m_itemaSelected;
      string                        m_wstrFilter;
      sp(::filemanager::manager)    m_pmanager;
      sp(::filemanager::manager)    m_pmanagerMain;
      sp(::user::impact)            m_pview;
      UINT                          m_uiId;
      string                        m_strPath;

      e_type                        m_etype;

      ::action::context             m_actioncontext;


      update_hint();
      virtual ~update_hint();


      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);


   };



} // namespace filemanager





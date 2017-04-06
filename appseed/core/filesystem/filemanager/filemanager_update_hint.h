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
         TypeTopicStart,
         TypeTopicCancel,
         TypeTopicOK,
         TypeTopicSaveFailed,
         TypeTopicSaved,
      };


      ::filemanager::manager::e_mode   m_emode;
      ::fs::item_array              m_itemaSelected;
      string                        m_wstrFilter;
      ::filemanager::manager *      m_pmanager;
      ::filemanager::manager *      m_pmanagerMain;
      ::user::impact *              m_pview;
      UINT                          m_uiId;
      ::file::path                  m_filepath;

      e_type                        m_etype;

      ::action::context             m_actioncontext;
      bool                              m_bOk;

      update_hint();
      virtual ~update_hint();


      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);


   };



} // namespace filemanager





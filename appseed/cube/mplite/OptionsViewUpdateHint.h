#pragma once

namespace mplite
{

   enum EOptionsView
   {
      OptionsViewNone,
      OptionsViewFolders,
      OptionsViewFileAssociation,
      OptionsViewAudioDevices,
      OptionsViewKaraoke,
   };


   class CLASS_DECL_CA2_CUBE OptionsViewUpdateHint :
      public ::radix::object  
   {
   public:
      enum e_type
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,
         TypeSetViewVmsDataKey,
      };
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      OptionsViewUpdateHint();
      virtual ~OptionsViewUpdateHint();

      EOptionsView      m_eview;
      ::userbase::view *        m_pview;
      ::database::id     m_datakey;
      e_type m_etype;

   };

} // namespace mplite
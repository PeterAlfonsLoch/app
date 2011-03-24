#pragma once

namespace mplite
{

   enum EMediaLibraryView
   {
      MediaLibraryViewNone,
      MediaLibraryViewAllMedia,
      MediaLibraryViewMediaExplorer,
      MediaLibraryViewKaraokeLibraryExplorer,
      MediaLibraryViewKaraokeFsExplorer,
   };

   class CLASS_DECL_CA2_CUBE MediaLibraryViewUpdateHint :
      public ::radix::object 
   {
      
   public:

      enum e_type
      {
         TypeFilter,
         TypeSetView,
         TypeGetView,
      };

      MediaLibraryViewUpdateHint();
      virtual ~MediaLibraryViewUpdateHint();

      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      
      string m_strFilter;

   public:
      EMediaLibraryView    m_eview;
   protected:
      e_type    m_etype;

   };

} // namespace mplite
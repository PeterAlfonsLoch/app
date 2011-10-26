#pragma once

class CLASS_DECL_ca PlaylistViewUpdateHint : public ::radix::object
{
public:

   enum EHint // Hints
   {
      HintInitial,
      HintFull,
      HintCurrentSong,
      HintMode,
      HintGetAttachableView,
      HintPop,
   };

protected:


   int     m_iHint;
   base_array < ::userbase::view *, ::userbase::view * > m_viewpaAttachable;

public:
   
   PlaylistViewUpdateHint();
   virtual ~PlaylistViewUpdateHint();


   bool is_type_of(EHint ehint);
   void AddAttachableView(::userbase::view * pview);
   void SetHint(int iHint);
   int GetHint();
   void GetAttachableViews(base_array < ::userbase::view *, ::userbase::view * > & viewpa);





};

#pragma once

class LyricViewLine;

namespace kar
{

   class CLASS_DECL_ca LyricViewLineSelectionItem  
   {

   public:
      int GetTokenStart();
      int GetTokenEnd();
      int GetCharStart();
      int GetCharEnd();
      void SetTokenStart(int iToken);
      void SetTokenEnd(int iToken);
      void SetCharStart(int iChar);
      void SetCharEnd(int iChar);

   protected:
      int               m_iTokenStart;
      int               m_iTokenEnd;
      int               m_iCharStart;
      int               m_iCharEnd;


        // Construction / Destruction
   public:
      void NormalizeSel();
      bool Intersect(LyricViewLine & viewline);
      bool Intersect(
         int      iTokenStart,
         int      iTokenEnd);
      LyricViewLineSelectionItem();
      LyricViewLineSelectionItem(
         int      iTokenStart,
         int      iTokenEnd,
         int      iCharStart,
         int      iCharEnd
         );
      virtual ~LyricViewLineSelectionItem();

      LyricViewLineSelectionItem & operator =(const LyricViewLineSelectionItem & item);
   };



   class CLASS_DECL_ca LyricViewLineSelection :
      virtual public ::radix::object
   {
   public:
      enum e_state
      {
         state_initial = 1,
         StateTracking = 2
      };
      
      enum e_event
      {
         EventStart = 1,
         EventEnd = 2
      };
      
      enum ETypeMask
      {
   //      TypeMaskStartHere = 1,
   //      TypeMaskEndHere = 2,
      };

   public:
      base_array < LyricViewLineSelectionItem, LyricViewLineSelectionItem> m_itema;

      LyricViewLineSelectionItem m_item;
      

      int               m_iTokenStartSource;
      int               m_iTokenEndSource;
      int               m_iCharStartSource;
      int               m_iCharEndSource;

      int               m_etype; 
      e_state            m_estate;

        // Conxtruction / Destruction
   public:
      bool get_item(LyricViewLineSelectionItem & item, LyricViewLine & viewline);
      e_state GetState();
      LyricViewLineSelection(::ca::application * papp);
      virtual ~LyricViewLineSelection();


      virtual void relay_event(LyricViewLine & viewline, gen::signal_object * pobj);
      virtual void OnSelEvent(LyricViewLine & viewline, e_event eselevent);
      bool SetSelBefore(LyricViewLine & viewline);
      bool SetSelAfter(LyricViewLine & viewline);
      void NormalizeSel(LyricViewLine & viewline);

      void Select(
         int      iTokenStart,
         int      iTokenEnd,
         int      iCharStart,
         int      iCharEnd,
         bool   bMerge);



      LyricViewLineSelection & operator =(LyricViewLineSelection & selection);

      bool OnMouseMove(LyricViewLine & viewline, UINT user, point pt);
      bool OnLButtonDown(LyricViewLine & viewline, UINT user, point pt);
      bool OnLButtonUp(LyricViewLine & viewline, UINT user, point pt);
      bool OnTimer(LyricViewLine & viewline, UINT user);

   };




} // namespace kar

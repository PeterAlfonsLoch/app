#pragma once

class XfplayerViewLine;

class CLASS_DECL_ca XfplayerViewLineSelectionItem  
{

public:
   int GetLineStart();
   int GetLineEnd();
   int GetCharStart();
   int GetCharEnd();
   void SetLineStart(int iLine);
   void SetLineEnd(int iLine);
   void SetCharStart(int iChar);
   void SetCharEnd(int iChar);

protected:
   int               m_iLineStart;
   int               m_iLineEnd;
   int               m_iCharStart;
   int               m_iCharEnd;


      // Construction / Destruction
public:
   void NormalizeSel();
   bool Intersect(XfplayerViewLine & viewline);
   bool Intersect(int iLineStart, int iLineEnd);
   XfplayerViewLineSelectionItem();
   XfplayerViewLineSelectionItem(
      int      iLineStart,
      int      iLineEnd,
      int      iCharStart,
      int      iCharEnd
      );
   virtual ~XfplayerViewLineSelectionItem();

   XfplayerViewLineSelectionItem & operator =(const XfplayerViewLineSelectionItem & item);
};


class CLASS_DECL_ca XfplayerViewLineSelection :
   virtual ::radix::object
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
   base_array < XfplayerViewLineSelectionItem, XfplayerViewLineSelectionItem> m_itema;

   XfplayerViewLineSelectionItem m_item;
      

   int               m_iLineStartSource;
   int               m_iLineEndSource;
   int               m_iCharStartSource;
   int               m_iCharEndSource;

   int               m_etype; 
   e_state            m_estate;

      // Conxtruction / Destruction
public:
   bool get_item(XfplayerViewLineSelectionItem & item, XfplayerViewLine & viewline);
   e_state GetState();
   XfplayerViewLineSelection();
   virtual ~XfplayerViewLineSelection();


   virtual void relay_event(XfplayerViewLine & viewline, gen::signal_object * pobj);
   virtual void OnSelEvent(XfplayerViewLine & viewline, e_event eselevent);
   bool SetSelBefore(XfplayerViewLine & viewline);
   bool SetSelAfter(XfplayerViewLine & viewline);
   void NormalizeSel(XfplayerViewLine & viewline);
   void GetNormalSelection(int & iLineStart, int & iCharStart, int & iLineEnd, int & iCharEnd);

   void Select(
      int      iLineStart,
      int      iLineEnd,
      int      iCharStart,
      int      iCharEnd,
      bool   bMerge);



   XfplayerViewLineSelection & operator =(XfplayerViewLineSelection & selection);

   bool OnMouseMove(XfplayerViewLine & viewline, UINT user, point pt);
   bool OnLButtonDown(XfplayerViewLine & viewline, UINT user, point pt);
   bool OnLButtonUp(XfplayerViewLine & viewline, UINT user, point pt);
   bool OnTimer(XfplayerViewLine & viewline, UINT user);

};


#pragma once

class XfplayerViewLine;

class CLASS_DECL_ca2 XfplayerViewLineSelectionItem  
{
protected:

   index               m_iLineStart;
   index               m_iLineEnd;
   strsize               m_iCharStart;
   strsize               m_iCharEnd;

public:
   index GetLineStart();
   index GetLineEnd();
   index GetCharStart();
   index GetCharEnd();
   void SetLineStart(index iLine);
   void SetLineEnd(index iLine);
   void SetCharStart(strsize iChar);
   void SetCharEnd(index iChar);



      // Construction / Destruction
public:
   void NormalizeSel();
   bool Intersect(XfplayerViewLine & viewline);
   bool Intersect(index iLineStart, index iLineEnd);
   XfplayerViewLineSelectionItem();
   XfplayerViewLineSelectionItem(
      index      iLineStart,
      index      iLineEnd,
      strsize      iCharStart,
      strsize      iCharEnd
      );
   virtual ~XfplayerViewLineSelectionItem();

   XfplayerViewLineSelectionItem & operator =(const XfplayerViewLineSelectionItem & item);
};


class CLASS_DECL_ca2 XfplayerViewLineSelection :
   virtual ::ca::object
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
   array < XfplayerViewLineSelectionItem, XfplayerViewLineSelectionItem> m_itema;

   XfplayerViewLineSelectionItem m_item;
      

   index               m_iLineStartSource;
   index               m_iLineEndSource;
   strsize               m_iCharStartSource;
   strsize               m_iCharEndSource;

   int32_t               m_etype; 
   e_state            m_estate;

      // Conxtruction / Destruction
public:
   bool get_item(XfplayerViewLineSelectionItem & item, XfplayerViewLine & viewline);
   e_state GetState();
   XfplayerViewLineSelection();
   virtual ~XfplayerViewLineSelection();


   virtual void relay_event(XfplayerViewLine & viewline, ::ca::signal_object * pobj);
   virtual void OnSelEvent(XfplayerViewLine & viewline, e_event eselevent);
   bool SetSelBefore(XfplayerViewLine & viewline);
   bool SetSelAfter(XfplayerViewLine & viewline);
   void NormalizeSel(XfplayerViewLine & viewline);
   void GetNormalSelection(index & iLineStart, strsize & iCharStart, index & iLineEnd, strsize & iCharEnd);

   void Select(
      index      iLineStart,
      index      iLineEnd,
      strsize      iCharStart,
      strsize      iCharEnd,
      bool   bMerge);



   XfplayerViewLineSelection & operator =(XfplayerViewLineSelection & selection);

   bool OnMouseMove(XfplayerViewLine & viewline, UINT user, point pt);
   bool OnLButtonDown(XfplayerViewLine & viewline, UINT user, point pt);
   bool OnLButtonUp(XfplayerViewLine & viewline, UINT user, point pt);
   bool OnTimer(XfplayerViewLine & viewline, UINT user);

};


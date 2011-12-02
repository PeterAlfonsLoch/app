// BaseDockContext.h: interface for the BaseDockContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEDOCKCONTEXT_H__0BB0FA53_7FA3_440C_9D2C_A0B0578F1EE8__INCLUDED_)
#define AFX_BASEDOCKCONTEXT_H__0BB0FA53_7FA3_440C_9D2C_A0B0578F1EE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ::userbase::control_bar;
class userbase::frame_window;

/////////////////////////////////////////////////////////////////////////////
// toolbar docking support

class BaseDockContext
{
public:
// Construction
   BaseDockContext(::userbase::control_bar* pBar);

// Attributes
   point m_ptLast;            // last mouse position during drag
   rect m_rectLast;
   size m_sizeLast;
   BOOL m_bDitherLast;

   // Rectangles used during dragging or resizing
   rect m_rectDragHorz;
   rect m_rectDragVert;
   rect m_rectFrameDragHorz;
   rect m_rectFrameDragVert;

   ::userbase::control_bar* m_pBar;        // the toolbar that created this context
   userbase::frame_window* m_pDockSite;     // the controlling frame of the ::userbase::control_bar
   DWORD m_dwDockStyle;        // allowable dock styles for bar
   DWORD m_dwOverDockStyle;    // style of dock that rect is over
   DWORD m_dwStyle;            // style of control bar
   BOOL m_bFlip;               // if shift key is down
   BOOL m_bForceFrame;         // if ctrl key is down

   ::ax::graphics * m_pDC;                 // where to draw during drag
   BOOL m_bDragging;
   int m_nHitTest;
   bool m_bTracking;

   UINT m_uMRUDockID;
   rect m_rectMRUDockPos;

   DWORD m_dwMRUFloatStyle;
   point m_ptMRUFloatPos;

// Drag Operations
   virtual void StartDrag(point pt);
   void Move(point pt);       // called when mouse has moved
   void EndDrag();             // drop
   void OnKey(int nChar, BOOL bDown);

// Resize Operations
   virtual void StartResize(int nHitTest, point pt);
   void Stretch(point pt);
   void EndResize();

// Double Click Operations
   virtual void ToggleDocking();

// Operations
   void InitLoop();
   void CancelLoop();

// Implementation
public:
   ~BaseDockContext();
   BOOL Track();
   void DrawFocusRect(BOOL bRemoveRect = FALSE);
      // draws the correct outline
   void UpdateState(BOOL* pFlag, BOOL bNewValue);
   DWORD CanDock();
   BaseDockBar* GetDockBar(DWORD dwOverDockStyle);


   void OnBarMouseMove(UINT uiFlags, point pt);
   void OnBarLButtonUp(UINT uiFlags, point pt);
   void DragMoveFeedback();
};

#endif // !defined(AFX_BASEDOCKCONTEXT_H__0BB0FA53_7FA3_440C_9D2C_A0B0578F1EE8__INCLUDED_)

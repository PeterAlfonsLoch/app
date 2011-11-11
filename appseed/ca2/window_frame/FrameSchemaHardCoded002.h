#pragma once

#include "FrameSchema.h"

namespace window_frame
{

   class CLASS_DECL_ca FrameSchemaHardCoded002 :
      public FrameSchema
   {
   public:


      enum EElement
      {
         ElementNone,
         ElementTopLeftIcon,
         ElementEnd,
      };

      enum EStyle
      {
         StyleLightBlue,
         StyleTranslucidLightBlue,
         StyleBlackBorder,
         StyleLightGreen,
         StyleTranslucidLightGreen,
         StyleRedOrange,
         StyleBlueRedPurple,
         StyleEveningSun,
         StyleTranslucidWarmGray,
      };

      EStyle                        m_estyle;

      COLORREF                      m_crFrameBorder;

      COLORREF                      m_crMoveableBorder;
      COLORREF                      m_crMoveableBorderHilight;
      COLORREF                      m_crMoveableBorderShadow;
      COLORREF                      m_crMoveableBorderDkShadow;


      ::ca::pen_sp                  m_penText1;
      ::ca::pen_sp                  m_penFace1;
      ::ca::pen_sp                  m_penHilight1;
      ::ca::pen_sp                  m_penShadow1;
      ::ca::pen_sp                  m_penDkShadow1;



      COLORREF                      m_crDkShadow;

      

      size                          m_minSize;

      int                           m_iMargin;
      int                           m_iButtonMargin;

      rect                          m_rectCaption;
      rect                          m_rectWindowText;
      rect                          m_rectControlBox;
      rect                          m_rectClient;
      point                         m_pointWindowIcon;



      FrameSchemaHardCoded002(::ca::application * papp);
      virtual ~FrameSchemaHardCoded002();

      void CalcWndClient(LPRECT lprect, LPCRECT lprectWindow);
      virtual void OnAttach();
      virtual void _000OnBeforeMove(LPCRECT lpcrect);
      virtual void _000OnBeforeSize(LPCRECT lpcrect);
      virtual void layout();
      virtual void OnActivate();
      virtual bool _000OnNcHitTest(point pt, LRESULT & nHitTest);



      virtual void OnMove(::user::interaction * pwnd);
      virtual bool _000OnDisplayChange(int iBitsPerPixel, size sizeScreen);
      virtual void OnInitializeAppearance();
      ::user::interaction * GetDrawWindow();
      ::user::interaction * GetWnd();
      virtual void OnNcCalcSize(LPRECT lprect);
      virtual void OnAppearanceModeChange();

      void _001OnDraw(::ca::graphics * pca);

      void SetStyle(EStyle nStyle);
      void SetMoveableBorderColor(COLORREF cr);

      int GetMargin();
      int GetCaptionHeight();
      int GetButtonSize();

      int UpdateControlBox();

      void DrawFrame(::ca::graphics * pdc);
      void Draw3dRectSide(::ca::graphics * pdc, LPCRECT lpcrect, MoveManager::EBorder eborder, COLORREF crTopLeft, COLORREF crBottomRight);
      void DrawBorder(::ca::graphics * pdc, LPCRECT lpcrectClient);
      void DrawBorderSide(::ca::graphics * pdc, LPCRECT lpcrectClient, MoveManager::EBorder eside);
      void GetBorderRect(LPCRECT lpcrectClient, LPRECT lprect, MoveManager::EBorder eside);
      void DrawGripSet(::ca::graphics * pdc, LPCRECT lpcrectClient);
      void DrawGrip(::ca::graphics * pdc, LPCRECT lpcrectClient,   EGrip egrip);
      void DrawRectGrip(::ca::graphics * pdc, LPCRECT lpcrect);

      void GetWndClientRect(LPRECT lprect);
      void GetDrawClientRect(LPRECT lprect);
      bool GetElementRect(LPRECT lprect, EElement eelement);
      bool hit_test(const POINT & point, EElement & eelement);

      void UpdateDrawingObjects();
      void UpdateWndClientRect();
      void UpdateWndRegion(LPCRECT lpcrectWindow);
      void UpdateWnd();
      void UpdateWndStyle();

      virtual EHitTest _000HitTest(point pt);
      virtual bool _000OnMove(int x, int y);
      virtual bool _000OnSize(UINT nType, int x, int y);


      COLORREF get_border_main_body_color();

   };

   FrameSchemaHardCoded002::EElement operator++(FrameSchemaHardCoded002::EElement & eelement, int i);

} // namespace window_frame

#pragma once


#include "FrameSchema.h"


namespace window_frame
{


   class CLASS_DECL_ca FrameSchemaHardCoded001 :
      public FrameSchema
   {
   public:

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

      enum EElement
      {
         ElementNone,
         ElementTopLeftIcon,
         ElementEnd,
      };

      EStyle                        m_estyle;

      COLORREF                      m_crFrameBorder;

      COLORREF                      m_crMoveableBorder;
      COLORREF                      m_crMoveableBorderHilight;
      COLORREF                      m_crMoveableBorderShadow;
      COLORREF                      m_crMoveableBorderDkShadow;


      ::ax::pen_sp                  m_penText1;
      ::ax::pen_sp                  m_penFace1;
      ::ax::pen_sp                  m_penHilight1;
      ::ax::pen_sp                  m_penShadow1;
      ::ax::pen_sp                  m_penDkShadow1;

      COLORREF                      m_crDkShadow;

      size                          m_minSize;

      int                           m_iMargin;
      int                           m_iButtonMargin;

      rect                          m_rectCaption;
      rect                          m_rectWindowText;
      rect                          m_rectControlBox;
      rect                          m_rectClient;
      point                         m_pointWindowIcon;


      FrameSchemaHardCoded001(::ax::application * papp);
      virtual ~FrameSchemaHardCoded001();


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

      void _001OnDraw(::ax::graphics * pca);

      void SetStyle(EStyle nStyle);
      void SetMoveableBorderColor(COLORREF cr);

      int GetMargin();
      int GetCaptionHeight();
      int GetButtonSize();

      int UpdateControlBox();

      void DrawFrame(::ax::graphics * pdc);
      void Draw3dRectSide(::ax::graphics * pdc, LPCRECT lpcrect, MoveManager::EBorder eborder, COLORREF crTopLeft, COLORREF crBottomRight);
      void DrawBorder(::ax::graphics * pdc, LPCRECT lpcrectClient);
      void DrawBorderSide(::ax::graphics * pdc, LPCRECT lpcrectClient, MoveManager::EBorder eside);
      void GetBorderRect(LPCRECT lpcrectClient, LPRECT lprect, MoveManager::EBorder eside);
      void DrawGripSet(::ax::graphics * pdc, LPCRECT lpcrectClient);
      void DrawGrip(::ax::graphics * pdc, LPCRECT lpcrectClient,   EGrip egrip);
      void DrawRectGrip(::ax::graphics * pdc, LPCRECT lpcrect);

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





   };

   FrameSchemaHardCoded001::EElement operator++(FrameSchemaHardCoded001::EElement & eelement, int i);

} // namespace window_frame

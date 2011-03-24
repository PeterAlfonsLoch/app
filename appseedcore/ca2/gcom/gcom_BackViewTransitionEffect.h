#pragma once

namespace gcom
{
   namespace backview
   {

      enum ETransitionEffect
      {
         TransitionEffectInvalid,
         TransitionEffectStart,
         TransitionEffectFirst = TransitionEffectStart,
         TransitionEffectSingleStep = TransitionEffectFirst,
         TransitionEffectSquarypixelate_,
         TransitionEffectHexagonalpixelate_,
         TransitionEffectCirclypixelate_,
         TransitionEffectEllipsoidalpixelate_,
         TransitionEffectLinearFadingTopBottom,
         TransitionEffectLinearFadingBottomTop,
         TransitionEffectLinearFadingLeftRight,
         TransitionEffectLinearFadingRightLeft,
         TransitionEffectAccumulLinearFadingTopBottom,
         TransitionEffectAccumulLinearFadingBottomTop,
         TransitionEffectAccumulLinearFadingLeftRight,
         TransitionEffectAccumulLinearFadingRightLeft,
         TransitionEffectFlyInTopBottom,
         TransitionEffectFlyInBottomTop,
         TransitionEffectFlyInLeftRight,
         TransitionEffectFlyInRightLeft,
         TransitionEffectFlyInLeftBottom,
         TransitionEffectFlyInLeftTop,
         TransitionEffectFlyInRightBottom,
         TransitionEffectFlyInRightTop,
         TransitionEffectWipeBottom,
         TransitionEffectWipeTop,
         TransitionEffectWipeRight,
         TransitionEffectWipeLeft,
         TransitionEffectWipeTopLeft,
         TransitionEffectWipeTopRight,
         TransitionEffectWipeBottomLeft,
         TransitionEffectWipeBottomRight,
         TransitionEffectWipeCenter,
         TransitionEffectWipeIn,
         TransitionEffectScaleBottom,
         TransitionEffectScaleTop,
         TransitionEffectScaleRight,
         TransitionEffectScaleLeft,
         TransitionEffectScaleTopLeft,
         TransitionEffectScaleTopRight,
         TransitionEffectScaleBottomLeft,
         TransitionEffectScaleBottomRight,
         TransitionEffectScaleCenter,
         TransitionEffectpixelate_TopBottom,
         TransitionEffectpixelate_BottomTop,
         TransitionEffectpixelate_LeftRight,
         TransitionEffectpixelate_RightLeft,
         TransitionEffectVisual,
         TransitionEffectRadialUnveil,
         TransitionEffectLast = TransitionEffectRadialUnveil,
         TransitionEffectEnd,
      };

      class CLASS_DECL_ca TransitionEffect :
         public Helper
      {

         friend class Interface;
         friend class VisualEffect;
      public:

         class Tool001 :
            public Helper
         {
         public:
            Tool001(Main & viewinterface);
            union DATA
            {
               struct SQUARY_PIXELATE
               {
                  double xyz;
               } m_squarypixelate;
               struct HEXAGON_PIXELATE
               {
                  double xyz;
               } m_hexagonpixelate;
               struct SLICE_FRAME
               {
                  int m_iTileCount;
                  int m_iFrameCount;
                  int m_iGroupCount;
               } m_sliceframe;
               struct TILES
               {
                  int m_iTilesX;
                  int m_iTilesY;
                  int m_iTiles;
               } m_tiles;
               struct ALPHA_PIXELATE
               {
                  int m_c1;
                  int m_c2;
                  int m_iSizeIndex;
               } m_alphapixelate;
               struct RADIAL_UNVEIL
               {
                  int m_iRadius;
                  int m_iRadiusIncrement;
               } m_radialunveil;
            } m_data;
            double      m_dAlpha;

            enum EAlign
            {
               AlignTop,
               AlignBottom,
               AlignLeft,
               AlignRight,
               AlignLeftTop,
               AlignTopRight,
               AlignBottomLeft,
               AlignRightBottom,
               AlignCenter,
               AlignCenterOut,
            };
         
         

         protected:
            ETransitionEffect   m_etransitioneffect;
            size            m_size;
            int               m_cx;
            int               m_cy;
            double            m_dRate;
            double            m_dRateEx;
            double            m_phi;
            int               m_iRadius;
         
         public:
            int            m_iStepRepeatCount;
            rect         m_rect;
            point         m_point;
            rect         m_rectIn;
            rect         m_rectOut;
            rect         m_rectA;
            rect         m_rectB;
            rect         m_rectC;
            rect         m_rectD;
            base_array <point, point> m_pointa;
            base_array <point, point> m_pointa2;
            int_array   m_ia;
            int            m_iStep; // 0 - Inactive, >= 1 Active
            int            m_iStepCount; // -1 - Infinite, 0 and 1 - invalid, > 1 count out
         public:
            void Start(int cx, int cy, double dRate, double dRateEx);
   //         void Go(ETransitionEffect eType);
            void Go();

         

            void GetSliceRect(
               LPRECT   lprect,
               EAlign   aelign);

            void GetSliceRect(
               LPRECT   lprect,
               EAlign   aelign,
               double   dRate,
               double   dRateMinus);

            void GetRectAB(LPRECT lprectA, LPRECT lprectB);
            void GetRectABCD(LPRECT lprectA, LPRECT lprectB, LPRECT lprectC, LPRECT lprectD);
            void GetHorizontalHexagon(LPRECT lprect, LPPOINT lppointa);
            int FindRandomEnglobingEllipse(LPCRECT lprect, LPRECT lprectCircle, int iMaxRand);
            int FindRandomEnglobingCircle(LPCRECT lprect, LPRECT lprectCircle, int iMaxRand);
            void GetRect(LPPOINT lppoint, LPCRECT lpcrect);
            void GetRect(
               LPRECT   lprect);
            void GetRect(
               LPRECT lprect,
               double   dRate,
               double   dRateEx);
            void GetRect(
               LPRECT   lprect,
               EAlign   ealign);
            void GetRect(
               LPRECT   lprect,
               EAlign   ealign,
               double   dRate);
            void GetRect(
               LPRECT   lprect,
               EAlign   ealign,
               int      cx,
               int      cy,
               double   dRate);
            void GetRotateRect(int w, int h, int i, int j, double phi, LPPOINT lppoint);
            void GetRotateRect(int i, int j, LPPOINT lppoint);
            void TranslateRect(LPRECT lprect, int w, int h, int i, int j);
            void GetRotateHexagon(int iRadius, int i, int j, double phi, LPPOINT lppoint);
            void GetRotateHexagon(int i, int j, LPPOINT lppoint);
            void Initialize(ETransitionEffect eeffect, int cx, int cy, TransitionEffect & effect);
            void Finalize();
         
            static void GetSimplePolyBox(LPRECT lprect, LPPOINT lppoint, int iCount);

         };

         friend class Tool001;
   
         bool              m_bInitialized;
         bool              m_bActive;
         DWORD               m_dwTransitionStepLastRunTime;
         DWORD               m_dwDelay;
         bool               m_bTransitionStepRunActive;
         bool               m_bTransitionStepPostActive;
         DWORD               m_dwTransitionStepPostActive;
   
         DWORD               m_dwLastTransitionTime;

         int               m_iVisual;

         ::radix::thread *      m_pthreadRunStep;
   //      ETransitionEffect               m_etype;
   //      ETransitionEffect               m_etypeNew;

         int m_iType;

         comparable_array < ETransitionEffect, ETransitionEffect >
                           m_etypea;

         Tool001            m_tool001;
         CEvent            m_eventStartTransition;
         CEvent            m_eventThreadExit;
         bool              m_bDestroy;
      
      protected:
         void RunStepProcLevel1(rect_array & arra); 
         void RunStepProcLevel2(); 
      public:
         ETransitionEffect get_type();
         void StepBack();
         void StepNext();
         int CalcRepeatCount();
         EDirection GetDirection(ETransitionEffect eeffect);
         EAlign GetAlign(ETransitionEffect effect);
         void DisableEffect(ETransitionEffect eeffect);
         void EnableEffect(ETransitionEffect eeffect);
      
         //void _Init(ETransitionEffect etypeNew);

         TransitionEffect(Main & main);
         virtual ~TransitionEffect();
         void OnTimer();
         void Reset();
         bool IsActive();
         bool TestEnd();
         void End();
         void RenderBuffer(rect_array & rectaUpdate);
      
      
         ::radix::thread * CreateRunStepThread();
         void Initialize();
         void _Final();
         void _Init();
         void Restart();
         //void RunStep_();
         void OnNoPrecisionThousandMillisTimer();
         static UINT AFX_CDECL ThreadProcRunStep(LPVOID lpParameter);

      };

   } // namespace backview

} // namespace gcom


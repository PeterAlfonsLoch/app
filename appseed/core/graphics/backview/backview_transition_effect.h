#pragma once

namespace backview
{



   class CLASS_DECL_CORE TransitionEffect :
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
               int32_t m_iTileCount;
               int32_t m_iFrameCount;
               int32_t m_iGroupCount;
            } m_sliceframe;
            struct TILES
            {
               int32_t m_iTilesX;
               int32_t m_iTilesY;
               int32_t m_iTiles;
            } m_tiles;
            struct ALPHA_PIXELATE
            {
               int32_t m_c1;
               int32_t m_c2;
               int32_t m_iSizeIndex;
            } m_alphapixelate;
            struct RADIAL_UNVEIL
            {
               int32_t m_iRadius;
               int32_t m_iRadiusIncrement;
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
         int32_t               m_cx;
         int32_t               m_cy;
         double            m_dRate;
         double            m_dRateEx;
         double            m_phi;
         int32_t               m_iRadius;

      public:
         int32_t            m_iStepRepeatCount;
         rect         m_rect;
         point         m_point;
         rect         m_rectIn;
         rect         m_rectOut;
         rect         m_rectA;
         rect         m_rectB;
         rect         m_rectC;
         rect         m_rectD;
         array <point, point> m_pointa;
         array <point, point> m_pointa2;
         int_array   m_ia;
         index            m_iStep; // 0 - Inactive, >= 1 Active
         ::count m_iStepCount; // -1 - Infinite, 0 and 1 - invalid, > 1 ::count out
         index m_iFrame;
      public:
         void Start(int32_t cx, int32_t cy, double dRate, double dRateEx);
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

         void GetSliceRect(
            int32_t      cx,
            int32_t      cy,
            LPRECT   lprect,
            EAlign   aelign,
            double   dRate,
            double   dRateMinus);


         void GetRectAB(LPRECT lprectA, LPRECT lprectB);
         void GetRectABCD(LPRECT lprectA, LPRECT lprectB, LPRECT lprectC, LPRECT lprectD);
         void GetHorizontalHexagon(LPRECT lprect, LPPOINT lppointa);
         int32_t FindRandomEnglobingEllipse(LPCRECT lprect, LPRECT lprectCircle, int32_t iMaxRand);
         int32_t FindRandomEnglobingCircle(LPCRECT lprect, LPRECT lprectCircle, int32_t iMaxRand);
         void GetRect(LPPOINT lppoint, const RECT & rect);
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
            int32_t      cx,
            int32_t      cy,
            double   dRate);
         void GetRotateRect(int32_t w, int32_t h, int32_t i, int32_t j, double phi, LPPOINT lppoint);
         void GetRotateRect(int32_t i, int32_t j, LPPOINT lppoint);
         void TranslateRect(LPRECT lprect, int32_t w, int32_t h, int32_t i, int32_t j);
         void GetRotateHexagon(int32_t iRadius, int32_t i, int32_t j, double phi, LPPOINT lppoint);
         void GetRotateHexagon(int32_t i, int32_t j, LPPOINT lppoint);
         void Initialize(ETransitionEffect eeffect, int32_t cx, int32_t cy, TransitionEffect & effect);
         void Finalize();

         static void GetSimplePolyBox(LPRECT lprect, LPPOINT lppoint, int32_t iCount);

      };

      friend class Tool001;

      bool                 m_bRun;
      bool                 m_bInitialized;
      bool                 m_bActive;
      uint32_t                m_dwTransitionStepLastRunTime;
      uint32_t                m_dwDelay;
      bool                 m_bTransitionStepRunActive;
      bool                 m_bTransitionStepPostActive;
      uint32_t                m_dwTransitionStepPostActive;

      uint32_t                m_dwLastTransitionTime;

      index                  m_iVisual;

      ::thread *    m_pthreadRunStep;
//      ETransitionEffect               m_etype;
//      ETransitionEffect               m_etypeNew;

      index m_iType;

      comparable_array < ETransitionEffect, ETransitionEffect >
                        m_etypea;

      int_array         m_iaVisual;

      Tool001            m_tool001;
      event            m_eventStartTransition;
      event            m_eventThreadExit;
      bool              m_bDestroy;

   protected:
      void RunStepProcLevel1(rect_array & arra);
      void RunStepProcLevel2();
   public:
      ETransitionEffect get_type();
      void StepBack();
      void StepNext();
      int32_t CalcRepeatCount();
      ::gcom::e_direction GetDirection(ETransitionEffect eeffect);
      ::gcom::e_align GetAlign(ETransitionEffect effect);
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


      ::thread * CreateRunStepThread();
      void Initialize();
      void _Final();
      void _Init();
      void Restart();
      //void RunStep_();
      void OnNoPrecisionThousandMillisTimer();
      static UINT c_cdecl ThreadProcRunStep(LPVOID lpParameter);

   };

} // namespace backview


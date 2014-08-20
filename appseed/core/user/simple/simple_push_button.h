#pragma once


class CLASS_DECL_CORE SimplePushButton :
   public ::user::button
{
public:


   class CLASS_DECL_CORE ColorSchema
   {
   public:
      color::hls   m_hlsRateHover;
      color::hls   m_hlsRatePush;
   };

   //COLORREF       m_crPush;
   //COLORREF       m_crPushHover;
   //COLORREF       m_crNormal;
   //COLORREF       m_crHover;
   COLORREF         m_cr; // Normal color

   bool             m_bHover;
   bool             m_bPush;
   bool             m_bTransitionEffect;
   index            m_iStepCount;
   index            m_iStep;

   ColorSchema *    m_pcolorschema;

   SimplePushButton(sp(::axis::application) papp);
   virtual ~SimplePushButton();


   virtual void install_message_handling(::message::dispatch * pinterface);

#ifdef WINDOWSEX
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
#endif
   virtual bool pre_create_window(::user::create_struct& cs);

   void SetColorSchema(ColorSchema * pschema);
   void TransitionEffectStart();
   void TransitionEffectRunStep();
   bool IsPushed();
   void push(bool bPush = true);
   void Hover(bool bHover = true);
   void UpdateHover();
   void _001OnDraw(::draw2d::graphics * pdc);

   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnDestroy);
   DECL_GEN_SIGNAL(_001OnTimer);


};




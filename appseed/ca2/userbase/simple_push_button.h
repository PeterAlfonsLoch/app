#pragma once


class CLASS_DECL_ca SimplePushButton :
   public ::userbase::button
{
public:


   class CLASS_DECL_ca ColorSchema
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
   int              m_iStepCount;
   int              m_iStep;

   ColorSchema *    m_pcolorschema;

   SimplePushButton(::ax::application * papp);
   virtual ~SimplePushButton();


   virtual void install_message_handling(::gen::message::dispatch * pinterface);

#ifdef WINDOWS
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
#endif
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   void SetColorSchema(ColorSchema * pschema);
   void TransitionEffectStart();
   void TransitionEffectRunStep();
   bool IsPushed();
   void push(bool bPush = true);
   void Hover(bool bHover = true);
   void UpdateHover();
   void _001OnDraw(::ax::graphics * pdc);

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnTimer)


};




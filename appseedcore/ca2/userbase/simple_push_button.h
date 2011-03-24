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
   SimplePushButton(::ca::application * papp);

   //COLORREF      m_crPush;
   //COLORREF      m_crPushHover;
   //COLORREF      m_crNormal;
   //COLORREF      m_crHover;
   COLORREF      m_cr; // Normal color

   bool            m_bHover;
   bool            m_bPush;
   bool            m_bTransitionEffect;
   int            m_iStepCount;
   int            m_iStep;

   ColorSchema *   m_pcolorschema;

// Operations
public:
   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
   void SetColorSchema(ColorSchema * pschema);
   void TransitionEffectStart();
   void TransitionEffectRunStep();
   bool IsPushed();
   void push(bool bPush = true);
   void Hover(bool bHover = true);
   void UpdateHover();
   void _001OnDraw(::ca::graphics * pdc);
   virtual ~SimplePushButton();

protected:
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnTimer)
};


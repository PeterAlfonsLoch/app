#pragma once

namespace mixeruserbase
{

   class CLASS_DECL_ca slider :
      public ::user::interaction,
      public mixer::LevelControl
   {

   public:
      slider(::ca::application * papp);
      virtual ~slider();

      bool      m_bPresenceOnHover;
      virtual bool Initialize(::user::interaction * pwndParent, UINT uiId);
      virtual int _GetDlgCtrlID();

      ::user::interaction * GetWnd();

   protected:
      bool               m_bHover;
      int               m_iLineSize;
      int               m_iPageSize;
      int               m_iRangeMin;
      int               m_iRangeMax;
      int               m_iPos;
      int               m_iTrackingPos;
      int               m_eorientation;
      bool              m_bTracking;
      bool              m_bThumbHover;
      point             m_ptTrackOffset;
      //    ::ca::bitmap     m_bitmapBuffer;
      //    ::ca::bitmap     m_bitmapBufferOriginal;
      //    ::ca::graphics_sp         m_dcBuffer;
      ::ca::pen_sp      m_penThumbA;
      ::ca::pen_sp      m_penThumbB;
      ::ca::pen_sp      m_penHoverA;
      ::ca::pen_sp      m_penHoverB;
      int               m_iMargin;
      mutex            m_mutexPaint;



   // Operations
   public:
      void UpdateDrawingObjects();
      bool GetPageARect(LPRECT lpRectClient, LPRECT lpRectTrack,  LPRECT lpRect);
      bool GetPageBRect(LPRECT lpRectClient, LPRECT lpRectTrack,  LPRECT lpRect);
      bool GetThumbRect(LPRECT lpRect);

      bool IsHover();
      void DoHoverSmartUpdate();
      void SetOrientation(e_orientation orientation);
      
      virtual void _001OnDraw(::ca::graphics * pdc);

      double GetRate() const;
      void SetRate(double rate);
   //   CXfplayerView * GetParentLyricView();
   //    CTransparentWndContainer * GetTransparentWndContainer();
      void  SetPos(int iPos);
      int   GetPos() const;
      void  SetRange(int iMin, int iMax, bool bRedraw);
      void  SetRange(int iMin, int iMax);
      void  SetRangeMax(int iMax, bool bRedraw);
      void  SetRangeMin(int iMin, bool bRedraw = false);
      void  GetRange(int & iMin, int & iMax) const;
      int   GetRangeMin() const;
      int   GetRangeMax()  const;
      void  SetPageSize(int iPageSize);
      int   GetPageSize() const;
      void  SetLineSize(int iLineSize);
      int   GetLineSize() const; 

      int   ScrollLineA();
      int   ScrollLineB();
      int   ScrollPageB();
      int   ScrollPageA();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

   protected:
       int SetTrackingPos(point point);


   protected:
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnSize)
   };

} // namespace mixeruserbase

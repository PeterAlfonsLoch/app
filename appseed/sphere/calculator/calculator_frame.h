#pragma once


namespace calculator
{


   class CLASS_DECL_SPHERE frame : 
      public simple_frame_window
   {
   public: 


      
      
      sp(image_list)               m_pimagelist;
      bool                       m_bTimerOn;


      frame(::aura::application * papp);
      virtual ~frame();

      virtual bool pre_create_window(::user::create_struct& cs);

      void ShowControlBars(bool bShow);
      
      
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate);
      void OnTimer(UINT nIDEvent);

   };

} // namespace calculator





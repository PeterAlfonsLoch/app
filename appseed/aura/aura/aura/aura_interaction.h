#pragma once


namespace aura
{


   class CLASS_DECL_AURA interaction :
      virtual public command_target,
      virtual public ::aura::draw_interface
   {
   public:

      
      void *         m_pvoidUserInteraction; // ::user::interaction * 


      interaction();
      virtual ~interaction();

      inline oswindow get_safe_handle() const;

#ifdef WINDOWSEX
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);
#endif

      virtual bool SetPlacement(const RECT & rect,UINT nFlags = SWP_SHOWWINDOW);

   };


} // namespace aura




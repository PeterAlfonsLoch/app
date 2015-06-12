#pragma once


namespace user
{


   class CLASS_DECL_AURA elemental:
      virtual public command_target,
      virtual public ::aura::draw_interface
   {
   public:


      void *         m_pvoidUserInteraction; // ::user::elemental * 


      elemental();
      virtual ~elemental();

      inline oswindow get_safe_handle() const;

#ifdef WINDOWSEX
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);
#endif

      virtual bool SetPlacement(const RECT & rect,UINT nFlags = SWP_SHOWWINDOW);

   };


} // namespace aura




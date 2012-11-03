#pragma once




namespace user
{
   class interaction;
   class frame_window_interface;

   class CLASS_DECL_ca window_interface :
      virtual public elemental,
      virtual public command_target,
      virtual public text_interface,
      virtual public check_interface,
      virtual public draw_interface
   {
   public:

      enum ETranslucency
      {
         TranslucencyNone,
         TranslucencyPresent,
         TranslucencyTotal,
      };

      enum e_message
      {
         MessageBaseWndGetProperty = WM_USER + 96,
         MessageProperty,
         MessageGeneralEvent,
      };

      enum EProperty
      {
         PropertyBaseWndInterface = 0,
         PropertyDrawBaseWndInterface,
      };

      enum EGeneralEvent
      {
         GeneralEventPosCreate1,
         GeneralEventPosCreate2,
         GeneralEventPosCreate3,
         GeneralEventPosCreate4,
         GeneralEventPosCreate5,
      };

      interaction *                       m_pguie;
      // window rectangle relative to the parent
      // this rectangle comes before in importance compared to m_rectWindow
      // m_rectWindow should be sychronized and recalculated based
      // on m_rectParentClient values of the window and its ascendants.
      rect64                              m_rectParentClient;
      bool                                m_bVisible;
      bool                                m_bVoidPaint;
      draw_interface *             m_pdrawinterfaceBackground;
      bool                                m_bBackgroundBypass;
      ETranslucency                       m_etranslucency;




      window_interface();
      window_interface(::ca::application * papp);
      virtual ~window_interface();


      virtual bool _001IsWindowEnabled();
      virtual void _001EnableWindow(bool bEnable = true);
      virtual void _000OnDraw(::ca::graphics * pdc);

      //window_interface * _001GetParent() const;
      //virtual bool _001IsFrameWnd();
      //user::frame_window_interface * _001GetParentFrame() const;
      //bool Attach(oswindow_ hwnd);

      virtual void PreSubClassWindow();


      virtual void GetClientRect(LPRECT lprect);
      virtual void GetClientRect(__rect64 * lprect);
      virtual void GetWindowRect(LPRECT lprect);
      virtual void GetWindowRect(__rect64 * lprect);
      virtual void ClientToScreen(LPRECT lprect);
      virtual void ClientToScreen(__rect64 * lprect);
      virtual void ClientToScreen(LPPOINT lppoint);
      virtual void ClientToScreen(__point64 * lppoint);
      virtual void ScreenToClient(LPRECT lprect);
      virtual void ScreenToClient(__rect64 * lprect);
      virtual void ScreenToClient(LPPOINT lppoint);
      virtual void ScreenToClient(__point64 * lppoint);


      virtual window_interface * window_interface_get_parent();


      /*oswindow_ GetHandle() const;
      DWORD GetStyle() const;
      DWORD GetExStyle() const;
      bool ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT uiFlags);
      bool ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT uiFlags);
      static bool PASCAL ModifyStyle(oswindow_ hwnd, DWORD dwRemove, DWORD dwAdd, UINT uiFlags);
      static bool PASCAL ModifyStyleEx(oswindow_ hwnd, DWORD dwRemove, DWORD dwAdd, UINT uiFlags);

      LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
      bool PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);*/

   // Window size and position Functions
      /*bool IsIconic() const;
      bool IsZoomed() const;

      int GetWindowText(string & str) const;
      int GetWindowText(wchar_t * lpsz, int iLen) const;
      int GetWindowTextLen() const;*/




      virtual void install_message_handling(gen::message::dispatch * pinterface);

      virtual void _on_start_user_message_handler();
      static window_interface * g_pwndLastLButtonDown;


      virtual void UpdateWindow();
      virtual void Invalidate(bool bErase = TRUE);
      /*void InvalidateRect(LPCRECT lprect, bool bErase = TRUE);
      void InvalidateRgn(::ca::region* prgn, bool bErase = TRUE);
      void ValidateRect(LPCRECT lprect);
      void ValidateRgn(::ca::region* prgn);
      bool ShowWindow(int iCmdShow);
      bool IsWindowVisible() const;
      bool RedrawWindow(LPCRECT lpRectUpdate = NULL,
         ::ca::region* prgnUpdate = NULL,
         UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
      bool SetTimer(UINT nIDEvent, UINT nElapse, void (CALLBACK* lpfnTimer)(oswindow_, UINT, UINT, DWORD));
      bool KillTimer(int nIDEvent);
      bool SetWindowPos(const ::ca::window* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
      ::ca::window * SetFocus();*/


      /*::ca::graphics * GetDC();
      void  ReleaseDC(::ca::graphics * pdc);*/

      bool RedrawOptimize(LPRECT lprectOut, LPCRECT lpcrect1, LPCRECT lpcrect2);
      void RedrawOptimize(rect_array & base_array);
      bool _001IsBackgroundBypass();
      bool _001IsTransparent();
      bool _001IsTranslucent();
      bool _001HasTranslucency();

      /*
      virtual void _001SetWindowPos(const ::ca::window* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
      virtual void _001SetFocus();
      virtual void _001ShowWindow(int iShow);
      virtual void _001ScreenToClient(LPPOINT lppoint);
      */

      ETranslucency _001GetTranslucency();






      virtual void _001RedrawWindow();
      virtual void _001DrawBackground(::ca::graphics * pdc, LPRECT lprect);


      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_VSIGNAL(_001OnBaseWndGetProperty)

      virtual LRESULT _001BaseWndGetProperty(EProperty eproperty, LPARAM lparam);

      virtual interaction * get_guie();
      virtual ::ca::window * get_wnd();

      enum EOptimize
      {
         OptimizeNone,
         OptimizeThis,
      };

      //void Optimize001(
      //   user::HwndTree::Array & hwndtreea,
      //   LPCRECT lpcrect);

      //EOptimize Optimize001(
      //   user::HwndTree::Array & hwndtreea,
      //   HRGN hrgn);

      //EOptimize Optimize001(
      //   user::HwndTree & hwndtree,
      //   HRGN hrgn);

      void Optimize008(
         user::HwndTree::Array & hwndtreea,
         LPCRECT lpcrect);

      EOptimize Optimize008(
         user::HwndTree::Array & hwndtreea,
         HRGN hrgn);

      EOptimize Optimize008(
         user::HwndTree & hwndtree,
         HRGN hrgn);



      void TwfGetWndArray(user::LPWndArray & wndpa);
      void TwfGetWndArray(user::HWNDArray & hwnda);

      virtual bool Redraw(rect_array & recta);
      virtual bool Redraw(LPCRECT lprect = NULL, ::ca::region * prgn = NULL);
      virtual bool Redraw(::ca::graphics * pdc);

      void _001BaseWndInterfaceMap();

   };

} // namespace user


#include "user/user_buffer.h"
#include "user/user_window_map.h"
#include "gen/gen_keeper.h"
#include "ex1/ex1_seekable.h"
#include "ex1/ex1_reader.h"
#include "ex1/ex1_writer.h"
#include "ex1/ex1_stream.h"
#include "ex1/ex1_byte_stream.h"
#include "ex1/ex1_stream2.h"
#include "ex1/ex1_str_stream.h"

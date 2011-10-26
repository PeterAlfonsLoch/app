#pragma once

class biteditor_view;

namespace biteditor
{

   class ascii_box : 
      public ::user::interaction
   {
   public:

      ::ca::font_sp                 m_spfont;

      point                         m_pt;
      size                          m_size;

      biteditor_view *              m_pview;
      bool                          m_bMouseDown;

      char *                        m_pchLineBuffer;

      
      point                         m_ptSelStart;
      bool                          m_bFocus;
      bool                          m_bCaretOn;
      DWORD                         m_dwLastCaret;
      DWORD                         m_dwCaretTime;
      int                           m_iLineOffset;
      int                           m_y;
      bool                          m_bGetTextNeedUpdate;


      ascii_box(::ca::application * papp);

      void read_line(string & str, int iLine);

      void _001OnKeyboardFocusTimer(biteditor_view * pview, int iTimer);

      void on_update();

      file_position char_hit_test(biteditor_view * pview, ::ca::graphics * pdc, int x, int y);

      virtual void _001OnDraw(::ca::graphics * pdc);

      void _001GetViewSel(file_position &iSelStart, file_position &iSelEnd);

      void _001OnLButtonDown(user::elemental * pview, gen::signal_object * pobj);
      void _001OnLButtonUp(gen::signal_object * pobj);
      void _001OnCalcLayout(biteditor_view * pview, ::ca::graphics * pdc);
      void _001OnMouseMove(user::elemental * pview, gen::signal_object * pobj);
      void _001OnChar(biteditor_view * pview, gen::signal_object * pobj);
      void _001OnSysChar(biteditor_view * pview, gen::signal_object * pobj);
      void _001OnCalcLayoutProc(biteditor_view * pview, ::ca::graphics * pdc);

      void SetFile(ex1::file * pfile);
      void OnFileUpdate();

      int SelToColumn(biteditor_view * pview, file_position iSel);
      int64_t SelToLine(biteditor_view * pview, file_position iSel);
      file_position LineColumnToSel(biteditor_view * pview, int64_t iLine, int iColumn);

      void OneLineUp(biteditor_view * pview);

      void IndexRegisterDelete(file_position iSel, file_size iCount);
      void IndexRegisterInsert(file_position iSel, const char * lpcszWhat);

   };

} // namespace biteditor
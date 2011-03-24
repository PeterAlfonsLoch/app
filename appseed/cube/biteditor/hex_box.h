#pragma once

namespace biteditor
{

   class hex_box : 
      public ::user::interaction
   {
   public:
      int                     m_iSelStart;
      int                     m_iSelEnd;
      int                     m_iViewOffset; // in bytes
      int                     m_iViewSize; // in bytes
      int                     m_iColumn;

      int                     m_iLineSize;
      char *                  m_pchLineBuffer;

      ex1::edit_file *        m_peditfile;

      ::ca::font_sp            m_spfont;

      size                    m_size;

      biteditor_view *        m_pview;
      bool                     m_bMouseDown;
      point                     m_ptSelStart;
      bool                    m_bFocus;
      bool                    m_bCaretOn;
      DWORD                   m_dwLastCaret;
      DWORD                   m_dwCaretTime;
      int                     m_iLineOffset;
      stringa               m_straLines;
      int                     m_y;
      bool                    m_bGetTextNeedUpdate;

      hex_box(::ca::application * papp);

      void ReadLine(string &str);

      void _001OnKeyboardFocusTimer(biteditor_view * pview, int iTimer);

      void on_update();

      int char_hit_test(biteditor_view * pview, ::ca::graphics * pdc, int x, int y);

      virtual void _001OnDraw(::ca::graphics * pdc);
      void _001GetSelText(string & str) const; 

      void _001OnGetText(biteditor_view * pview);
      void _001GetViewText(biteditor_view * pview, string & str);
      void _001GetViewSel(int &iSelStart, int &iSelEnd);

      void _001OnLButtonDown(user::elemental * pview, gen::signal_object * pobj);
      void _001OnLButtonUp(gen::signal_object * pobj);
      void _001OnCalcLayout(biteditor_view * pview, ::ca::graphics * pdc);
      void _001OnMouseMove(user::elemental * pview, gen::signal_object * pobj);
      void _001OnChar(biteditor_view * pview, gen::signal_object * pobj);
      void _001OnSysChar(biteditor_view * pview, gen::signal_object * pobj);
      void _001OnCalcLayoutProc(biteditor_view * pview, ::ca::graphics * pdc);

      void SetFile(ex1::file * pfile);
      void OnFileUpdate();

      int SelToColumn(biteditor_view * pview, int iSel);
      int SelToLine(biteditor_view * pview, int iSel);
      int LineColumnToSel(biteditor_view * pview, int iLine, int iColumn);

      void OneLineUp(biteditor_view * pview);

      void IndexRegisterDelete(int iSel, int iCount);
      void IndexRegisterInsert(int iSel, const char * lpcszWhat);

   };

} // namespace biteditor
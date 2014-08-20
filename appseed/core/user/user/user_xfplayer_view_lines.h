#pragma once


class CLASS_DECL_CORE XfplayerViewLines :
   virtual public spa(XfplayerViewLine),
   virtual public signalizable
{
public:


   XfplayerViewLineSelection   m_selection;
   sp(::user::interaction)      m_pinteraction;
   index                        m_iFirstVisible;
   index                        m_iLastVisible;


   XfplayerViewLines(sp(::axis::application) papp);


   void SetBlend(double dBlend);
   index FindLine(XfplayerViewLine * pline);
   void SetRenderWindow(::window_sp pwindow);
   void SetEffect(int32_t iEffect);
   void set_user_interaction(sp(::user::interaction) pinteraction);
   void Prepare(XfplayerViewLine * lpViewLine);
   void Prepare();

   index GetFirstVisibleLineIndex();
   index GetLastVisibleLineIndex();
   void OnChildSetVisible(XfplayerViewLine * lpViewLine, bool bVisible);

   user::e_line_hit hit_test(POINT &ptCursor, strsize &iLine, strsize &iChar);

   void InstallMessageHandling(::message::dispatch *pinterface);

   virtual ~XfplayerViewLines();

   DECL_GEN_SIGNAL(OnMouseMove);
   DECL_GEN_SIGNAL(OnLButtonDown);
   DECL_GEN_SIGNAL(OnLButtonUp);
   DECL_GEN_SIGNAL(OnTimer);
   DECL_GEN_SIGNAL(OnSetCursor);

   XfplayerViewLineSelection & GetSelection();

   void get_sel_text(string & strSelText, const char * pszLineSeparator = "\r\n");
   string get_sel_text(const char * pszLineSeparator = "\r\n");

   void get_text(string & strSelText, const char * pszLineSeparator = "\r\n");
   string get_text(const char * pszLineSeparator = "\r\n");

};




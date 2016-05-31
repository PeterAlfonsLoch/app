#pragma once

void RedirectIOToConsole();


class std_out_buffer:
   virtual public ::file::stream_buffer
{
public:


   std_out_buffer() {}
   virtual ~std_out_buffer(){}


   void write(const void * lpBuf,memory_size_t nCount);


};

//class console_ostream:
//   virtual public ::file::plain_text_ostream
//{
//public:
//
//   console_ostream(): ::file::plain_text_ostream(canew(std_out_buffer())){}
//   virtual ~console_ostream(){}
//
//};

namespace console
{

   const int WHITE    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
   const int RED      = FOREGROUND_RED | FOREGROUND_INTENSITY;
   const int BLUE     = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
   const int DARKBLUE = FOREGROUND_BLUE;
   const int CYAN     = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
   const int MAGENTA  = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
   const int YELLOW   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
   const int BLACK    = 0;


   class CLASS_DECL_ACE window:
      virtual public ::object
   {
   public:


      ::file::plain_text_ostream   cout;


      virtual void redirect_io();
      virtual void SetWindowSize(int iHeight,int iWidth) = 0;
      virtual void SetCursorVisibility(bool show) = 0;
      virtual void SetCursorPosition(int y,int x) = 0;
      virtual void SetTextColor(int color) = 0;
      virtual void SetScreenColor(int color,int iLineStart = 0,int iLineCount = -1) = 0;
      virtual void write(const char * psz) = 0;


   };



   class window_composite:
      virtual public window
   {
   public:





      window * m_p;

      window_composite()
      {
         m_p = NULL;
      }

      window_composite(window * p):
         object(p->get_app()),
         m_p(p)
      {
         cout.m_spbuffer = m_p->cout.m_spbuffer;
      }

      virtual void redirect_io() { m_p->redirect_io(); }
      virtual void SetWindowSize(int iHeight,int iWidth) { m_p->SetWindowSize(iHeight,iWidth); }
      virtual void SetCursorVisibility(bool show)  { m_p->SetCursorVisibility(show); }
      virtual void SetCursorPosition(int y,int x)  { m_p->SetCursorPosition(y,x); }
      virtual void SetTextColor(int color)  { m_p->SetTextColor(color); }
      virtual void SetScreenColor(int color,int iLineStart = 0,int iLineCount = -1)  { m_p->SetScreenColor(color,iLineStart,iLineCount); }
      virtual void write(const char * psz)  { m_p->write(psz); }
      //virtual void write(const void * lpBuf,memory_size_t nCount);

   };



} // namespace console




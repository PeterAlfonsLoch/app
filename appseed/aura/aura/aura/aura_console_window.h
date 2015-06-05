#pragma once

void RedirectIOToConsole();


class std_out_buffer:
   virtual public ::file::stream_buffer
{
public:
   std_out_buffer() {}
   virtual ~std_out_buffer(){}
   void write(const void * lpBuf,::primitive::memory_size nCount)
   {
//      string str((const char * ) lpBuf,MIN(strnlen_s((const char *) lpBuf, nCount), nCount));
  //    printf("%s",str);
          DWORD dw= 0;
          ::WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),lpBuf,nCount,&dw,NULL);

   }


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

class CLASS_DECL_AURA console_window_base:
   virtual public ::object
{
public:

   ::file::plain_text_ostream   cout;


   virtual void redirect_io();
   virtual void SetWindowSize(int iHeight,int iWidth) = 0;
   virtual void SetCursorVisibility(bool show) = 0;
   virtual void SetCursorPosition(int y,int x) = 0;
   virtual void SetTextColor(int color) = 0;
   virtual void SetScreenColor(int color) = 0;
   virtual void write(const char * psz) = 0;


};



class console_window_composite:
   virtual public console_window_base
{
public:


   


   console_window_base * m_p;

   console_window_composite()
   {
      m_p = NULL;
   }

   console_window_composite(console_window_base * p):
      object(p->get_app()),
      m_p(p)
   {
      cout.m_spbuffer = m_p->cout.m_spbuffer;
   }

   virtual void SetWindowSize(int iHeight,int iWidth) {   m_p->SetWindowSize(iHeight,iWidth);   }
   virtual void SetCursorVisibility(bool show)  { m_p->SetCursorVisibility(show); }
   virtual void SetCursorPosition(int y,int x)  { m_p->SetCursorPosition(y,x); }
   virtual void SetTextColor(int color)  { m_p->SetTextColor(color); }
   virtual void SetScreenColor(int color)  { m_p->SetScreenColor(color); }
   virtual void write(const char * psz)  { m_p->write(psz); }
   //virtual void write(const void * lpBuf,::primitive::memory_size nCount);

};

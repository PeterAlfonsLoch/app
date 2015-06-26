#include "framework.h"
//#include <io.h>


namespace windows
{

   console::console()
   {
      cout.m_spbuffer = canew(std_out_buffer());
      AllocConsole();

   }

   console::~console()
   {
      FreeConsole();
   }


   // maximum mumber of lines the output console should have

   static const WORD MAX_CONSOLE_LINES = 500;

   void console::redirect_io()
   {

      int hConHandle;

      long lStdHandle;

      CONSOLE_SCREEN_BUFFER_INFO coninfo;

      FILE *fp;

      // allocate a console for this app

      // set the screen buffer to be big enough to let us scroll text

      GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),

       &coninfo);

      coninfo.dwSize.Y = MAX_CONSOLE_LINES;

      SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),

       coninfo.dwSize);

      // redirect unbuffered STDOUT to the console

      lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);

      hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

      fp = _fdopen(hConHandle,"w");

      *stdout = *fp;

      setvbuf(stdout,NULL,_IONBF,0);

      // redirect unbuffered STDIN to the console

      lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);

      hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

      fp = _fdopen(hConHandle,"r");

      *stdin = *fp;

      setvbuf(stdin,NULL,_IONBF,0);

      // redirect unbuffered STDERR to the console

      lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);

      hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);

      fp = _fdopen(hConHandle,"w");

      *stderr = *fp;

      setvbuf(stderr,NULL,_IONBF,0);

       //make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog

       //point to console as well

         //ios::sync_with_stdio();

   }


   void console::SetWindowSize(int height,int width)
   {
      m_iH = height;
      m_iW = width;
      SMALL_RECT window;
      window.Top = 0;
      window.Left = 0;
      window.Bottom = height - 1;
      window.Right = width - 1;
      SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,&window);
      COORD buffer ={width,height};
      SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),buffer);
   }

   void console::SetCursorVisibility(bool show)
   {
      CONSOLE_CURSOR_INFO cursor;
      GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
      cursor.bVisible = show;
      SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
   }

   void console::SetCursorPosition(int y,int x)
   {
      COORD cursor ={x,y};
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cursor);
   }

   void console::SetTextColor(int color)
   {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
   }

   void console::SetScreenColor(int color, int iLineStart, int iLineCount)
   {
      COORD coord ={0,iLineStart};
      DWORD dwWritten;
      if(iLineCount < 0)
         iLineCount = m_iH + iLineCount + 1;
      if(iLineCount > m_iH - iLineStart)
         iLineCount = m_iH - iLineStart;
      FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color,iLineCount * m_iW,coord,&dwWritten);
   }

   void console::write(const char * psz)
   {
      
      DWORD dw= 0;
      ::WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),psz,strlen(psz),&dw, NULL);
      //fprintf("%s",psz);

   }

} // namespace windows




#include <windows.h>

#include <stdio.h>

#include <fcntl.h>

#include <io.h>

//#include <iostream>

//#include <fstream>

//#ifndef _USE_OLD_IOSTREAMS
//
//using namespace std;
//
//#endif


#pragma once


namespace windows
{


   class CLASS_DECL_AURA console_window:
      virtual public console_window_base
   {
   public:

      console_window();
      virtual ~console_window();

      void redirect_io();
      void SetWindowSize(int height,int width);
      void SetCursorVisibility(bool show);
      void SetCursorPosition(int y,int x);
      void SetTextColor(int color);
      void SetScreenColor(int color);
      void write(const char * psz);

   };


} // namespace windows





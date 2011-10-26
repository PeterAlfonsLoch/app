#pragma once


namespace spa
{

   class CLASS_DECL_____ canvas
   {
   public:

      int m_iMode;

      canvas();
      ~canvas();

      void on_paint(HDC hdc, LPCRECT lpcrect);


   };


} // namespace spa
#pragma once


class CLASS_DECL_c simple_font
{
public:

   
   HFONT                  m_hfont;


   simple_font();
   ~simple_font();

   bool create_point(int nPointSize, const char * lpszFaceName, simple_graphics & g);
   bool create_point_bold(int nPointSize, const char * lpszFaceName, int BOLD, simple_graphics & g);
   
   // aim to be all-platoform
   bool destroy();


   // platform-specific
   bool create_indirect(LPLOGFONT lplf);

};


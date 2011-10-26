#pragma once

namespace syllomatter
{

   class CLASS_DECL_CA2_TESSERACT main_frame : public simple_frame_window
   {
   public:


      simple_toolbar m_toolbar;


      main_frame(::ca::application * papp);
      virtual ~main_frame();


      bool LoadToolBar(const char * lpcszMatter);
   };

} // namespace syllomatter
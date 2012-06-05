#pragma once


namespace uinteraction
{


   class CLASS_DECL_ca frame : 
      virtual public gen::signalizable,
      virtual public ::radix::object
   {
   public:


      ::ca::type_info      m_typeinfoControlBoxButton;



      frame(::ca::application * papp);
      virtual ~frame();

      virtual void set_style(const char * pszStyle);
      virtual void OnInitializeAppearance();



   };


} // namespace window_frame





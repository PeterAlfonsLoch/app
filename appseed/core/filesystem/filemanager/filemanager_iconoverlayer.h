#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE iconoverlayer :
      virtual public ::object
   {
   public:


      iconoverlayer(sp(::aura::application) papp);
      virtual ~iconoverlayer();

      virtual bool initialize() = 0;
      virtual bool finalize() = 0;


      // give a chance to cache and optimize
      virtual void on_open_directory(const char * pszPath) = 0;

      virtual void overlay(const char * pszPath, ::draw2d::graphics * pgraphics, const RECT & rect) = 0;

   };


} // namespace filemanager
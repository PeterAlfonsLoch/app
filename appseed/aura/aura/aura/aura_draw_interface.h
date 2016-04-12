#pragma once


namespace aura
{

   class CLASS_DECL_AURA drawable:
      virtual public ::object
   {
   public:


      virtual void _001OnDraw(::draw2d::dib * pdib);

   };

   class CLASS_DECL_AURA draw_interface :
      virtual public drawable
   {
   public:


      virtual void _000OnDraw(::draw2d::dib * pdib) = 0;

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::dib * pdib) = 0;

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::dib * pdib) = 0;

      virtual bool GetWindowRect(LPRECT lprect) = 0;
      virtual bool GetWindowRect(RECT64 * lprect) = 0;
      virtual rect GetWindowRect() = 0;
      virtual rect64 GetWindowRect64() = 0;


      virtual ::window_graphics ** get_window_graphics() = 0;
      virtual oswindow get_handle() const = 0;

      virtual bool is_composite() = 0;


   };


} // namespace aura



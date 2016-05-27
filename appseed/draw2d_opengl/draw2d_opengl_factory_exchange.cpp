#include "framework.h"
#include "base/base/os/windows/windows_window_opengl.h"


WNDCLASSEX g_wcl = { 0 };
namespace draw2d_opengl
{


   factory_exchange::factory_exchange(::aura::application * papp) :
      object(papp)
   {

      MSG msg = { 0 };
      

      g_wcl.cbSize = sizeof(g_wcl);
      g_wcl.style = 0;
      g_wcl.lpfnWndProc = WindowProc;
      g_wcl.cbClsExtra = 0;
      g_wcl.cbWndExtra = 0;
      g_wcl.hInstance = ::GetModuleHandle("draw2d_opengl.dll");
      g_wcl.hIcon = NULL;
      g_wcl.hCursor = NULL;
      g_wcl.hbrBackground = 0;
      g_wcl.lpszMenuName = 0;
      g_wcl.lpszClassName = _T("GLLayeredWindowClass");
      g_wcl.hIconSm = 0;

      RegisterClassEx(&g_wcl);

      System.factory().cloneable_large < dib                   >  (System.type_info < ::draw2d::dib                  > ());
      System.factory().cloneable_large < graphics              >  (System.type_info < ::draw2d::graphics             > ());
      System.factory().cloneable_large < bitmap                >  (System.type_info < ::draw2d::bitmap               > ());
      System.factory().cloneable_large < pen                   >  (System.type_info < ::draw2d::pen                  > ());
      System.factory().cloneable_large < brush                 >  (System.type_info < ::draw2d::brush                > ());
      System.factory().cloneable_large < palette               >  (System.type_info < ::draw2d::palette              > ());
      System.factory().cloneable_large < region                >  (System.type_info < ::draw2d::region               > ());
      System.factory().cloneable_large < font                  >  (System.type_info < ::draw2d::font                 > ());
      System.factory().cloneable_large < path                  >  (System.type_info < ::draw2d::path                 > ());
      System.factory().cloneable_large < printer               >  (System.type_info < ::aura::printer                > ());
      System.factory().cloneable_large < window_opengl         >  (System.type_info < window_graphics                >());

   }


   factory_exchange::~factory_exchange()
   {
   }


} // namespace draw2d_opengl


#ifdef CUBE
void draw2d_factory_exchange(::aura::application * papp)
{
   draw2d_opengl::factory_exchange factoryexchange(papp);
}
#else
void ca2_factory_exchange(::aura::application * papp)
{
   draw2d_opengl::factory_exchange factoryexchange(papp);
}
#endif



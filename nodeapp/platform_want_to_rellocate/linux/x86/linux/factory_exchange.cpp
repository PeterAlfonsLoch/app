#include "StdAfx.h"

namespace win
{

   factory_exchange::factory_exchange(::ca::application * papp) :
      ::ca::ca(papp)
   {
      Application.factory().cloneable < WinStdioFile         >  (typeid(ex1::text_file       ));
      Application.factory().cloneable < WinFile              >  (typeid(ex1::file            ));
      Application.factory().cloneable < WinFileSet           >  (typeid(ex2::file_set        ));
      Application.factory().cloneable < WinFileSystem        >  (typeid(ex1::file_system     ));
      Application.factory().cloneable < WinFileException     >  (typeid(ex1::file_exception  ));
      Application.factory().cloneable < WinResource          >  (typeid(ex1::resource        ));
      Application.factory().cloneable < application          >  (typeid(::ex2::application   ));
      Application.factory().cloneable < WinStdioFile         >  (typeid(ex1::text_file       ));
      Application.factory().cloneable < dir                  >  (typeid(::ca::dir            ));
      Application.factory().cloneable < dib                  >  (typeid(::ca::dib            ));
      Application.factory().cloneable < graphics             >  (typeid(::ca::graphics       ));
      Application.factory().cloneable < bitmap               >  (typeid(::ca::bitmap         ));
      Application.factory().cloneable < pen                  >  (typeid(::ca::pen            ));
      Application.factory().cloneable < brush                >  (typeid(::ca::brush          ));
      Application.factory().cloneable < palette              >  (typeid(::ca::palette        ));
      Application.factory().cloneable < rgn                  >  (typeid(::ca::rgn            ));
      Application.factory().cloneable < font                 >  (typeid(::ca::font           ));
      Application.factory().creatable < window_draw          >  (typeid(::ca::window_draw    ));
      Application.factory().creatable < thread               >  (typeid(::ca::thread         ));
      Application.factory().creatable < window               >  (typeid(::ca::window         ));
      Application.factory().cloneable < draw_dib             >  (typeid(::ca::draw_dib       ));
      Application.factory().creatable < osi                  >  (typeid(::ca::osi            ));
      ::win::dib::s_initialize();
   }

   factory_exchange::~factory_exchange()
   {
   }

} // namespace win



void ca2_factory_exchange(::ca::application * papp)
{
   win::factory_exchange factoryexchange(papp);
}
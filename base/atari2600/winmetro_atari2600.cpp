#include "core/core/core.h"

#undef CoreApplication

[MTAThread]
int main(Array<String^>^)
{

   return app_core_main("m_app.exe : app=app-core/hellomultiverse wndfrm=rootkiller client_only");


}



/*[MTAThread]
int main(Array<String^>^)
{
   
   // No Depends
   
   return 0;

}
*/
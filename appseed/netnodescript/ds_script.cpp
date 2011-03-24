#include "StdAfx.h"

class ds_script : public netnodeScriptInstance
{
public:
   ds_script(netnodeScript * pscript) : netnodeScriptInstance(pscript){};
   virtual void run();
};

extern "C"  netnodeScriptInstance * __cdecl create_netnode_script_instance(netnodeScript * pscript)
{
   return dynamic_cast < netnodeScriptInstance * > (new ds_script(pscript));
}

void ds_script::run()
{
	print("<html>");
	print("<head>");
	print("</head>");
	print("<body>");
	print("<h1>Eu te amo Carlos Gustavo Cecyn Lundgren de quinze de novembro de mil novecentos e oitenta e quatro!</h1>");
	print("<h1>Assinado Camilo Sasuke Tsumanuma de dois de abril de mil novecentos e setenta e sete!</h1>");
	print("</body>");
	print("</html>");
}
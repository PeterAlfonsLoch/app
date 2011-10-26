#include "StdAfx.h"

class dynamic_source_script : public dynamic_source::script_instance
{
public:
   dynamic_source_script(dynamic_source::script * pscript) : dynamic_source::script_instance(pscript){};
   virtual void run();
};

extern "C"  dynamic_source::script_instance * __cdecl create_dynamic_source_script_instance(dynamic_source::script * pscript)
{
   return dynamic_cast < dynamic_source::script_instance * > (new dynamic_source_script(pscript));
}

void dynamic_source_script::run()
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
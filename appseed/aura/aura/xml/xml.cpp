#include "framework.h"
#include "xml_disp_option.h"
#include "xml_department.h"
#include "aura/primitive/primitive_property.h"


namespace xml
{


   CLASS_DECL_AURA string get(const property & prop, ::xml::disp_option * opt /*= &optDefault*/)
   {
      //   ::file::plain_text_ostream ostring;
      //   //ostring << (const char *)m_strName << "='" << (const char *)m_strValue << "' ";

      //   ostring << (const char *)m_strName << L"=" << (CHAR)opt->value_quotation_mark
      //      << (const char *)(opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue)
      //      << (CHAR)opt->value_quotation_mark << L" ";
      //   return ostring.str();

      if (opt == ((::xml::disp_option *) 1))
      {

         opt = Sys(::get_thread_app()).xml().m_poptionDefault;

      }

      string str;

      str = prop.name();
      str += "=";
      str += opt->value_quotation_mark;
      string strValue;
      if (opt->reference_value && opt->m_pentities)
         strValue = opt->m_pentities->entity_to_ref(prop.get_string());
      else
         strValue = prop.get_string();

      strValue.replace("\\", "\\\\"); // should be first
      strValue.replace("\n", "\\n");
      strValue.replace("\t", "\\t");
      strValue.replace("\r", "\\r");
      strValue.replace("'", "\\'");
      strValue.replace("\"", "\\\"");

      str += strValue;
      str += opt->value_quotation_mark;
      str += " ";

      return str;

   }


} // namespace xml



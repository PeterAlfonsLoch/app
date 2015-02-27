#include "framework.h"

namespace calculator
{

   element::element()
   {
      m_pparent   = NULL;
      m_pelement1 = NULL;
      m_pelement2 = NULL;
      m_pelement3 = NULL;
   }

   element::~element()
   {
   }


    double pi();

   value element::get_value()
   {
      if(m_ptoken->value == token::identifier)
      {
         value val;
         if(m_ptoken->m_str.CompareNoCase("pi") == 0)
         {
            val.m_dR = pi();
         }
         else
         {
            throw "unknown identifier";
         }
         return val;
      }
      else if(m_ptoken->value == token::number)
      {
         value val;
         val.m_dR = atof(m_ptoken->m_str);
         return val;
      }
      else if(m_ptoken->value == token::imaginary)
      {
         value val;
         val.m_dI = atof(m_ptoken->m_str);
         return val;
      }
      else if(m_ptoken->value == token::addition)
      {
         if(m_pelement2 == NULL)
            return m_pelement1->get_value();
         else
            return m_pelement1->get_value() + m_pelement2->get_value();
      }
      else if(m_ptoken->value == token::subtraction)
      {
         if(m_pelement2 == NULL)
            return value() - m_pelement1->get_value();
         else
            return m_pelement1->get_value() - m_pelement2->get_value();
      }
      else if(m_ptoken->value == token::multiplication)
      {
         return m_pelement1->get_value() * m_pelement2->get_value();
      }
      else if(m_ptoken->value == token::division)
      {
         return m_pelement1->get_value() / m_pelement2->get_value();
      }
      else if(m_ptoken->value == token::function)
      {
         if(m_ptoken->m_str == "sqr")
         {
            return m_pelement1->get_value() * m_pelement1->get_value();
         }
         else if(m_ptoken->m_str == "sqrt")
         {
            return sqrt(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "exp")
         {
            return exp(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "ln")
         {
            return log(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "log")
         {
            value val;
            val.m_dR = 10.0;
            return log(m_pelement1->get_value()) / log(val);
         }
         else if(m_ptoken->m_str == "pow")
         {
            return pow(m_pelement1->get_value(), m_pelement2->get_value());
         }
         else if(m_ptoken->m_str == "atan")
         {
            return atan(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "asin")
         {
            return asin(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "acos")
         {
            return acos(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "tan")
         {
            return tan(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "sin")
         {
            return sin(m_pelement1->get_value());
         }
         else if(m_ptoken->m_str == "cos")
         {
            return cos(m_pelement1->get_value());
         }
         else
         {
            throw "unknown function";
         }
      }
      return value();
   }

   string element::get_expression()
   {
      if(m_ptoken->value == token::number || m_ptoken->value == token::identifier)
      {
         return m_ptoken->m_str;
      }
      else if(m_ptoken->value == token::imaginary)
      {
         return "i" + m_ptoken->m_str;
      }
      else if(m_ptoken->value == token::addition)
      {
         if(m_pelement2 == NULL)
            return "(" + m_pelement1->get_expression() + ")";
         else
            return "(" + m_pelement1->get_expression() + " + " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->value == token::subtraction)
      {
         if(m_pelement2 == NULL)
            return "( - " + m_pelement1->get_expression() + ")";
         else
            return "(" + m_pelement1->get_expression() + " - " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->value == token::multiplication)
      {
         return "(" + m_pelement1->get_expression() + " * " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->value == token::division)
      {
         return "(" + m_pelement1->get_expression() + " / " + m_pelement2->get_expression() + ")";
      }
      else if(m_ptoken->value == token::function)
      {
         if(m_ptoken->m_str == "sqr")
         {
            return "sqr(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "sqrt")
         {
            return "sqrt(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "exp")
         {
            return "exp(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "ln")
         {
            return "ln(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "log")
         {
            return "log(" + m_pelement1->get_expression() + ")";
         }
         else if(m_ptoken->m_str == "pow")
         {
            return "pow(" + m_pelement1->get_expression() + ", "
                + m_pelement2->get_expression() + ")";
         }
         else
         {
            throw "unknown function";
         }
      }
      return "not supported operation";
   }



} // namespace calculator

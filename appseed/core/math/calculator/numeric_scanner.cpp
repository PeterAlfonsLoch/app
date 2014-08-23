/* (C) Copyright 2008 Nick Mudge <mudgen@gmail.com>
 * This code can be freely copied and modified.
 */
#include  "framework.h"

/* conversas dos Js Jefferson Dalavechia e Joice sobre calculadora cient凬ica, financeira e com pilha
mais tico de calculadora no command */

/* o LeoFischer falouu sobre participar do cl・(modinha de jogos de conquista de terra na internet) -
para mim sugest縊 na minha linguagem - para "criar um cl・? */

namespace calculator
{

   token::token()
   {
      value = token::none;
   }

   token::~token()
   {
   }


   scanner::scanner(sp(::aura::application) papp) :
      element(papp)
   {
      m_ptoken    = NULL;
      input       = NULL;
   }

   scanner::~scanner()
   {
   }


   void scanner::initialize(const char * psz)
   {
      input          = psz;
      next_input     = input;
   }


   void scanner::peek()
   {
      const char *beginning;
      if(input != next_input && next_input != NULL)
         return;
      beginning = input;
      m_ptoken = look_ahead();
      next_input = input;
      input = beginning;
   }

   void scanner::next()
   {
      input = next_input;
   }

   token * scanner::look_ahead()
   {
      token * token;
      token = new class token;
      if(token == NULL)
         throw memory_exception(get_app());
      while(::str::ch::is_space_char(input))
         input = ::str::utf8_inc(input);
      if(*input == '\0')
      {
         token->value = token::end;
         return token;
      }
      const char * nextinput = ::str::utf8_inc(input);

      if((*input == 'j' || *input == 'i') &&
         ::str::ch::is_digit(nextinput))
      {
         token->value = token::imaginary;
         char * endptr;
         strtod(nextinput, &endptr);
         token->m_str = string(nextinput, endptr - nextinput);
         input = endptr;
         return token;
      }
      else if(::str::ch::is_digit(input))
      {
         token->value = token::number;
         char * endptr;
         strtod(input, &endptr);
         token->m_str = string(input, endptr - input);
         if((*endptr == 'i' || *endptr == 'j')
            && !(isdigit_dup(*(endptr + 1)) || isalpha_dup(*(endptr + 1))))
         {
            token->value = token::imaginary;
            endptr++;
         }
         input = endptr;
         return token;
      }
      else if(*input == '+')
      {
         token->value = token::addition;
         input++;
         return token;
      }
      else if(*input == '-')
      {
         token->value = token::subtraction;
         input++;
         return token;
      }
      else if(*input == '*')
      {
         token->value = token::multiplication;
         input++;
         return token;
      }
      else if(*input == '/')
      {
         token->value = token::division;
         input++;
         return token;
      }
      else if(*input == '(')
      {
         token->value = token::open_paren;
         input++;
         return token;
      }
      else if(*input == ',')
      {
         token->value = token::virgula;
         input++;
         return token;
      }
      else if(*input == ')')
      {
         token->value = token::close_paren;
         input++;
         return token;
      }
      else
      {
         token->m_str = ::str::consume_nc_name(input);
         while(::str::ch::is_space_char(input))
            input = ::str::utf8_inc(input);
         if(*input == '(')
         {
            token->value = token::function;
         }
         else
         {
            token->value = token::identifier;
         }
         return token;
      }
   }


} // namespace calculator

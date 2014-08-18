/** \file parse.cpp - parse a string
 **
 **   Written: 1999-Feb-10 grymse@alhem.net
 **/

/*
Copyright (C) 1999-2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about 
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "framework.h"


namespace str {


/* implementation of class parse */

   parse::parse()
   :pa_the_str("")
   ,pa_splits("")
   ,pa_ord("")
   ,pa_the_ptr(0)
   ,pa_breakchar(0)
   ,pa_enable(0)
   ,pa_disable(0)
   ,pa_nospace(0)
   ,pa_quote(false)
   {
   }

   parse::parse(const string &s)
   :pa_the_str(s)
   ,pa_splits("")
   ,pa_ord("")
   ,pa_the_ptr(0)
   ,pa_breakchar(0)
   ,pa_enable(0)
   ,pa_disable(0)
   ,pa_nospace(0)
   ,pa_quote(false)
   {
   }

   parse::parse(const string &s,const string &sp)
   :pa_the_str(s)
   ,pa_splits(sp)
   ,pa_ord("")
   ,pa_the_ptr(0)
   ,pa_breakchar(0)
   ,pa_enable(0)
   ,pa_disable(0)
   ,pa_nospace(0)
   ,pa_quote(false)
   {
   }

   parse::parse(const string &s,const string &sp,int16_t nospace)
   :pa_the_str(s)
   ,pa_splits(sp)
   ,pa_ord("")
   ,pa_the_ptr(0)
   ,pa_breakchar(0)
   ,pa_enable(0)
   ,pa_disable(0)
   ,pa_nospace(1)
   ,pa_quote(false)
   {
      UNREFERENCED_PARAMETER(nospace);
   }


   parse::~parse()
   {
   }

   #define C ((pa_the_ptr<pa_the_str.get_length()) ? ((const char *) pa_the_str)[pa_the_ptr] : 0)

   int16_t parse::issplit(const char ca)
   {
      for (int32_t i = 0; i < pa_splits.get_length(); i++)
         if (pa_splits[i] == ca)
            return 1;
      return 0;
   }

   void parse::getsplitword()
   {
      index x;
      int32_t disabled = 0;
      int32_t quote = 0;
      int32_t rem = 0;

      if (C == '=')
      {
         x = pa_the_ptr++;
         if (x == pa_the_ptr && C == '=')
            pa_the_ptr++;
      }
      else if (pa_nospace)
      {
         while (C && issplit(C))
            pa_the_ptr++;
         x = pa_the_ptr;
         while (C && !issplit(C) && C != '=' && (C != pa_breakchar || !pa_breakchar || disabled))
         {
            if (pa_breakchar && C == pa_disable)
               disabled = 1;
            if (pa_breakchar && C == pa_enable)
               disabled = 0;
            if (pa_quote && C == '"')
               quote = 1;
            pa_the_ptr++;
            while (quote && C && C != '"')
            {
               pa_the_ptr++;
            }
            if (pa_quote && C == '"')
            {
               pa_the_ptr++;
            }
            quote = 0;
         }
         if (x == pa_the_ptr && C == '=')
            pa_the_ptr++;
      }
      else
      {
         if (C == pa_breakchar && pa_breakchar)
         {
            x = pa_the_ptr++;
            rem = 1;
         }
         else
         {
            while (C && (C == ' ' || C == 9 || C == 13 || C == 10 || issplit(C)))
               pa_the_ptr++;
            x = pa_the_ptr;
            while (C && C != ' ' && C != 9 && C != 13 && C != 10 && !issplit(C) && C != '=' &&
               (C != pa_breakchar || !pa_breakchar || disabled))
            {
               if (pa_breakchar && C == pa_disable)
                  disabled = 1;
               if (pa_breakchar && C == pa_enable)
                  disabled = 0;
               if (pa_quote && C == '"')
               {
                  quote = 1;
                  pa_the_ptr++;
                  while (quote && C && C != '"')
                  {
                     pa_the_ptr++;
                  }
                  if (pa_quote && C == '"')
                  {
                     pa_the_ptr++;
                  }
               }
               else
                  pa_the_ptr++;
               quote = 0;
            }
            if (C != '=')
            {
               pa_the_ptr++;
               rem = 1;
            }
         }
         if (x == pa_the_ptr && ((C == pa_breakchar && pa_breakchar) || C == '='))
            pa_the_ptr++;
      }

      pa_ord = (x < pa_the_str.get_length()) ? pa_the_str.Mid(x, pa_the_ptr - x - rem) : "";

   }

   void parse::getsplit()
   {
      index x;

      if (C == '=')
      {
         x = pa_the_ptr++;
      } else
      {
         while (C && (issplit(C)))
            pa_the_ptr++;
         x = pa_the_ptr;
         while (C && !issplit(C) && C != '=')
            pa_the_ptr++;
      }
      if (x == pa_the_ptr && C == '=')
         pa_the_ptr++;
      pa_ord = (x < pa_the_str.get_length()) ? pa_the_str.Mid(x,pa_the_ptr - x) : "";
   }

   string parse::getword()
   {
      index x;
      int32_t disabled = 0;
      int32_t quote = 0;
      int32_t rem = 0;

      if (pa_nospace)
      {
         while (C && issplit(C))
            pa_the_ptr++;
         x = pa_the_ptr;
         while (C && !issplit(C) && (C != pa_breakchar || !pa_breakchar || disabled))
         {
            if (pa_breakchar && C == pa_disable)
               disabled = 1;
            if (pa_breakchar && C == pa_enable)
               disabled = 0;
            if (pa_quote && C == '"')
               quote = 1;
            pa_the_ptr++;
            while (quote && C && C != '"')
            {
               pa_the_ptr++;
            }
            if (pa_quote && C == '"')
            {
               pa_the_ptr++;
            }
            quote = 0;
         }
      } else
      {
         if (C == pa_breakchar && pa_breakchar)
         {
            x = pa_the_ptr++;
            rem = 1;
         } else
         {
            while (C && (C == ' ' || C == 9 || C == 13 || C == 10 || issplit(C)))
               pa_the_ptr++;
            x = pa_the_ptr;
            while (C && C != ' ' && C != 9 && C != 13 && C != 10 && !issplit(C) &&
             (C != pa_breakchar || !pa_breakchar || disabled))
            {
               if (pa_breakchar && C == pa_disable)
                  disabled = 1;
               if (pa_breakchar && C == pa_enable)
                  disabled = 0;
               if (pa_quote && C == '"')
               {
                  quote = 1;
               pa_the_ptr++;
               while (quote && C && C != '"')
               {
                  pa_the_ptr++;
               }
               if (pa_quote && C == '"')
               {
                  pa_the_ptr++;
               }
               }
               else
                  pa_the_ptr++;
               quote = 0;
            }
            pa_the_ptr++;
            rem = 1;
         }
         if (x == pa_the_ptr && C == pa_breakchar && pa_breakchar)
            pa_the_ptr++;
      }
      if (x < pa_the_str.get_length())
      {
         pa_ord = pa_the_str.Mid(x,pa_the_ptr - x - rem);
      }
      else
      {
         pa_ord = "";
      }
      return pa_ord;
   }

   void parse::getword(string &s)
   {
      s = parse::getword();
   }

   void parse::getsplit(string &s)
   {
      parse::getsplit();
      s = pa_ord;
   }


   void parse::getsplitword(string & s)
   {
      
      parse::getsplitword();
      
      s = pa_ord;

   }


   void parse::getword(string &s,string &fill,int32_t l)
   {
      parse::getword();
      s = "";
      while (s.get_length() + pa_ord.get_length() < (index)l)
         s += fill;
      s += pa_ord;
   }

   string parse::getrest()
   {
      string s;
      while (C && (C == ' ' || C == 9 || issplit(C)))
         pa_the_ptr++;
      s = (pa_the_ptr < pa_the_str.get_length()) ? pa_the_str.Mid(pa_the_ptr) : "";
      return s;
   }

   void parse::getrest(string &s)
   {
      while (C && (C == ' ' || C == 9 || issplit(C)))
         pa_the_ptr++;
      s = (pa_the_ptr < pa_the_str.get_length()) ? pa_the_str.Mid(pa_the_ptr) : "";
   }

   long parse::getvalue()
   {
      parse::getword();
      return atol(pa_ord);
   }

   void parse::setbreak(const char ca)
   {
      pa_breakchar = ca;
   }

   int32_t parse::getwordlen()
   {
      index x,y = pa_the_ptr,len;

      if (C == pa_breakchar && pa_breakchar)
      {
         x = pa_the_ptr++;
      } else
      {
         while (C && (C == ' ' || C == 9 || C == 13 || C == 10 || issplit(C)))
            pa_the_ptr++;
         x = pa_the_ptr;
         while (C && C != ' ' && C != 9 && C != 13 && C != 10 && !issplit(C) && (C != pa_breakchar || !pa_breakchar))
            pa_the_ptr++;
      }
      if (x == pa_the_ptr && C == pa_breakchar && pa_breakchar)
         pa_the_ptr++;
      len = pa_the_ptr - x;
      pa_the_ptr = y;
      return (int32_t)len;
   }

   int32_t parse::getrestlen()
   {
      index y = pa_the_ptr;
      index len;

      while (C && (C == ' ' || C == 9 || issplit(C)))
         pa_the_ptr++;
      len = strlen(pa_the_str.Mid(pa_the_ptr));
      pa_the_ptr = y;
      return (int32_t)len;
   }

   void parse::getline()
   {
      index x;

      x = pa_the_ptr;
      while (C && C != 13 && C != 10)
         pa_the_ptr++;
      pa_ord = (x < pa_the_str.get_length()) ? pa_the_str.Mid(x,pa_the_ptr - x) : "";
      if (C == 13)
         pa_the_ptr++;
      if (C == 10)
         pa_the_ptr++;
   }

   void parse::getline(string &s)
   {
      getline();
      s = pa_ord;
   }

} // namespace str



/** \file parse.h - parse a string
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

#pragma once

namespace str
{

   // Splits a string whatever way you want.

   class CLASS_DECL_AURA parse
   {
   public:
      parse();
      parse(const string &);
      parse(const string &, const string &);
      parse(const string &, const string &, int16_t);
      ~parse();
      int16_t issplit(const char);
      void getsplit();
      void getsplit(string &);
      string getword();
      void getword(string &);
      void getword(string &, string &, int32_t);
      void getsplitword();
      void getsplitword(string &);
      string getrest();
      void getrest(string &);
      long getvalue();
      void setbreak(const char);
      int32_t getwordlen();
      int32_t getrestlen();

      void enablebreak(const char ca)
      {
         pa_enable = ca;
      }

      void disablebreak(const char ca)
      {
         pa_disable = ca;
      }
      void getline();
      void getline(string &);
      index getptr() { return pa_the_ptr; }
      void EnableQuote(bool b) { pa_quote = b; }

   private:
      string   pa_the_str;
      string   pa_splits;
      string   pa_ord;
      strsize  pa_the_ptr;
      char     pa_breakchar;
      char     pa_enable;
      char     pa_disable;
      int16_t    pa_nospace;
      bool     pa_quote;
   };


} // namespace str



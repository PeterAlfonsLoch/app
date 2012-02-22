/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
 *
 * Authored By Gordon Williams <gw@pur3.co.uk>
 *
 * Copyright (C) 2009 Pur3 Ltd
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "StdAfx.h"

#ifdef _DEBUG
#	ifdef _MSC_VER
#		define new DEBUG_NEW
#	endif
#endif

#ifdef __GNUC__
#	define UNUSED(x) __attribute__((__unused__))
#elif defined(_MSC_VER)
#	ifndef UNUSED
#		define UNUSED(x) x
#		pragma warning( disable : 4100 ) /* unreferenced formal parameter */
#	endif
#else
#	define UNUSED(x) x
#endif


//using namespace std;
// ----------------------------------------------- Actual Functions

void scTrace(CScriptVar *c, void * userdata) {
	tinyjs *js = (tinyjs*)userdata;
	if(c->getParameterLength())
		c->getParameter(0)->trace();
	else
		js->root->trace("root");
}

void scObjectDump(CScriptVar *c, void *) {
	c->getParameter("this")->trace("> ");
}

void scObjectClone(CScriptVar *c, void *) {
	CScriptVar *obj = c->getParameter("this");
	c->getReturnVar()->copyValue(obj);
}

void scMathRand(CScriptVar *c, void *) {
	c->getReturnVar()->setDouble((double)rand()/RAND_MAX);
}

void scMathRandInt(CScriptVar *c, void *)
{
	int64_t min = c->getParameter("min")->getInt();
	int64_t max = c->getParameter("max")->getInt();
	int64_t val = min + (int)((long)rand()*(1+max-min)/RAND_MAX);
	if(val>max)
      val=max;
	c->getReturnVar()->setInt(val);
}

void scCharToInt(CScriptVar *c, void *)
{
	string str = c->getParameter("ch")->getString();;
	int64_t val = 0;
	if (str.length()>0)
		val = (int)str.c_str()[0];
	c->getReturnVar()->setInt(val);
}

void scStringIndexOf(CScriptVar *c, void *) {
	string str = c->getParameter("this")->getString();
	string search = c->getParameter("search")->getString();
	strsize p = str.find(search);
	strsize val = (p< 0) ? -1 : p;
	c->getReturnVar()->setInt(val);
}

void scStringSubstring(CScriptVar *c, void *) {
	string str = c->getParameter("this")->getString();
	int64_t lo = c->getParameter("lo")->getInt();
	int64_t hi = c->getParameter("hi")->getInt();

	int64_t l = hi-lo;
	if (l>0 && lo>=0 && lo+l<=(int)str.length())
		c->getReturnVar()->setString(str.substr((strsize) lo, (strsize) l));
	else
		c->getReturnVar()->setString("");
}

void scStringCharAt(CScriptVar *c, void *) {
	string str = c->getParameter("this")->getString();
	int64_t p = c->getParameter("pos")->getInt();
	if (p>=0 && p<(int)str.length())
		c->getReturnVar()->setString(str.substr((strsize) p, 1));
	else
		c->getReturnVar()->setString("");
}

void scIntegerParseInt(CScriptVar *c, void *) {
	string str = c->getParameter("str")->getString();
	int val = strtol(str.c_str(),0,0);
	c->getReturnVar()->setInt(val);
}

void scIntegerValueOf(CScriptVar *c, void *) {
	string str = c->getParameter("str")->getString();

	int val = 0;
	if (str.length()==1)
		val = str[0];
	c->getReturnVar()->setInt(val);
}

void scJSONStringify(CScriptVar *c, void *) {
	_template_std_ostringstream result;
	c->getParameter("obj")->getJSON(result);
	c->getReturnVar()->setString(result.str());
}

void scEval(CScriptVar *c, void *data) {
	tinyjs *tinyJS = (tinyjs *)data;
	string str = c->getParameter("jsCode")->getString();
	c->setReturnVar(tinyJS->evaluateComplex(str).var);
}

void scIsInNet(CScriptVar *c, void *data)
{
	tinyjs *tinyJS = (tinyjs *)data;
	string host = c->getParameter("host")->getString();
   string addr = c->getParameter("addr")->getString();
   string mask = c->getParameter("mask")->getString();

   strsize iFind = host.reverse_find(':');
   if(iFind >= 0)
      host = host.Left(iFind);


   ipaddr_t l_host;
   if (!Sys(tinyJS->m_psystem).net().u2ip(host, l_host))
   {
   	c->getReturnVar()->setBool(false);
      return;
   }
   ipaddr_t l_addr;
   if (!Sys(tinyJS->m_psystem).net().u2ip(addr, l_addr))
   {
   	c->getReturnVar()->setBool(false);
      return;
   }
   ipaddr_t l_mask;
   if (!Sys(tinyJS->m_psystem).net().u2ip(mask, l_mask))
   {
   	c->getReturnVar()->setBool(false);
      return;
   }

   sockets::ipv4_address ad_host(tinyJS->get_app(), l_host, 0);
   sockets::ipv4_address ad_addr(tinyJS->get_app(), l_addr, 0);
   sockets::ipv4_address ad_mask(tinyJS->get_app(), l_mask, 0);


	c->getReturnVar()->setBool(ad_host.is_in_net(ad_addr, ad_mask));

}


// ----------------------------------------------- Register Functions
void registerFunctions(tinyjs *tinyJS) {
//    tinyJS->addNative("function eval(jsCode)", scEval, tinyJS); // execute the given string and return the result
	tinyJS->addNative("function trace()", scTrace, tinyJS);
	tinyJS->addNative("function Object.dump()", scObjectDump, 0);
	tinyJS->addNative("function Object.clone()", scObjectClone, 0);
	tinyJS->addNative("function Math.rand()", scMathRand, 0);
	tinyJS->addNative("function Math.randInt(min, max)", scMathRandInt, 0);
	tinyJS->addNative("function charToInt(ch)", scCharToInt, 0); //  convert a character to an int - get its value
	tinyJS->addNative("function String.indexOf(search)", scStringIndexOf, 0); // find the position of a string in a string, -1 if not
	tinyJS->addNative("function String.substring(lo,hi)", scStringSubstring, 0);
	tinyJS->addNative("function String.charAt(pos)", scStringCharAt, 0);
	tinyJS->addNative("function Integer.parseInt(str)", scIntegerParseInt, 0); // string to int
	tinyJS->addNative("function Integer.valueOf(str)", scIntegerValueOf, 0); // value of a single character
	tinyJS->addNative("function JSON.stringify(obj, replacer)", scJSONStringify, 0); // convert to JSON. replacer is ignored at the moment
   tinyJS->addNative("function isInNet(host, addr, mask)", scIsInNet, tinyJS); // convert to JSON. replacer is ignored at the moment
	// JSON.parse is left out as you can (unsafely!) use eval instead
}


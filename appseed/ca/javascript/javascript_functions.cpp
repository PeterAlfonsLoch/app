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

#include "framework.h"

#ifdef DEBUG
#	ifdef _MSC_VER
#		define new DEBUG_NEW
#	endif
#endif

/*#ifdef __GNUC__
#ifndef UNUSED
#	define UNUSED(x) __attribute__((__unused__))
#endif
#elif defined(_MSC_VER)
#	ifndef UNUSED
#		define UNUSED(x) x
#		pragma warning( disable : 4100 ) /* unreferenced formal parameter */
/*#	endif
#else
#	define UNUSED(x) x
#endif*/

void scIsInNet(CScriptVar *c, void *data);
bool is_only_digits(const char * psz);
void scIsPlainHostName(CScriptVar *c, void *data);
void scMyIpAddress(CScriptVar *c, void *data);



void scIsInNet(CScriptVar *c, void *data)
{
	tinyjs *tinyJS = (tinyjs *)data;
	string host = c->getParameter("host")->getString();
   string addr = c->getParameter("addr")->getString();
   string mask = c->getParameter("mask")->getString();

   strsize iFind = host.reverse_find(':');
   if(iFind >= 0)
      host = host.Left(iFind);


/*   ipaddr_t l_host;
   if (!Sys(tinyJS->m_psystem).net().u2ip(host, l_host))
   {
   	c->getReturnVar()->setInt(FALSE);
      return;
   }
   ipaddr_t l_addr;
   if (!Sys(tinyJS->m_psystem).net().u2ip(addr, l_addr))
   {
   	c->getReturnVar()->setInt(FALSE);
      return;
   }
   ipaddr_t l_mask;
   if (!Sys(tinyJS->m_psystem).net().u2ip(mask, l_mask))
   {
   	c->getReturnVar()->setInt(FALSE);
      return;
   }*/

   ::sockets::address ad_host(tinyJS->get_app(), host, 0);
   ::sockets::address ad_addr(tinyJS->get_app(), addr, 0);
   ::sockets::address ad_mask(tinyJS->get_app(), mask, 0);


	c->getReturnVar()->setInt(ad_host.is_in_net(ad_addr, ad_mask));

}


bool is_only_digits(const char * psz)
{
   if(psz == NULL || *psz == '\0')
      return false;
   while(true)
   {
      if(!isdigit_dup(*psz))
         return false;
      psz++;
      if(*psz == '\0')
         return true;
   }
         
}

void scIsPlainHostName(CScriptVar *c, void *data)
{
//	tinyjs *tinyJS = (tinyjs *)data;

//   App(tinyJS->m_papp);

   string str = c->getParameter("host")->getString();

   stringa stra;

   stra.explode(".", str);

   bool bIpv4 = true;

   if(stra.get_count() == 4)
   {
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         if(!is_only_digits(stra[i]) || atoi_dup(stra[i]) > 255)
         {
            bIpv4 = true;
         }
      }
   }

   if(bIpv4)
   {
      c->getReturnVar()->setInt(0);
      return;
   }

   
   c->getReturnVar()->setInt(str.find(".") > 0);

}


void scMyIpAddress(CScriptVar *c, void *data)
{
//	tinyjs *tinyJS = (tinyjs *)data;

//   App(tinyJS->m_papp);


   c->getReturnVar()->setString("127.0.0.1");

}

// ----------------------------------------------- Register Functions
void registerJavascriptFunctions(tinyjs *tinyJS) {
//    tinyJS->addNative("function eval(jsCode)", scEval, tinyJS); // execute the given string and return the result
   tinyJS->addNative("function isInNet(host, addr, mask)", scIsInNet, tinyJS); // convert to JSON. replacer is ignored at the moment
   tinyJS->addNative("function isPlainHostName(host)", scIsPlainHostName, tinyJS); // convert to JSON. replacer is ignored at the moment
   tinyJS->addNative("function myIpAddress()", scMyIpAddress, tinyJS); // convert to JSON. replacer is ignored at the moment
	// JSON.parse is left out as you can (unsafely!) use eval instead
}


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
#		define new BASE_NEW
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

void scIsInNet(CScriptVar *ca, void *data);
bool is_only_digits(const char * psz);
void scIsPlainHostName(CScriptVar *ca, void *data);
void scMyIpAddress(CScriptVar *ca, void *data);



void scIsInNet(CScriptVar *ca, void *data)
{
//	tinyjs *tinyJS = (tinyjs *)data;
	string host = ca->getParameter("host")->getString();
   string addr = ca->getParameter("addr")->getString();
   string mask = ca->getParameter("mask")->getString();

   strsize iFind = host.reverse_find(':');
   if(iFind >= 0)
      host = host.Left(iFind);


/*   ipaddr_t l_host;
   if (!Sys(tinyJS->m_psystem).net().u2ip(host, l_host))
   {
   	ca->getReturnVar()->setInt(FALSE);
      return;
   }
   ipaddr_t l_addr;
   if (!Sys(tinyJS->m_psystem).net().u2ip(addr, l_addr))
   {
   	ca->getReturnVar()->setInt(FALSE);
      return;
   }
   ipaddr_t l_mask;
   if (!Sys(tinyJS->m_psystem).net().u2ip(mask, l_mask))
   {
   	ca->getReturnVar()->setInt(FALSE);
      return;
   }*/

   ::net::address ad_host(host, 0);
   ::net::address ad_addr(addr, 0);
   ::net::address ad_mask(mask, 0);


	ca->getReturnVar()->setInt(ad_host.is_in_same_net(ad_addr, ad_mask));

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

void scIsPlainHostName(CScriptVar *ca, void *data)
{
//	tinyjs *tinyJS = (tinyjs *)data;

//   App(tinyJS->m_paxisapp);

   string str = ca->getParameter("host")->getString();

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
      ca->getReturnVar()->setInt(0);
      return;
   }

   
   ca->getReturnVar()->setInt(str.find(".") > 0);

}


void scMyIpAddress(CScriptVar *ca, void *data)
{
//	tinyjs *tinyJS = (tinyjs *)data;

//   App(tinyJS->m_paxisapp);


   ca->getReturnVar()->setString("127.0.0.1");

}

// ----------------------------------------------- Register Functions
void registerJavascriptFunctions(tinyjs *tinyJS) {
//    tinyJS->addNative("function eval(jsCode)", scEval, tinyJS); // execute the given string and return the result
   tinyJS->addNative("function isInNet(host, addr, mask)", scIsInNet, tinyJS); // convert to JSON. replacer is ignored at the moment
   tinyJS->addNative("function isPlainHostName(host)", scIsPlainHostName, tinyJS); // convert to JSON. replacer is ignored at the moment
   tinyJS->addNative("function myIpAddress()", scMyIpAddress, tinyJS); // convert to JSON. replacer is ignored at the moment
	// JSON.parse is left out as you can (unsafely!) use eval instead
}


/* 
 * libepp-nicbr 1.10 on 2010-14-10 2009 Registro.br
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistribution of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY REGISTRO.BR ``AS IS AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIE OF FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL REGISTRO.BR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
/* $Id: Greeting.cpp 1040 2009-10-01 17:49:12Z fneves $ */

#include "StdAfx.h"

#include "Greeting.H"

namespace libepp {

void Greeting::set_svID(const char *svID) 
{ 
  _svID = svID; 
}

void Greeting::set_svDate(const char *svDate) 
{ 
  _svDate = svDate; 
}

void Greeting::set_version(const char *version) 
{ 
  _version.add(version); 
}

void Greeting::set_lang(const char *lang) 
{ 
  _lang.add(lang);
}

void Greeting::set_objURI(const char *objURI) 
{ 
  _objURI.add(objURI);
}

void Greeting::set_extURI(const char *extURI)  
{ 
  _extURI.add(extURI);
}

void Greeting::set_access(const Greeting::Access &access) 
{ 
  _access = access; 
}

void Greeting::set_purpose(const Greeting::Purpose &purpose) 
{ 
    _purpose.add(purpose); 
}

void Greeting::set_recipient(const Greeting::Recipient &recipient) 
{ 
  _recipient.add(recipient);
}

void Greeting::set_recDesc(const char *recDesc) 
{
  _recDesc = recDesc;
}

void Greeting::set_retention(const Greeting::Retention &retention) 
{ 
  _retention = retention; 
}

void Greeting::set_expiry(const int &type, const char *expiry) 
{ 
  _type_expiry = type;
  _expiry = expiry; 
}

string Greeting::get_svID() const
{ 
  return _svID; 
}

string Greeting::get_svDate() const
{ 
  return _svDate; 
}

stringa Greeting::get_version() const 
{ 
  return _version;
}

stringa Greeting::get_lang() const
{ 
  return _lang;
}

stringa Greeting::get_objURI() const
{ 
  return _objURI;
}

stringa Greeting::get_extURI() const
{ 
  return _extURI;
}

Greeting::Access Greeting::get_access() const
{ 
  return _access; 
}
  
comparable_array<Greeting::Purpose> Greeting::get_purpose() const 
{ 
  return _purpose;
}

comparable_array<Greeting::Recipient> Greeting::get_recipient() const
{ 
  return _recipient;
}

string Greeting::get_recDesc() const
{ 
  return _recDesc; 
}

Greeting::Retention Greeting::get_retention() const
{ 
  return _retention; 
}

int Greeting::get_type_expiry() const
{ 
  return _type_expiry; 
}

string Greeting::get_expiry() const
{ 
  return _expiry; 
}

}

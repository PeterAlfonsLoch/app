/*
 * Copyright (C) 2006 Registro.br. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are 
 * met: 
 * 1. Redistribution of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and\/or other materials provided with the distribution. 
 *  
 * THIS SOFTWARE IS PROVIDED BY REGISTRO.BR AS IS'' AND ANY EXPRESS OR 
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
/** @file libepp_nicbr.H
 *  @brief Project defines
 */

#pragma once

#include "ca2.h"

#define SCHEMASDIR "/usr/local/share/libepp_nicbr/schemas"
#define TEMPLATESDIR "/usr/local/share/libepp_nicbr/templates"
#define SSLCERTDIR "/usr/local/share/libepp_nicbr/ssl"

#include "StrUtil.H"
#include "NameServer.h"
#include "CommonData.H"
#include "RegistrationPeriod.H"
#include "KeyData.H"
#include "DSInfo.H"
#include "CommonData.H"
#include "DSInfo.H"

#include "GeneralException.H"
#include "EppException.H"
#include "IoException.H"
#include "StringEncodingException.H"
#include "XmlException.H"


//#include "BeautifierHandlers_need_to_adapt.H"
#include "GeneralException.H"
#include "XmlException.H"

#include "Response.H"
#include "Command.H"
#include "CommonData.H"
#include "PanDataResponse.H"


#include "PollCommand.H"
#include "PollResponse.H"
#include "LoginCommand.H"


#include "AsnCheckCommand.H"
#include "AsnCheckResponse.H"
#include "AsnCreateCommand.H"
#include "AsnCreateResponse.H"
#include "AsnDeleteCommand.H"
#include "AsnInfoCommand.H"
#include "AsnInfoResponse.H"
#include "AsnRenewCommand.H"
#include "AsnRenewResponse.H"
#include "AsnTransferCommand.H"
#include "AsnTransferResponse.H"
#include "AsnUpdateCommand.H"




#include "DomainCheckCommand.H"
#include "DomainCheckResponse.H"
#include "DomainCreateCommand.H"
#include "DomainCreateResponse.H"
#include "DomainDeleteCommand.H"
#include "DomainInfoCommand.H"
#include "DomainInfoResponse.H"
#include "DomainRenewResponse.H"
#include "DomainTransferCommand.H"
#include "DomainTransferResponse.H"
#include "DomainUpdateCommand.H"
#include "DomainRenewCommand.H"
#include "DomainRenewResponse.H"



#include "BrDomainCommon.H"

#include "BrDomainCheckCommand.H"
#include "BrDomainCheckResponse.H"
#include "BrDomainCreateCommand.H"
#include "BrDomainCreateResponse.H"
#include "BrDomainInfoCommand.H"
#include "BrDomainInfoResponse.H"
#include "BrDomainPanDataResponse.h"
#include "BrDomainUpdateCommand.H"
#include "BrDomainUpdateResponse.H"
#include "BrDomainRenewResponse.H"



#include "ContactCheckCommand.H"
#include "ContactCheckResponse.H"
#include "ContactCreateCommand.H"
#include "ContactCreateResponse.H"
#include "ContactInfoCommand.H"
#include "ContactInfoResponse.H"
#include "ContactCheckResponse.H"
#include "ContactTransferCommand.H"
#include "ContactTransferResponse.H"
#include "ContactUpdateCommand.H"



#include "BrOrgCheckCommand.H"
#include "BrOrgCheckResponse.H"
#include "BrOrgCreateCommand.H"
#include "BrOrgCreateResponse.H"
#include "BrOrgInfoCommand.H"
#include "BrOrgInfoResponse.H"
#include "BrOrgPanDataResponse.H"
#include "BrOrgUpdateCommand.H"


#include "IpNetworkCheckCommand.H"
#include "IpNetworkCheckResponse.H"
#include "IpNetworkCreateCommand.H"
#include "IpNetworkCreateResponse.H"
#include "IpNetworkDeleteCommand.H"
#include "IpNetworkInfoCommand.H"
#include "IpNetworkInfoResponse.H"
#include "IpNetworkRenewCommand.H"
#include "IpNetworkRenewResponse.H"
#include "IpNetworkTransferCommand.H"
#include "IpNetworkTransferResponse.H"
#include "IpNetworkUpdateCommand.H"




#include "Response.H"
#include "Greeting.H"

#include "DomErrorHandler.H"
#include "DomParserCommon.H"
#include "DomParser.H"


#include "Action.H"


#include "AsnCheck.H"
#include "AsnCreate.H"
#include "AsnDelete.H"
#include "AsnInfo.H"
#include "AsnRenew.H"
#include "AsnTransfer.H"
#include "AsnUpdate.H"


#include "DomainCheck.H"
#include "DomainCreate.H"
#include "DomainDelete.H"
#include "DomainInfo.H"
#include "DomainRenew.H"
#include "DomainTransfer.H"
#include "DomainUpdate.H"



#include "BrDomainCheck.H"
#include "BrDomainCreate.H"
#include "BrDomainInfo.H"
#include "BrDomainRenew.H"
#include "BrDomainUpdate.H"



#include "ContactCheck.H"
#include "ContactCreate.H"
#include "ContactInfo.H"
#include "ContactTransfer.H"
#include "ContactUpdate.H"





#include "BrOrgCheck.H"
#include "BrOrgInfo.H"
#include "BrOrgCreate.H"
#include "BrOrgUpdate.H"



#include "IpNetworkCheck.H"
#include "IpNetworkCreate.H"
#include "IpNetworkDelete.H"
#include "IpNetworkInfo.H"
#include "IpNetworkRenew.H"
#include "IpNetworkTransfer.H"
#include "IpNetworkUpdate.H"



#include "Session.H"


//#include "shell_command.H"


//#include "shell_global.H"
//#include "shell_StrUtil.H"
//#include "shell_ObjectSet.H"
//#include "shell_Print.H"

#include "Hello.H"

#include "Login.H"
#include "Logout.H"

#include "Poll.H"


//#include "shell_CommandFunctions.H"

//#include "BrOrgFunctions.H"
//#include "ContactFunctions.H"
//#include "DomainFunctions.H"
//#include "IpNetworkFunctions.H"




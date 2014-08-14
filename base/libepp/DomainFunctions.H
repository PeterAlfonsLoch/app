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
/* $Id: DomainFunctions.H 1073 2010-07-22 16:48:52Z eduardo $ */
/** @file DomainFunctions.H
 *  @brief EPP Domain related functions
 */
#pragma once

#include "BrDomainCheck.H"
#include "BrDomainInfo.H"
#include "DomainTransfer.H"
#include "BrDomainCreate.H"
#include "BrDomainUpdate.H"
#include "BrDomainRenew.H"
#include "DomainCheck.H"
#include "DomainInfo.H"
#include "DomainTransfer.H"
#include "DomainCreate.H"
#include "DomainUpdate.H"
#include "DomainRenew.H"

#include "DomainDelete.H"
#include "RegistrationPeriod.H"

/// print domain command usage info
/**
   @param error_msg   error message to be printed
   @param specific    optional, choses specific sub-command
   @return 0 if ok, -1 otherwise
*/
int cmd_domain_help(string error_msg, string specific = "")
{
  if (error_msg != "") {
    printf("error: %s\n", error_msg);
  }

  printf("domain command syntax help:\n");
  printf("\n");

  if (specific == "" || specific == "check") {
    printf("  check <domain1> [domain2 ... domainN]"
	   " [-o organization]"
	   "\n");
   
    printf("\n");
  }
  if (specific == "" || specific == "info") {
    printf("  info <domain> [-auth authInfoPw[:authInfoRoid]]"
	   " [-t ticketNumber]"
	   "\n");
    printf("\n");
  }
  if (specific == "" || specific == "transfer") {
    printf("  transfer <domain> [-auth authInfoPw[:authInfoRoid]]\n");
    printf("\n");
  }
  if (specific == "" || specific == "create") {
    printf("  create <domain> [-period time:unit]\n"
	   "    [-ns nameserver[,ipversion:ipaddr][, ...] ...] "
	   "[-r registrant]"
	   "\n    [-contact type=value ...] [-auth authInfoPw]"
	   "\n    [-max-sig-life <maxSigLife>]"
	   "\n    [-dnskey <flags> <protocol> <alg> <pubKey>]"
	   "\n    [-ds <keyTag> <alg> <digestType> <digest> "
	   "[-maxlife <maxSigLife>]"
	   "\n         [-keyData <flags> <protocol> <alg> <pubKey>]] "
	   "\n    <-o organization> [-rpflags flag1:flag2:flag3]"
	   "\n    [-auto-renew <on|off>]"
           "\n");

    printf("\n");
  }
  if (specific == "" || specific == "delete") {
    printf("  delete <domain>\n");
    printf("\n");
  }
  if (specific == "" || specific == "renew") {
    printf("  renew <domain> <-expdate curExpDate> [-period time:unit]\n");
    printf("\n");
  }
  if (specific == "" || specific == "update") {
    printf("  update <domain>\n"
	   "    [-add-ns nameserver[,ipversion:ipaddr][, ...] ...]\n"
	   "    [-add-contact type=value ...]\n"
	   "    [-add-status status:lang:\"description\" ...]\n"
	   "    [-max-sig-life <maxSigLife>]\n"
	   "    [-add-dnskey <flags> <protocol> <alg> <pubKey>]\n"
	   "    [-add-ds <keyTag> <alg> <digestType> <digest> "
	   "[-maxlife <maxSigLife>]\n"
	   "        [-keyData <flags> <protocol> <alg> <pubKey>] ...]\n"
	   "    [-secDNS-urgent]\n"
	   "    [-rem-ns nameserver[,ipversion:ipaddr][, ...] ...]\n"
	   "    [-rem-contact type=value ...]\n"
	   "    [-rem-status status ...]\n"
	   "    [-rem-dnskey <flags> <protocol> <alg> <pubKey>]\n"
	   "    [-rem-ds <keyTag> <alg> <digestType> <digest> "
	   "[-maxlife <maxSigLife>]\n"
	   "        [-keyData <flags> <protocol> <alg> <pubKey>] ...] \n"
	   "    [-rem-ds-1.0 <keyTag>]\n"
	   "    [-remove-all-secdns]\n"
	   "    [-chg-ds <keyTag> <alg> <digestType> <digest> "
	   "[-maxlife <maxSigLife>]\n"
	   "        [-keyData <flags> <protocol> <alg> <pubKey>]]\n"

	   "    [-r registrant] [-auth authInfoPw]"
	   
 	   "\n    [-t ticketNumber] [-rpflags flag1:flag2:flag3]"
	   "\n    [-auto-renew <on|off>]"
	   "\n");
    printf("\n");
  }

  if (error_msg != "") {
    return -1;
  }

  return 0;
}

/// domain check command function
/**
   @param args   comparable_array with command-line arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_domain_check(stringa &args)
{
#if USE_BR_DOMAINS
  BrDomainCheck act;
  BrDomainCheckCommand *cmd = act.get_command();
#else
  DomainCheck act;
  DomainCheckCommand *cmd = act.get_command();
#endif //USE_BR_DOMAINS
  string cmd_name = "check";

  while (!args.is_empty()) {
#if USE_BR_DOMAINS
    if (args[0] == "-o") {
      // comparable_array organization
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("organization parameter missing", cmd_name);
      }
      cmd->set_organization(args[0]);
      args.remove_at(args.begin());
    } else {
#endif //USE_BR_DOMAINS
      // add domains
      cmd->insert_domain(args[0]);
      args.remove_at(args.begin());
#if USE_BR_DOMAINS
    }
#endif //USE_BR_DOMAINS
  }

  if (cmd->get_domains_list().is_empty()) {
    return cmd_domain_help("no domain names specified", cmd_name);
  }

  if (_debug) {
    stringa domains = cmd->get_domains_list();
    
    printf("names to be checked:\n");
    for (it = domains.begin(); it != domains.end(); it++) {
      printf("  [%s]\n", (*it));
    }
    
#if USE_BR_DOMAINS
    if (cmd->get_organization() != "") {
      printf("  organization: [%s]\n", cmd->get_organization());
    }
#endif //USE_BR_DOMAINS
  } // _debug

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// domain info command function
/**
   @param args   comparable_array with command-line arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_domain_info(stringa &args)
{
#if USE_BR_DOMAINS
  BrDomainInfo act;
  BrDomainInfoCommand *cmd = act.get_command();
#else
  DomainInfo act;
  DomainInfoCommand *cmd = act.get_command();
#endif //USE_BR_DOMAINS
  string cmd_name = "info";

  if (args.is_empty()) {
    return cmd_domain_help("no domain name specified", cmd_name);
  }
  
  // domain name MUST be the first attribute
  cmd->set_name(args[0]);
  args.remove_at(args.begin());

  while (!args.is_empty()) {
    if (args[0] == "-auth") {
      // comparable_array authInfo
      AuthInfo auth;
      if (ObjectSet::authInfo(auth, args) != 0) {
	return cmd_domain_help("invalid auth", cmd_name);
      }
      cmd->set_authInfo(auth);
#if USE_BR_DOMAINS
    } else if (args[0] == "-t") {
      // ticketNumber
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("ticket number parameter missing", cmd_name);
      }
      if (atoi(args[0]) <= 0) {
	return cmd_domain_help("ticket parameter must be a positive integer",
			       cmd_name);
      }
      cmd->set_ticketNumber(atoi(args[0]));
      args.remove_at(args.begin());
#endif //USE_BR_DOMAINS
    } else {
      return cmd_domain_help("invalid syntax near \"" + args[0] + "\"",
			     cmd_name);
    }
  }

  if (_debug) {
    printf("name to get info: [%s]\n", cmd->get_name());

#if USE_BR_DOMAINS
    if (cmd->get_ticketNumber() != 0) {
      printf("  ticketNumber: [%d]\n", cmd->get_ticketNumber());
    }
#endif //USE_BR_DOMAINS
    
    SheppPrint::authInfo(cmd->get_authInfo());
  } // _debug

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// domain transfer command function
/**
   @param args   comparable_array with command-line arguments
   @return 0
*/
int cmd_domain_transfer(stringa &args)
{
  DomainTransfer act;
  DomainTransferCommand *cmd = act.get_command();
  string cmd_name = "transfer";

  if (args.is_empty()) {
    return cmd_domain_help("no domain name specified", cmd_name);
  }
  
  // domain name MUST be the first attribute
  cmd->set_name(args[0]);
  args.remove_at(args.begin());

  while (!args.is_empty()) {
    if (args[0] == "-auth") {
      // comparable_array authInfo
      AuthInfo auth;
      if (ObjectSet::authInfo(auth, args) != 0) {
	return cmd_domain_help("invalid auth", cmd_name);
      }
      cmd->set_authInfo(auth);
    } else {
      return cmd_domain_help("invalid syntax near \"" + args[0] + "\"",
			     cmd_name);
    }
  }

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// domain create command function
/**
   @param args   comparable_array with command-line arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_domain_create(stringa &args)
{
#if USE_BR_DOMAINS
  BrDomainCreate act;
  BrDomainCreateCommand *cmd = act.get_command();
#else
  DomainCreate act;
  DomainCreateCommand *cmd = act.get_command();
#endif //USE_BR_DOMAINS
  string cmd_name = "create";

  cmd->set_secDnsVersion(_serverSecDnsVersion);

  if (args.is_empty()) {
    return cmd_domain_help("domain name missing", cmd_name);
  }
  // domain name MUST be the first attribute
  cmd->set_name(args[0]);
  args.remove_at(args.begin());

  while (!args.is_empty()) {
    if (args[0] == "-period") {
      //registration period
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("period parameter missing", cmd_name);
      }

      string time;
      string unit;
      if (SheppStrUtil::split(args[0], time, unit, ":", false) != 0) {
	return cmd_domain_help("invalid period", cmd_name);
      }

      cmd->set_period(atoi(time), unit);
      args.remove_at(args.begin());
    } else if (args[0] == "-ns") {
      //nameserver
      NameServer ns;
      if (ObjectSet::nameServer(ns, args) != 0) {
	return cmd_domain_help("invalid nameserver", cmd_name);
      }
      cmd->insert_nameserver(ns);
    } else if (args[0] == "-r") {
      //registrant
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("registrant parameter missing", cmd_name);
      }
      cmd->set_registrant(args[0]);
      args.remove_at(args.begin());
    } else if (args[0] == "-contact") {
      //contact
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("contact parameter missing", cmd_name);
      }

      string type;
      string value;
      if (SheppStrUtil::split(args[0], type, value, "=", false) != 0) {
	return cmd_domain_help("invalid contact", cmd_name);
      }

      cmd->insert_contact(type, value);
      args.remove_at(args.begin());      

    } else if (args[0] == "-auth") {
      //authInfo
      AuthInfo auth;
      if (ObjectSet::authInfo(auth, args) != 0) {
	return cmd_domain_help("invalid auth", cmd_name);
      }

      // roid not allowed in domain create command
      if (auth.get_roid_f() == true) {
	return cmd_domain_help("invalid auth", cmd_name);
      }

      cmd->set_authInfo(auth);
    } else if (args[0] == "-dnskey") {
      //DNSSEC data (RFC 5910)
      KeyData dnskey;
      string error_msg;
      if (ObjectSet::keyData(dnskey, args, error_msg) != 0) {
	return cmd_domain_help(error_msg, cmd_name);
      }
      cmd->add_keyData(dnskey);
    } else if (args[0] == "-ds") {
      //DNSSEC data (RFC 4310/5910)
      DSInfo ds;
      string error_msg;
      if (ObjectSet::dsInfo(ds, args, error_msg) != 0) {
	return cmd_domain_help(error_msg, cmd_name);
      }
      cmd->add_dsInfo(ds);
    } else if (args[0] == "-max-sig-life") {
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("maxSigLife parameter missing", cmd_name);
      }
      cmd->set_max_sig_life(atoi(args[0]));
      args.remove_at(args.begin());
#if USE_BR_DOMAINS
    } else if (args[0] == "-o") {
      //organization
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("organization parameter missing", cmd_name);
      }
      cmd->set_organization(args[0]);
      args.remove_at(args.begin());
    } else if (args[0] == "-rpflags") {
      //releaseProcessFlags
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("rpflags parameter missing", cmd_name);
      }
      ReleaseProcessFlags rpf;
      string flag1;
      string flag2;
      string flag3;

      if (SheppStrUtil::split(args[0], flag1, flag2, ":", false) != 0) {
	return cmd_domain_help("invalid rpflags", cmd_name);
      }

      if (SheppStrUtil::split(flag2, flag2, flag3, ":", false) != 0) {
	return cmd_domain_help("invalid rpflags", cmd_name);
      }
      
      rpf.flag1 = (flag1 == "0") ? 0 : 1;
      rpf.flag2 = (flag2 == "0") ? 0 : 1;
      rpf.flag3 = (flag3 == "0") ? 0 : 1;

      cmd->set_releaseProcessFlags(rpf);
      args.remove_at(args.begin());
    } else if (args[0] == "-auto-renew") {
      //auto-renew
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("auto-renew parameter missing", cmd_name);
      }
      if (args[0] == "on") {
	cmd->set_auto_renew(1);
      } else if (args[0] == "off") {
	cmd->set_auto_renew(0);
      } else {
	return cmd_domain_help("invalid auto-renew", cmd_name);
      }
      args.remove_at(args.begin());
#endif //USE_BR_DOMAINS
    } else {
      return cmd_domain_help("invalid syntax near \"" + args[0] + "\"",
			     cmd_name);
    }
  }
#if USE_BR_DOMAINS
  if (cmd->get_organization() == "") {
    return cmd_domain_help("organization is mandatory", cmd_name);
  }
#endif //USE_BR_DOMAINS

  if (_debug) {
    printf("creating domain: %s\n", cmd->get_name());
    
#if USE_BR_DOMAINS
    printf("  organization: %s\n", cmd->get_organization());
#endif //USE_BR_DOMAINS
    
    if (cmd->get_period().time != 0) {
      printf("  period: %d %s\n", cmd->get_period().time,
	     cmd->get_period().unit);
    }
    
    NameServerArray nss = cmd->get_nameservers();
    NameServerArray::const_iterator nsit;
    for (nsit = nss.begin(); nsit != nss.end(); nsit++) {
      SheppPrint::nameserver(*nsit);
    }
    
    if (cmd->get_registrant() != "") {
      printf("  registrant: %s\n", cmd->get_registrant());
    }
    
    string_to_string_map contacts = cmd->get_contacts();
    string_to_string_map::const_iterator cit;
    for (cit = contacts.begin(); cit != contacts.end(); cit++) {
      printf("  contact %s: %s\n", (*cit).first, (*cit).second);
    }
    
    SheppPrint::authInfo(cmd->get_authInfo());
    
#if USE_BR_DOMAINS
    if (cmd->get_releaseProcessFlags().flag1 == 1 ||
	cmd->get_releaseProcessFlags().flag2 == 1 ||
	cmd->get_releaseProcessFlags().flag3 == 1) {
      printf("  releaseProcessFlags: %d, %d, %d\n",
	     cmd->get_releaseProcessFlags().flag1,
	     cmd->get_releaseProcessFlags().flag2,
	     cmd->get_releaseProcessFlags().flag3);
    }

    printf("  auto-renew: %d\n", cmd->get_auto_renew());
#endif //USE_BR_DOMAINS
  } // _debug

  if (process_action(act) != 0) {
    return -1;
  }
  
  return 0;
}

/// domain check delete function
/**
   @param args   comparable_array with command-line arguments
   @return 0
*/
int cmd_domain_delete(stringa &args)
{
  DomainDelete act;
  DomainDeleteCommand *cmd = act.get_command();

  string cmd_name = "delete";

  if (args.is_empty()) {
    return cmd_domain_help("domain name missing", cmd_name);
  }
  
  // domain name MUST be the first attribute
  cmd->set_name(args[0]);
  args.remove_at(args.begin());

  if (_debug) {
    printf("deleting domain: %s\n", cmd->get_name());
  }

  if (process_action(act) != 0) {
    return -1;
  }
  
  return 0;
}

/// domain renew command function
/**
   @param args   comparable_array with command-line arguments
   @return 0
*/
int cmd_domain_renew(stringa &args)
{
#if USE_BR_DOMAINS
  BrDomainRenew act;
#else
  DomainRenew act;
#endif //USE_BR_DOMAINS
  DomainRenewCommand *cmd = act.get_command();
  string cmd_name = "renew";

  if (args.is_empty()) {
    return cmd_domain_help("domain name missing", cmd_name);
  }
  // domain name MUST be the first attribute
  cmd->set_name(args[0]);
  args.remove_at(args.begin());

  while (!args.is_empty()) {
    if (args[0] == "-expdate") {
      //-expdate
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("curExpDate missing", cmd_name);
      }
      cmd->set_curExpDate(args[0]);
      args.remove_at(args.begin());      
    } else if (args[0] == "-period") {
      args.remove_at(args.begin());      
      if (args.is_empty()) {
	return cmd_domain_help("period missing", cmd_name);
      }
      string str_time;
      string unit;
      if (SheppStrUtil::split(args[0], str_time, unit, ":", false) != 0) {
	return cmd_domain_help("error setting period", cmd_name);
      }
      RegistrationPeriod period;
      period.time = atoi(str_time);
      period.unit = unit;
      cmd->set_period(period);
      args.remove_at(args.begin());
    } else {
      return cmd_domain_help("invalid syntax near \"" + args[0] + "\"",
			     cmd_name);
    }
  }

  if (cmd->get_curExpDate() == "") {
    return cmd_domain_help("curExpDate is mandatory", cmd_name);
  }

  if (_debug) {
    printf("domain to renew: [%s]\n", cmd->get_name());
    printf("  curExpDate   : [%s]\n", cmd->get_curExpDate());
    if (cmd->get_period().time != 0 || cmd->get_period().unit != "") {
      printf("  period       : [%d %s]\n", cmd->get_period().time,
	     cmd->get_period().unit);
    }
  } //_debug

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// domain update command function
/**
   @param args   comparable_array with command-line arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_domain_update(stringa &args)
{
#if USE_BR_DOMAINS
  BrDomainUpdate act;
  BrDomainUpdateCommand *cmd = act.get_command();
#else
  DomainUpdate act;
  DomainUpdateCommand *cmd = act.get_command();
#endif //USE_BR_DOMAINS
  string cmd_name = "update";

  cmd->set_secDnsVersion(_serverSecDnsVersion);

  if (args.is_empty()) {
    return cmd_domain_help("domain name missing", cmd_name);
  }
  // domain name MUST be the first attribute
  cmd->set_name(args[0]);
  args.remove_at(args.begin());

  while (!args.is_empty()) {
    if (args[0] == "-add-ns") {
      //nameserver to add
      NameServer ns;
      if (ObjectSet::nameServer(ns, args) != 0) {
	return cmd_domain_help("invalid nameserver to add", cmd_name);
      }
      cmd->insert_nameserver_add(ns);
    } else if (args[0] == "-rem-ns") {
      //nameserver to remove
      NameServer ns;
      if (ObjectSet::nameServer(ns, args) != 0) {
	return cmd_domain_help("invalid nameserver to remove", cmd_name);
      }
      cmd->insert_nameserver_rem(ns);
    } else if (args[0] == "-add-contact") {
      //contact to add
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("add-contact parameter missing", cmd_name);
      }

      string type;
      string value;
      if (SheppStrUtil::split(args[0], type, value, "=", false) != 0) {
	return cmd_domain_help("invalid contact to add", cmd_name);
      }

      cmd->insert_contact_add(type, value);
      args.remove_at(args.begin());      

    } else if (args[0] == "-rem-contact") {
      //contact to remove
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("rem-contact parameter missing", cmd_name);
      }

      string type;
      string value;
      if (SheppStrUtil::split(args[0], type, value, "=", false) != 0) {
	return cmd_domain_help("invalid contact to remove", cmd_name);
      }

      cmd->insert_contact_rem(type, value);
      args.remove_at(args.begin());      

    } else if (args[0] == "-add-status") {
      //status to add
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("add-status parameter missing", cmd_name);
      }

      DomainUpdateCommand::Status st;
      if (ObjectSet::status(st, args) != 0) {
	return cmd_domain_help("invalid status to add", cmd_name);
      }
      cmd->insert_status_add(st);

    } else if (args[0] == "-rem-status") {
      //status to remove
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("rem-status parameter missing", cmd_name);
      }

      DomainUpdateCommand::Status st;
      st.s = args[0];
      args.remove_at(args.begin());

      cmd->insert_status_rem(st);

    } else if (args[0] == "-max-sig-life") {
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("maxSigLife parameter missing", cmd_name);
      }
      cmd->set_max_sig_life(atoi(args[0]));
      args.remove_at(args.begin());
    } else if (args[0] == "-add-dnskey") {
      //DNSSEC data (RFC 5910)
      KeyData dnskey;
      string error_msg;
      if (ObjectSet::keyData(dnskey, args, error_msg) != 0) {
	return cmd_domain_help(error_msg, cmd_name);
      }
      cmd->insert_dnskey_add(dnskey);
    } else if (args[0] == "-rem-dnskey") {
      //DNSSEC data (RFC 5910)
      KeyData dnskey;
      string error_msg;
      if (ObjectSet::keyData(dnskey, args, error_msg) != 0) {
	return cmd_domain_help(error_msg, cmd_name);
      }
      cmd->insert_dnskey_rem(dnskey);
    } else if (args[0] == "-remove-all-secdns") {
      args.remove_at(args.begin());
      cmd->setRemoveAll(true);
    } else if (args[0] == "-add-ds") {
      //DS to add
      DSInfo ds;
      string error_msg;
      if (ObjectSet::dsInfo(ds, args, error_msg) != 0) {
	return cmd_domain_help(error_msg, cmd_name);
      }
      cmd->insert_ds_add(ds);
    } else if (args[0] == "-rem-ds") {
      //DS to remove
      DSInfo ds;
      string error_msg;
      if (ObjectSet::dsInfo(ds, args, error_msg) != 0) {
	return cmd_domain_help(error_msg, cmd_name);
      }
      cmd->insert_ds_rem_1_1(ds);
    } else if (args[0] == "-rem-ds-1.0") {
      //DS to remove (RFC4310 - DEPRECATED!)
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("keytag parameter missing", cmd_name);
      }
      cmd->insert_ds_rem(atoi(args[0]));
    } else if (args[0] == "-chg-ds") {
      //DS to change
      DSInfo ds;
      string error_msg;
      if (ObjectSet::dsInfo(ds, args, error_msg) != 0) {
	return cmd_domain_help(error_msg, cmd_name);
      }
      cmd->insert_ds_chg(ds);
    } else if (args[0] == "-secDNS-urgent") {
      cmd->setUrgentFlag(true);
      args.remove_at(args.begin());
    } else if (args[0] == "-r") {
      //registrant
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("registrant parameter missing", cmd_name);
      }
      cmd->set_registrant(args[0]);
      args.remove_at(args.begin());
    } else if (args[0] == "-auth") {
      //authInfo
      AuthInfo auth;
      if (ObjectSet::authInfo(auth, args) != 0) {
	return cmd_domain_help("invalid auth", cmd_name);
      }

      // roid not allowed in update command
      if (auth.get_roid_f() == true) {
	return cmd_domain_help("invalid auth", cmd_name);
      }

      cmd->set_authInfo(auth);
#if USE_BR_DOMAINS
    } else if (args[0] == "-t") {
      // ticketNumber
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("ticket number parameter missing", cmd_name);
      }
      if (atoi(args[0]) <= 0) {
	return cmd_domain_help("ticket parameter must be a positive integer",
			       cmd_name);
      }
      cmd->set_ticketNumber(atoi(args[0]));
      args.remove_at(args.begin());
    } else if (args[0] == "-rpflags") {
      //releaseProcessFlags
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("rpflags parameter missing", cmd_name);
      }
      ReleaseProcessFlags rpf;
      string flag1;
      string flag2;
      string flag3;

      if (SheppStrUtil::split(args[0], flag1, flag2, ":", false) != 0) {
	return cmd_domain_help("invalid rpflags", cmd_name);
      }

      if (SheppStrUtil::split(flag2, flag2, flag3, ":", false) != 0) {
	return cmd_domain_help("invalid rpflags", cmd_name);
      }
      
      if (flag1 == "0" || flag1 == "1") {
	rpf.flag1 = atoi(flag1);
      } else if (flag1 != "-1") {
	return cmd_domain_help("rpflags invalid parameter. "
			       "Expected '-1', '0' or '1'.", cmd_name);
      }
      if (flag2 == "0" || flag2 == "1") {
	rpf.flag2 = atoi(flag2);
      } else if (flag2 != "-1") {
	return cmd_domain_help("rpflags invalid parameter. "
			       "Expected '-1', '0' or '1'.", cmd_name);
      }
      if (flag3 == "0" || flag3 == "1") {
	rpf.flag3 = atoi(flag3);
      } else if (flag3 != "-1") {
	return cmd_domain_help("rpflags invalid parameter. "
			       "Expected '-1', '0' or '1'.", cmd_name);
      }

      cmd->set_releaseProcessFlags(rpf);
      args.remove_at(args.begin());
    } else if (args[0] == "-auto-renew") {
      //auto-renew
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_domain_help("auto-renew parameter missing", cmd_name);
      }
      if (args[0] == "on") {
	cmd->set_auto_renew(1);
      } else if (args[0] == "off") {
	cmd->set_auto_renew(0);
      } else {
	return cmd_domain_help("invalid auto-renew", cmd_name);
      }
      args.remove_at(args.begin());
#endif //USE_BR_DOMAINS
    } else {
      return cmd_domain_help("invalid syntax near \"" + args[0] + "\"",
			     cmd_name);
    }
  }

#if USE_BR_DOMAINS
  bool brdomain_rpf_update = false;
  //if it has brdomain attributes comparable_array it MUST have ticketNumber also
  if (cmd->get_releaseProcessFlags().flag1 != -1 ||
      cmd->get_releaseProcessFlags().flag2 != -1 ||
      cmd->get_releaseProcessFlags().flag3 != -1) {
    brdomain_rpf_update = true;
  }

  if (brdomain_rpf_update && cmd->get_ticketNumber() == 0) {
    return cmd_domain_help("BrDomain extension rpf updates "
			   "MUST contain ticketNumber", cmd_name);
  }
#endif //USE_BR_DOMAINS

  if (cmd->get_nameserver_add().is_empty() &&
      cmd->get_nameserver_rem().is_empty() &&
      cmd->has_secdns_extension() == false &&
      cmd->get_contact_add().is_empty() &&
      cmd->get_contact_rem().is_empty() &&
      cmd->get_status_add().is_empty() &&
      cmd->get_status_rem().is_empty() &&
      cmd->get_registrant() == "" &&
      cmd->get_authInfo().get_pw() == ""
#if USE_BR_DOMAINS
      && !brdomain_rpf_update && cmd->get_auto_renew() == -1
#endif //USE_BR_DOMAINS
      ) {
    return cmd_domain_help("you didn't comparable_array a thing", cmd_name);
  }

  if (_debug) {
    printf("updating domain: %s\n", cmd->get_name());
    
    NameServerArray nss = cmd->get_nameserver_add();
    NameServerArray::const_iterator nsit;
    if (!nss.is_empty()) {
      printf("  nameservers to add:\n");
    }
    for (nsit = nss.begin(); nsit != nss.end(); nsit++) {
      SheppPrint::nameserver(*nsit);
    }
    
    nss = cmd->get_nameserver_rem();
    if (!nss.is_empty()) {
      printf("  nameservers to remove:\n");
    }
    for (nsit = nss.begin(); nsit != nss.end(); nsit++) {
      SheppPrint::nameserver(*nsit);
    }
    
    if (cmd->get_registrant() != "") {
      printf("  registrant: %s\n", cmd->get_registrant());
    }
    
    string_to_string_map contacts = cmd->get_contact_add();
    string_to_string_map::const_iterator cit;
    if (!contacts.is_empty()) {
      printf("  contacts to add:\n");
    }
    for (cit = contacts.begin(); cit != contacts.end(); cit++) {
      printf("  contact %s: %s\n", (*cit).first,
	     (*cit).second);
    }
    
    contacts = cmd->get_contact_rem();
    if (!contacts.is_empty()) {
      printf("  contacts to remove:\n");
    }
    for (cit = contacts.begin(); cit != contacts.end(); cit++) {
      printf("  contact %s: %s\n", (*cit).first,
	     (*cit).second);
    }
    
    comparable_array<DomainUpdateCommand::Status> statuses = cmd->get_status_add();
    comparable_array<DomainUpdateCommand::Status>::const_iterator stit;
    if (!statuses.is_empty()) {
      printf("  status to add:\n");
    }
    for (stit = statuses.begin(); stit != statuses.end(); stit++) {
      printf("    s   : [%s]\n", (*stit).s);
      printf("    lang: [%s]\n", (*stit).lang);
      printf("    msg : [%s]\n", (*stit).msg);
    }
    statuses = cmd->get_status_rem();
    if (!statuses.is_empty()) {
      printf("  status to remove:\n");
    }
    for (stit = statuses.begin(); stit != statuses.end(); stit++) {
      printf("    s   : [%s]\n", (*stit).s);
      printf("    lang: [%s]\n", (*stit).lang);
      printf("    msg : [%s]\n", (*stit).msg);
    }
    
    SheppPrint::authInfo(cmd->get_authInfo());
    
#if USE_BR_DOMAINS
    if (cmd->get_ticketNumber() != 0) {
      printf("  ticketNumber: [%d]\n", cmd->get_ticketNumber());
    }
    
    if (cmd->get_releaseProcessFlags().flag1 != -1 ||
	cmd->get_releaseProcessFlags().flag2 != -1 ||
	cmd->get_releaseProcessFlags().flag3 != -1) {
      printf("  releaseProcessFlags: %d, %d, %d\n",
	     cmd->get_releaseProcessFlags().flag1,
	     cmd->get_releaseProcessFlags().flag2,
	     cmd->get_releaseProcessFlags().flag3);
    }

    printf("  auto-renew: %d\n", cmd->get_auto_renew());
#endif //USE_BR_DOMAINS
  } // _debug

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// main domain command
/**
   @param arg   command-line input arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_domain(stringa &args)
{
  // domain command processing
  if (!args.is_empty() && !(args[0] == "help")) {
    if (args[0] == "check") {
      args.remove_at(args.begin());
      return cmd_domain_check(args);
    } else if (args[0] == "info") {
      args.remove_at(args.begin());
      return cmd_domain_info(args);
    } else if (args[0] == "transfer") {
      args.remove_at(args.begin());
      return cmd_domain_transfer(args);
    } else if (args[0] == "create") {
      args.remove_at(args.begin());
      return cmd_domain_create(args);
    } else if (args[0] == "delete") {
      args.remove_at(args.begin());
      return cmd_domain_delete(args);
    } else if (args[0] == "renew") {
      args.remove_at(args.begin());
      return cmd_domain_renew(args);
    } else if (args[0] == "update") {
      args.remove_at(args.begin());
      return cmd_domain_update(args);
    } else {
      return cmd_domain_help("invalid command: domain " + args[0]);
    }
  }
  
  return cmd_domain_help("");
}

#endif //__DOMAIN_FUNCTIONS_H__

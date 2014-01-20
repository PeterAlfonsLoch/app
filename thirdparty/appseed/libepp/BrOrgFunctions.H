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
/* $Id: BrOrgFunctions.H 1058 2010-07-05 18:31:53Z cesar $ */
/** @file BrOrgFunctions.H
 *  @brief EPP BrOrg related functions
 */
#pragma once


/// print brorg command usage info
/**
   @param error_msg   error message to be printed
   @param specific    optional, choses specific sub-command
   @return 0 if ok, -1 otherwise
*/
int cmd_brorg_help(string error_msg, string specific = "")
{
  if (error_msg != "") {
    printf("error: %s\n", error_msg);
  }

  printf("brorg command syntax help:\n");
  printf("\n");

  if (specific == "" || specific == "check") {
    printf("  check <brorg1> [brorg2 ... brorgN]\n");
    printf("\n");
  }
  if (specific == "" || specific == "info") {
    printf("  info <brorg> [-auth authInfoPw]\n");
    printf("\n");
  }
  if (specific == "" || specific == "transfer") {
    printf("  transfer: not implemented\n");
    printf("\n");
  }
  if (specific == "" || specific == "create") {
    printf("  create <brorg>\n");
    printf("    [-postalInfo <type> <-name \"BrOrg Name\"> "
	   "[-org \"Org Name\"]\n");
    printf("    <-street1 \"address street/line 1\"> "
	   "[-street2 \"address number/line 2\"]\n");
    printf("    [-street3 \"address line 3\"] <-city \"City Name\"> "
	   "[-state \"State or Province\"]\n");
    printf("    [-pc \"postal code\"] <-cc country-code> ...]\n");
    printf("    <-voice number:ext> [-fax number:ext]\n");
    printf("    <-email emailAddr> [-auth authInfoPw]\n");
    printf("    [-disclose opt,opt,...] "
	   " [-responsible \"Responsible Name\"]\n"
	   "     -contact key=value[,key=value,...]\n");
    printf("\n");
    printf("    available values for opt:\n");
    printf("    {name_int name_loc org_int org_loc addr_int addr_loc "
	   "voice fax email}\n");
    printf("\n");
  }
  if (specific == "" || specific == "delete") {
    printf("  delete: not implemented\n");
    printf("\n");
  }
  if (specific == "" || specific == "renew") {
    printf("  renew: not implemented\n");
    printf("\n");
  }
  if (specific == "" || specific == "update") {
    printf("  update <brorg> [-add-status st1,...,stN] "
	   "[-rem-status st1,...,stN]\n");
    printf("    [-postalInfo <type> [-name \"BrOrg Name\"] "
	   "[-org \"Org Name\"]\n");
    printf("    [-street1 \"address street/line 1\"] "
	   "[-street2 \"address number/line 2\"]\n");
    printf("    [-street3 \"address line 3\"] [-city \"City Name\"] "
	   "[-state \"State or Province\"]\n");
    printf("    [-pc \"postal code\"] [-cc country-code] ...]\n");
    printf("    [-voice number:ext] [-fax number:ext]\n");
    printf("    [-email emailAddr] [-auth authInfoPw] "
	   "[-disclose opt,opt,...]\n");
    printf("    [-responsible \"Responsible Name\"]\n");
    printf("    [-exdate expirationDate]\n");
    printf("    [-add-contact key=value[,key=value,...]\n");
    printf("    [-rem-contact key=value[,key=value,...]\n");
    printf("\n");
    printf("    available values for opt:\n");
    printf("    {name_int name_loc org_int org_loc addr_int addr_loc "
	   "voice fax email}\n");
    printf("\n");
  }

  if (error_msg != "") {
    return -1;
  }

  return 0;
}

/// brorg check command function
/**
   @param args   comparable_array with command-line arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_brorg_check(stringa &args)
{
  BrOrgCheck act;
  BrOrgCheckCommand *cmd = act.get_command();
  string cmd_name = "check";

  string id;
  int counter = 0;
  while (!args.is_empty()) {
    string numbers = SheppStrUtil::doc2id(args[0]);
    cmd->insert_id(numbers);
    cmd->insert_organization(numbers, args[0]);
    args.remove_at(args.begin());
    counter++;
  }

  if (cmd->get_id_list().is_empty() || cmd->get_organization_list().is_empty()) {
    return cmd_brorg_help("no brorg specified", cmd_name);
  }

  if (_debug) {
    string_to_string_map brorgs = cmd->get_organization_list();
    string_to_string_map::const_iterator it;
    printf("brorgs to be checked:\n");
    for (it = brorgs.begin(); it != brorgs.end(); it++) {
      printf("  id: [%s] org: [%s]\n", (*it).first,
	     (*it).second);
    }
  } // _debug

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// brorg info command function
/**
   @param args   comparable_array with command-line arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_brorg_info(stringa &args)
{
  BrOrgInfo act;
  BrOrgInfoCommand *cmd = act.get_command();
  string cmd_name = "info";

  if (args.is_empty()) {
    return cmd_brorg_help("no brorg specified", cmd_name);
  }

  cmd->set_id(SheppStrUtil::doc2id(args[0]));
  cmd->set_organization(args[0]);
  args.remove_at(args.begin());

  while (!args.is_empty()) {
    if (args[0] == "-auth") {
      //comparable_array authInfo
      AuthInfo auth;
      if (ObjectSet::authInfo(auth, args) != 0) {
	return cmd_brorg_help("invalid auth", cmd_name);
      }

      // roid not allowed in brorg commands
      if (auth.get_roid_f() == true) {
	return cmd_contact_help("invalid auth", cmd_name);
      }

      cmd->set_authInfo(auth);
    } else {
      return cmd_brorg_help("invalid syntax near \"" + args[0] + "\"",
			    cmd_name);
    }

  }

  if (_debug) {
    printf("id  to get info: [%s]\n", cmd->get_id());
    printf("org to get info: [%s]\n", cmd->get_organization());
    SheppPrint::authInfo(cmd->get_authInfo());
  } // _debug

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// brorg transfer command function
/**
   @param args   comparable_array with command-line arguments
   @return 0
*/
int cmd_brorg_transfer(stringa &args)
{
  string cmd_name = "transfer";
  return cmd_brorg_help("", cmd_name);
}

/// brorg create command function
/**
   @param args   comparable_array with command-line arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_brorg_create(stringa &args)
{
  BrOrgCreate act;
  BrOrgCreateCommand *cmd = act.get_command();
  string cmd_name = "create";

  if (args.is_empty()) {
    return cmd_brorg_help("no brorg specified", cmd_name);
  }

  CommonData common_data;

  common_data.set_id(SheppStrUtil::doc2id(args[0]));
  cmd->set_organization(args[0]);

  args.remove_at(args.begin());

  //authInfo defaults to is_empty()
  AuthInfo auth;
  cmd->set_authInfo(auth);

  while (!args.is_empty()) {
    if (args[0] == "-postalInfo") {
      //postalInfo
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("missing postal info arguments", cmd_name);
      }
      PostalInfo postal;
      string error_msg;
      if (ObjectSet::postalInfo(postal, args, error_msg, false) != 0) {
	return cmd_brorg_help(error_msg, cmd_name);
      }
      comparable_array<PostalInfo> postal_list = common_data.get_postal_info();
      for (int i = 0; i < (int) postal_list.size(); i++) {
	if (postal_list[i].get_type() == postal.get_type()) {
	  return cmd_brorg_help("duplicated postal info type", cmd_name);
	}
      }
      common_data.insert_postal_info(postal);
    } else if (args[0] == "-voice") {
      //voice
      args.remove_at(args.begin());
      CommonData::Phone phone;
      if (ObjectSet::phone(phone, args) != 0) {
	return cmd_brorg_help("error setting voice telephone number",
			      cmd_name);
      }
      common_data.set_voice(phone);
    } else if (args[0] == "-fax") {
      //fax
      args.remove_at(args.begin());
      CommonData::Phone phone;
      if (ObjectSet::phone(phone, args) != 0) {
	return cmd_brorg_help("error setting fax telephone number",
			      cmd_name);
      }
      common_data.set_fax(phone);
    } else if (args[0] == "-email") {
      //email
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("no e-mail address specified", cmd_name);
      }
      common_data.set_email(args[0]);
      args.remove_at(args.begin());
    } else if (args[0] == "-auth") {
      //auth
      AuthInfo auth;
      if (ObjectSet::authInfo(auth, args) != 0) {
	return cmd_brorg_help("invalid auth", cmd_name);
      }

      // roid not allowed in brorg commands
      if (auth.get_roid_f() == true) {
	return cmd_contact_help("invalid auth", cmd_name);
      }

      cmd->set_authInfo(auth);
    } else if (args[0] == "-disclose") {
      //disclose
      args.remove_at(args.begin());
      CommonData::Disclose disclose;
      if (ObjectSet::disclose(disclose, args[0]) != 0) {
	return cmd_brorg_help("invalid diclose information", cmd_name);
      }
      args.remove_at(args.begin());
      common_data.set_disclose(disclose);
    } else if (args[0] == "-contact") {
      //contacts
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("-contact requires an argument", cmd_name);
      }
      string_to_string_map my_contacts;
      string error_msg;
      if (ObjectSet::contacts(my_contacts, args[0], error_msg) != 0) {
	return cmd_brorg_help(error_msg, cmd_name);
      }
      string_to_string_map::const_iterator it;
      for (it = my_contacts.begin(); it != my_contacts.end(); it++) {
	cmd->insert_contact((*it).first, (*it).second);
      }
      args.remove_at(args.begin());
    } else if (args[0] == "-responsible") {
      //responsible
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("unspecified responsible name", cmd_name);
      }
      string responsible_name = args[0];
      args.remove_at(args.begin());
      if (SheppStrUtil::quote_gathering(args, responsible_name) != 0) {
	return cmd_brorg_help("error setting responsible name", cmd_name);
      }
      cmd->set_responsible(responsible_name);
    } else {
      return cmd_brorg_help("invalid syntax near \"" + args[0] + "\"",
			    cmd_name);
    }
  }

  if (common_data.get_postal_info().is_empty()) {
    return cmd_brorg_help("at least one postal info must be entered",
			  cmd_name);
  }

  if (common_data.get_email() == "") {
    return cmd_brorg_help("e-mail is mandatory", cmd_name);
  }

  if (common_data.get_voice().number == "") {
    return cmd_brorg_help("voice telephone number is mandatory", cmd_name);
  }

  if (cmd->get_organization() == "") {
    return cmd_brorg_help("orgid unset", cmd_name);
  }

  if (cmd->get_contact_list().is_empty()) {
    return cmd_brorg_help("at least one contact must be entered", cmd_name);
  }

  cmd->set_common_data(common_data);

  if (_debug) {
    printf("  brorg: [%s]\n", cmd->get_common_data().get_id());
    
    comparable_array<PostalInfo>::const_iterator it;
    comparable_array<PostalInfo> postal_list;
    postal_list = cmd->get_common_data().get_postal_info();
    for (it = postal_list.begin(); it != postal_list.end(); it++) {
      SheppPrint::postal_info((*it));
    }
    
    if (cmd->get_common_data().get_voice().number != "") {
      printf("  voice:");
      SheppPrint::phone(cmd->get_common_data().get_voice());
    }
    
    if (cmd->get_common_data().get_fax().number != "") {
      printf("  fax  :");
      SheppPrint::phone(cmd->get_common_data().get_fax());
    }
    
    printf("  email: [%s]\n", cmd->get_common_data().get_email());
    
    SheppPrint::authInfo(cmd->get_authInfo());
    
    if (cmd->get_common_data().get_disclose().is_set()) {
      SheppPrint::disclose(cmd->get_common_data().get_disclose());
    }
    
    //brorg
    printf("  orgid: [%s]\n", cmd->get_organization());
    
    string_to_string_map contacts = cmd->get_contact_list();
    string_to_string_map::const_iterator c_it;
    for (c_it = contacts.begin(); c_it != contacts.end(); c_it++) {
      printf("  contact[%s] = [%s]\n", (*c_it).first,
	     (*c_it).second);
    }
  } // _debug

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// brorg delete command function
/**
   @param args   comparable_array with command-line arguments
   @return 0
*/
int cmd_brorg_delete(stringa &args)
{
  string cmd_name = "delete";
  return cmd_brorg_help("", cmd_name);
}

/// brorg renew command function
/**
   @param args   comparable_array with command-line arguments
   @return 0
*/
int cmd_brorg_renew(stringa &args)
{
  string cmd_name = "renew";
  return cmd_brorg_help("", cmd_name);
}

/// brorg update command function
/**
   @param args   comparable_array with command-line arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_brorg_update(stringa &args)
{
  BrOrgUpdate act;
  BrOrgUpdateCommand *cmd = act.get_command();
  string cmd_name = "update";

  if (args.is_empty()) {
    return cmd_brorg_help("no brorg specified", cmd_name);
  }

  CommonData common_data;
  common_data.set_id(SheppStrUtil::doc2id(args[0]));

  cmd->set_organization(args[0]);
  args.remove_at(args.begin());

  while (!args.is_empty()) {
    if (args[0] == "-add-status") {
      //add-status
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("error setting add-status", cmd_name);
      }
      string tmp1 = args[0];
      string tmp2;
      while (SheppStrUtil::split(tmp1, tmp1, tmp2, ",", true) == 0) {
	cmd->insert_status_list_add(tmp1);
	if (tmp2 == "") {
	  break;
	}
	tmp1 = tmp2;
      }
      args.remove_at(args.begin());
    } else if (args[0] == "-rem-status") {
      //rem-status
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("error setting rem-status", cmd_name);
      }
      string tmp1 = args[0];
      string tmp2;
      while (SheppStrUtil::split(tmp1, tmp1, tmp2, ",", true) == 0) {
	cmd->insert_status_list_rem(tmp1);
	if (tmp2 == "") {
	  break;
	}
	tmp1 = tmp2;
      }
      args.remove_at(args.begin());
    } else if (args[0] == "-postalInfo") {
      //postalInfo
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("missing postal info arguments", cmd_name);
      }
      PostalInfo postal;
      string error_msg;
      if (ObjectSet::postalInfo(postal, args, error_msg, true) != 0) {
	return cmd_brorg_help(error_msg, cmd_name);
      }
      comparable_array<PostalInfo> postal_list = common_data.get_postal_info();
      for (int i = 0; i < (int) postal_list.size(); i++) {
	if (postal_list[i].get_type() == postal.get_type()) {
	  return cmd_brorg_help("duplicated postal info type", cmd_name);
	}
      }
      common_data.insert_postal_info(postal);
    } else if (args[0] == "-voice") {
      //voice
      args.remove_at(args.begin());
      CommonData::Phone phone;
      if (ObjectSet::phone(phone, args) != 0) {
	return cmd_brorg_help("error setting voice telephone number",
			      cmd_name);
      }
      common_data.set_voice(phone);
    } else if (args[0] == "-fax") {
      //fax
      args.remove_at(args.begin());
      CommonData::Phone phone;
      if (ObjectSet::phone(phone, args) != 0) {
	return cmd_brorg_help("error setting fax telephone number",
			      cmd_name);
      }
      common_data.set_fax(phone);
    } else if (args[0] == "-email") {
      //email
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("no e-mail address specified", cmd_name);
      }
      common_data.set_email(args[0]);
      args.remove_at(args.begin());
    } else if (args[0] == "-auth") {
      //auth
      AuthInfo auth;
      if (ObjectSet::authInfo(auth, args) != 0) {
	return cmd_brorg_help("invalid auth", cmd_name);
      }

      // roid not allowed in update command
      if (auth.get_roid_f() == true) {
	return cmd_brorg_help("invalid auth", cmd_name);
      }
      
      cmd->set_authInfo(auth);
    } else if (args[0] == "-disclose") {
      //disclose
      args.remove_at(args.begin());
      CommonData::Disclose disclose;
      if (ObjectSet::disclose(disclose, args[0]) != 0) {
	return cmd_brorg_help("invalid diclose information", cmd_name);
      }
      args.remove_at(args.begin());
      common_data.set_disclose(disclose);
    } else if (args[0] == "-add-contact") {
      //add contacts
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("-add-contact requires an argument",
			      cmd_name);
      }
      string_to_string_map my_contacts;
      string error_msg;
      if (ObjectSet::contacts(my_contacts, args[0], error_msg) != 0) {
	return cmd_brorg_help(error_msg, cmd_name);
      }
      string_to_string_map::const_iterator it;
      for (it = my_contacts.begin(); it != my_contacts.end(); it++) {
	cmd->insert_contact_add((*it).first, (*it).second);
      }
      args.remove_at(args.begin());
    } else if (args[0] == "-rem-contact") {
      //remove contacts
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("-rem-contact requires an argument",
			      cmd_name);
      }
      string_to_string_map my_contacts;
      string error_msg;
      if (ObjectSet::contacts(my_contacts, args[0], error_msg) != 0) {
	return cmd_brorg_help(error_msg, cmd_name);
      }
      string_to_string_map::const_iterator it;
      for (it = my_contacts.begin(); it != my_contacts.end(); it++) {
	cmd->insert_contact_rem((*it).first, (*it).second);
      }
      args.remove_at(args.begin());

    } else if (args[0] == "-responsible") {
      //responsible
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("unspecified responsible name", cmd_name);
      }
      string responsible_name = args[0];
      args.remove_at(args.begin());
      if (SheppStrUtil::quote_gathering(args, responsible_name) != 0) {
	return cmd_brorg_help("error setting responsible name", cmd_name);
      }
      cmd->set_responsible(responsible_name);
    } else if (args[0] == "-exdate") {
      //expiration date
      args.remove_at(args.begin());
      if (args.is_empty()) {
	return cmd_brorg_help("unspecified expiration date", cmd_name);
      }
      cmd->set_exDate(args[0]);
      args.remove_at(args.begin());
    } else {
      return cmd_brorg_help("invalid syntax near \"" + args[0] + "\"",
			    cmd_name);
    }
  }

  if (cmd->get_status_list_add().is_empty() &&
      cmd->get_status_list_rem().is_empty() &&
      common_data.get_postal_info().is_empty() &&
      common_data.get_voice().number == "" &&
      common_data.get_fax().number == "" &&
      common_data.get_email() == "" &&
      cmd->get_authInfo().get_pw() == "" &&
      !common_data.get_disclose().is_set() &&
      cmd->get_organization() == "") {
    return cmd_brorg_help("not enough information for update", cmd_name);
  }

  cmd->set_common_data(common_data);

  if (_debug) {
    printf("  brorg: [%s]\n", cmd->get_common_data().get_id());
    
    stringa status = cmd->get_status_list_add();
    stringa::const_iterator st_it;
    if (!status.is_empty()) {
      printf("  status to add: [ ");
      for (st_it = status.begin(); st_it != status.end(); st_it++) {
	printf("%s ", (*st_it));
      }
      printf("]\n");
    }
    
    status = cmd->get_status_list_rem();
    if (!status.is_empty()) {
      printf("  status to rem: [ ");
      for (st_it = status.begin(); st_it != status.end(); st_it++) {
	printf("%s ", (*st_it));
      }
      printf("]\n");
    }
    
    comparable_array<PostalInfo> postal_list;
    postal_list = cmd->get_common_data().get_postal_info();
    for (int i = 0; i < (int) postal_list.size(); i++) {
      SheppPrint::postal_info(postal_list[i]);
    }
    
    if (cmd->get_common_data().get_voice().number != "") {
      printf("  voice:");
      SheppPrint::phone(cmd->get_common_data().get_voice());
    }
    
    if (cmd->get_common_data().get_fax().number != "") {
      printf("  fax  :");
      SheppPrint::phone(cmd->get_common_data().get_fax());
    }
    
    if (cmd->get_common_data().get_email() != "") {
      printf("  email: [%s]\n", cmd->get_common_data().get_email());
    }
    
    if (cmd->get_authInfo().get_pw() != "") {
      SheppPrint::authInfo(cmd->get_authInfo());
    }
    
    if (cmd->get_common_data().get_disclose().is_set()) {
      SheppPrint::disclose(cmd->get_common_data().get_disclose());
    }
    
    //brorg
    if (cmd->get_organization() != "") {
      printf("  orgid: [%s]\n", cmd->get_organization());
      
      string_to_string_map contacts =
	cmd->get_contact_list_add();
      string_to_string_map::const_iterator c_it;
      for (c_it = contacts.begin(); c_it != contacts.end(); c_it++) {
	printf("  contact to add [%s] = [%s]\n", (*c_it).first,
	       (*c_it).second);
      }
      
      contacts = cmd->get_contact_list_rem();
      for (c_it = contacts.begin(); c_it != contacts.end(); c_it++) {
	printf("  contact to rem [%s] = [%s]\n", (*c_it).first,
	       (*c_it).second);
      }
    }
  } // _debug

  if (process_action(act) != 0) {
    return -1;
  }

  return 0;
}

/// main brorg command
/**
   @param arg   command-line input arguments
   @return 0 if ok, -1 otherwise
*/
int cmd_brorg(stringa &args)
{
  // brorg command processing
  if (!args.is_empty() && !(args[0] == "help")) {
    if (args[0] == "check") {
      args.remove_at(args.begin());
      return cmd_brorg_check(args);
    } else if (args[0] == "info") {
      args.remove_at(args.begin());
      return cmd_brorg_info(args);
    } else if (args[0] == "transfer") {
      args.remove_at(args.begin());
      return cmd_brorg_transfer(args);
    } else if (args[0] == "create") {
      args.remove_at(args.begin());
      return cmd_brorg_create(args);
    } else if (args[0] == "delete") {
      args.remove_at(args.begin());
      return cmd_brorg_delete(args);
    } else if (args[0] == "renew") {
      args.remove_at(args.begin());
      return cmd_brorg_renew(args);
    } else if (args[0] == "update") {
      args.remove_at(args.begin());
      return cmd_brorg_update(args);
    } else {
      return cmd_brorg_help("invalid command: brorg " + args[0]);
    }
  }
  
  return cmd_brorg_help("");
}

#endif //__BRORG_FUNCTIONS_H__

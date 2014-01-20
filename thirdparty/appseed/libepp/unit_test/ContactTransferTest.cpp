/* 
 * Copyright (C) 2009 Registro.br. All rights reserved.
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
/* $Id$ */

#include <string>
#include <memory>
#include <iostream>

#include "libepp_nicbr.H"
#include "StrUtil.H"

#include "ContactTransferTest.H"
#include "ContactTransfer.H"
#include "FileUtil.H"
#include "IoException.H"
#include "XmlException.H"

using std::auto_ptr;

LIBEPP_NICBR_NS_USE

CPPUNIT_TEST_SUITE_REGISTRATION(ContactTransferTest);

ContactTransferTest::ContactTransferTest() {}

ContactTransferTest::~ContactTransferTest() {}

void ContactTransferTest::setUp() {}

void ContactTransferTest::tearDown() {}

void ContactTransferTest::set_xml_template_test()
{
  string to_be_parsed =
    "<command>"
      "<transfer op='query'>"
        "<contact:transfer "
         "xmlns:contact='urn:ietf:params:xml:ns:contact-1.0' "
         "xsi:schemaLocation='urn:ietf:params:xml:ns:contact-1.0 "
         "contact-1.0.xsd'>"
          "<contact:id>$(id)$</contact:id>"
         "$(auth_info)$"
        "</contact:transfer>"
      "</transfer>"
    "$(clTRID)$"
   "</command>";

  ContactTransfer contact_transfer;
  ContactTransferCmd* contact_transfer_cmd = contact_transfer.get_command();
  contact_transfer_cmd->set_id("cem456");

  AuthInfo authInfo;
  authInfo.set_pw("2fooBAR");
  contact_transfer_cmd->set_authInfo(authInfo);
    
  contact_transfer.get_command()->set_clTRID("ABC-12345");
  contact_transfer.set_xml_template(to_be_parsed);

  string expected =
    "<command>"
      "<transfer op='query'>"
        "<contact:transfer "
         "xmlns:contact='urn:ietf:params:xml:ns:contact-1.0' "
         "xsi:schemaLocation='urn:ietf:params:xml:ns:contact-1.0 "
         "contact-1.0.xsd'>"
          "<contact:id>cem456</contact:id>"
          "<contact:authInfo>"
            "<contact:pw>2fooBAR</contact:pw>"
          "</contact:authInfo>"
        "</contact:transfer>"
      "</transfer>"
      "<clTRID>ABC-12345</clTRID>"
   "</command>";

  CPPUNIT_ASSERT_EQUAL(expected, contact_transfer.get_xml());

  // tests reset method
  CPPUNIT_ASSERT(contact_transfer_cmd->get_id() != "");
  CPPUNIT_ASSERT(contact_transfer_cmd->get_authInfo().get_pw() != "");
  contact_transfer_cmd->reset();
  CPPUNIT_ASSERT(contact_transfer_cmd->get_id() == "");
  CPPUNIT_ASSERT(contact_transfer_cmd->get_authInfo().get_roid() == "");
  CPPUNIT_ASSERT(contact_transfer_cmd->get_authInfo().get_pw() == "");

  // parent attribute
  CPPUNIT_ASSERT(contact_transfer_cmd->get_clTRID() == "");
}

void ContactTransferTest::command_test()
{
  ContactTransfer contact_transfer;
  ContactTransferCmd *contact_transfer_cmd = contact_transfer.get_command();

  contact_transfer_cmd->set_id("cem456");

  AuthInfo authInfo;
  authInfo.set_pw("2fooBAR");
  contact_transfer_cmd->set_authInfo(authInfo);

  bool exception_caught = false;
  try {
    string xml_template = 
      FileUtil::read_file("../docs/templates/contact_transfer.xml");

    contact_transfer.get_command()->set_clTRID("ABC-12345");
    contact_transfer.set_xml_template(xml_template);

    DomParser parser;
    parser.enable_validation("../docs/schemas");
    parser.parse_command(contact_transfer.get_xml());
  } catch (const IoException &e) {
    exception_caught = true;
    printf("\nIO Exception: code [%d] message [%s]",
	e.get_code(), e.get_msg().c_str());
  } catch (const XmlException &e) {
    exception_caught = true;
    printf("\nXml Exception: code [%d] message [%s] low level message [%s]\n",
	   e.get_code(), e.get_msg().c_str(), e.get_low_level_msg().c_str());
  }

  CPPUNIT_ASSERT(!exception_caught);
}

void ContactTransferTest::response_test()
{
  string expected =
    "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
    "<epp xmlns=\"urn:ietf:params:xml:ns:epp-1.0\" "
    "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
    "xsi:schemaLocation=\"urn:ietf:params:xml:ns:epp-1.0 "
    "epp-1.0.xsd\">"
    "<response>"
    "<result code='1000'>"
    "<msg>Command completed successfully</msg>"
    "</result>"
    "<resData>"
    "<contact:trnData"
    " xmlns:contact=\"urn:ietf:params:xml:ns:contact-1.0\""
    " xsi:schemaLocation=\"urn:ietf:params:xml:ns:contact-1.0 "
    "contact-1.0.xsd\">"
    "<contact:id>sh8013</contact:id>"
    "<contact:trStatus>pending</contact:trStatus>"
    "<contact:reID>ClientX</contact:reID>"
    "<contact:reDate>2000-06-06T22:00:00.0Z</contact:reDate>"
    "<contact:acID>ClientY</contact:acID>"
    "<contact:acDate>2000-06-11T22:00:00.0Z</contact:acDate>"
    "</contact:trnData>"
    "</resData>"
    "<trID>"
    "<clTRID>ABC-12345</clTRID>"
    "<svTRID>DEF-54321</svTRID>"
    "</trID>"
    "</response>"
    "</epp>";
  
  DomParser parser;
  parser.enable_validation("../docs/schemas");
  
  ContactTransfer contact_transfer;
  CPPUNIT_ASSERT_NO_THROW(contact_transfer.set_response(expected, &parser));
  
  ContactTransferRsp* contact_transfer_rsp = contact_transfer.get_response();
  
  map <Response::ResultCode, Response::ResultInfo> results;
  map <Response::ResultCode, Response::ResultInfo>::const_iterator r_it;
  results = contact_transfer_rsp->get_result_list();
  r_it = results.begin();

  CPPUNIT_ASSERT(r_it != results.end());
  CPPUNIT_ASSERT_EQUAL(Response::OK, r_it->first);

  string response =
    "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
    "<epp xmlns=\"urn:ietf:params:xml:ns:epp-1.0\" "
    "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
    "xsi:schemaLocation=\"urn:ietf:params:xml:ns:epp-1.0 "
    "epp-1.0.xsd\">"
    "<response>"
    "<result code='1000'>"
    "<msg";
  
  string result_lang = contact_transfer_rsp->get_result_lang();
  if (result_lang != "en") {
    response += " lang='" + result_lang + "'";
  }
  
  response +=
    ">" + r_it->second.msg + "</msg>"
    "</result>"
    "<resData>"
    "<contact:trnData "
    "xmlns:contact=\"urn:ietf:params:xml:ns:contact-1.0\" "
    "xsi:schemaLocation=\"urn:ietf:params:xml:ns:contact-1.0 "
    "contact-1.0.xsd\">"
    "<contact:id>" + contact_transfer_rsp->get_id() + "</contact:id>"
    "<contact:trStatus>" + contact_transfer_rsp->get_trStatus() + 
    "</contact:trStatus>"
    "<contact:reID>" + contact_transfer_rsp->get_reID() + "</contact:reID>"
    "<contact:reDate>" + contact_transfer_rsp->get_reDate() + 
    "</contact:reDate>"
    "<contact:acID>" + contact_transfer_rsp->get_acID() + "</contact:acID>"
    "<contact:acDate>" + contact_transfer_rsp->get_acDate() + 
    "</contact:acDate>"
    "</contact:trnData>"
    "</resData>"
    "<trID>"
    "<clTRID>" + contact_transfer_rsp->get_clTRID() + "</clTRID>"
    "<svTRID>" + contact_transfer_rsp->get_svTRID() + "</svTRID>"
    "</trID></response></epp>";

  CPPUNIT_ASSERT_EQUAL(expected, response);
  
  /* Reset Test */
  contact_transfer_rsp->reset();
  
  CPPUNIT_ASSERT_EQUAL((string) "", contact_transfer_rsp->get_id());
  CPPUNIT_ASSERT_EQUAL((string) "", contact_transfer_rsp->get_trStatus());
  CPPUNIT_ASSERT_EQUAL((string) "", contact_transfer_rsp->get_reID());
  CPPUNIT_ASSERT_EQUAL((string) "", contact_transfer_rsp->get_reDate());
  CPPUNIT_ASSERT_EQUAL((string) "", contact_transfer_rsp->get_acID());
  CPPUNIT_ASSERT_EQUAL((string) "", contact_transfer_rsp->get_acDate());
}

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

#include <memory>
#include <string>

#include "libepp_nicbr.H"

#include "DomainTransferTest.H"
#include "DomainTransfer.H"
#include "FileUtil.H"
#include "IoException.H"
#include "XmlException.H"

using std::auto_ptr;

#include <iostream>
using namespace std;

LIBEPP_NICBR_NS_USE

CPPUNIT_TEST_SUITE_REGISTRATION(DomainTransferTest);

DomainTransferTest::DomainTransferTest() {}

DomainTransferTest::~DomainTransferTest() {}

void DomainTransferTest::setUp() {}

void DomainTransferTest::tearDown() {}

void DomainTransferTest::set_xml_template_test()
{
  string to_be_parsed =
    "<command>"
      "<transfer op='query'>"
        "<domain:transfer "
          "xmlns:domain='urn:ietf:params:xml:ns:domain-1.0' "
          "xsi:schemaLocation='urn:ietf:params:xml:ns:domain-1.0 "
          "domain-1.0.xsd'>"
          "<domain:name>$(name)$</domain:name>"
          "$(auth_info)$"
        "</domain:transfer>"
      "</transfer>"
    "$(clTRID)$"
    "</command>";

  DomainTransfer domain_transfer;
  DomainTransferCmd* domain_transfer_cmd = domain_transfer.get_command();
  domain_transfer_cmd->set_name("EmmaWatsonIsCharming.com");

  AuthInfo auth;
  auth.set_roid("SH8013-REP");
  auth.set_pw("abc123");
  domain_transfer_cmd->set_authInfo(auth);

  domain_transfer.get_command()->set_clTRID("ABC-12345");
  domain_transfer.set_xml_template(to_be_parsed);

  string expected =
    "<command>"
      "<transfer op='query'>"
        "<domain:transfer "
          "xmlns:domain='urn:ietf:params:xml:ns:domain-1.0' "
          "xsi:schemaLocation='urn:ietf:params:xml:ns:domain-1.0 "
          "domain-1.0.xsd'>"
          "<domain:name>EmmaWatsonIsCharming.com</domain:name>"
          "<domain:authInfo>"
            "<domain:pw roid='SH8013-REP'>abc123</domain:pw>"
          "</domain:authInfo>"
        "</domain:transfer>"
        "</transfer>"
      "<clTRID>ABC-12345</clTRID>"
    "</command>";

  CPPUNIT_ASSERT_EQUAL(expected, domain_transfer.get_xml());

  // tests reset method
  domain_transfer_cmd = domain_transfer.get_command();
  domain_transfer_cmd->reset();

  CPPUNIT_ASSERT(domain_transfer_cmd->get_name() == "");
  CPPUNIT_ASSERT(domain_transfer_cmd->get_authInfo().get_pw() == "");
  CPPUNIT_ASSERT(domain_transfer_cmd->get_authInfo().get_roid() == "");

  // parent attribute
  CPPUNIT_ASSERT(domain_transfer_cmd->get_clTRID() == "");
}

void DomainTransferTest::command_test()
{
  DomainTransfer domain_transfer;
  DomainTransferCmd *domain_transfer_cmd = domain_transfer.get_command();

  domain_transfer_cmd->set_name("EmmaWatsonIsCharming.com");

  AuthInfo auth;
  auth.set_roid("SH8013-REP");
  auth.set_pw("abc123");
  domain_transfer_cmd->set_authInfo(auth);

  bool exception_caught = false;
  try {
    string xml_template = 
      FileUtil::read_file("../docs/templates/domain_transfer.xml");

    domain_transfer.get_command()->set_clTRID("ABC-12345");
    domain_transfer.set_xml_template(xml_template);

    DomParser parser;
    parser.enable_validation("../docs/schemas");
    parser.parse_command(domain_transfer.get_xml());
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

void DomainTransferTest::response_test()
{
  string expected =
    "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
    "<epp xmlns=\"urn:ietf:params:xml:ns:epp-1.0\" "
    "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
    "xsi:schemaLocation=\"urn:ietf:params:xml:ns:epp-1.0 "
    "epp-1.0.xsd\">"
    "<response>"
    "<result code=\"1000\">"
    "<msg>Command completed successfully</msg>"
    "</result>"
    "<resData>"
    "<domain:trnData "
    "xmlns:domain=\"urn:ietf:params:xml:ns:domain-1.0\" "
    "xsi:schemaLocation=\"urn:ietf:params:xml:ns:domain-1.0 "
    "domain-1.0.xsd\">"
    "<domain:name>example.com</domain:name>"
    "<domain:trStatus>pending</domain:trStatus>"
    "<domain:reID>ClientX</domain:reID>"
    "<domain:reDate>2000-06-08T22:00:00.0Z</domain:reDate>"
    "<domain:acID>ClientY</domain:acID>"
    "<domain:acDate>2000-06-13T22:00:00.0Z</domain:acDate>"
    "<domain:exDate>2002-09-08T22:00:00.0Z</domain:exDate>"
    "</domain:trnData>"
    "</resData>"
    "<trID>"
    "<clTRID>ABC-12345</clTRID>"
    "<svTRID>54321-XYZ</svTRID>"
    "</trID>"
    "</response>"
    "</epp>";

  DomParser parser;
  parser.enable_validation("../docs/schemas");

  DomainTransfer domain_transfer;
  CPPUNIT_ASSERT_NO_THROW(domain_transfer.set_response(expected, &parser));

  DomainTransferRsp* domain_transfer_rsp = domain_transfer.get_response();

  CPPUNIT_ASSERT(domain_transfer_rsp != 0);
  string result_code = "1000";

  map <Response::ResultCode, Response::ResultInfo> results;
  map <Response::ResultCode, Response::ResultInfo>::const_iterator r_it;
  results = domain_transfer_rsp->get_result_list();
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
    "<result code=\"" + result_code + "\">"
    "<msg";
  
  string result_lang = domain_transfer_rsp->get_result_lang();
  if (result_lang != "en") {
    response += " lang='" + result_lang + "'";
  }
  
  response +=
    ">" + r_it->second.msg + "</msg>"
    "</result>"
    "<resData>"
    "<domain:trnData "
    "xmlns:domain=\"urn:ietf:params:xml:ns:domain-1.0\" "
    "xsi:schemaLocation=\"urn:ietf:params:xml:ns:domain-1.0 "
    "domain-1.0.xsd\">"
    "<domain:name>" + domain_transfer_rsp->get_name() + "</domain:name>"
    "<domain:trStatus>" + domain_transfer_rsp->get_trStatus() + 
    "</domain:trStatus>"
    "<domain:reID>" + domain_transfer_rsp->get_reID() + "</domain:reID>"
    "<domain:reDate>" + domain_transfer_rsp->get_reDate() + 
    "</domain:reDate>"
    "<domain:acID>" + domain_transfer_rsp->get_acID() + "</domain:acID>"
    "<domain:acDate>" + domain_transfer_rsp->get_acDate() + 
    "</domain:acDate>"
    "<domain:exDate>" + domain_transfer_rsp->get_exDate() + 
    "</domain:exDate>"
    "</domain:trnData>"
    "</resData>"
    "<trID>"
    "<clTRID>" + domain_transfer_rsp->get_clTRID() + "</clTRID>"
    "<svTRID>" + domain_transfer_rsp->get_svTRID() + "</svTRID>"
    "</trID></response></epp>";

  CPPUNIT_ASSERT_EQUAL(expected, response);
  
  /* Reset Test */
  domain_transfer_rsp->reset();
  
  CPPUNIT_ASSERT_EQUAL((string) "", domain_transfer_rsp->get_name());
  CPPUNIT_ASSERT_EQUAL((string) "", domain_transfer_rsp->get_trStatus());
  CPPUNIT_ASSERT_EQUAL((string) "", domain_transfer_rsp->get_reID());
  CPPUNIT_ASSERT_EQUAL((string) "", domain_transfer_rsp->get_reDate());
  CPPUNIT_ASSERT_EQUAL((string) "", domain_transfer_rsp->get_acID());
  CPPUNIT_ASSERT_EQUAL((string) "", domain_transfer_rsp->get_acDate());
  CPPUNIT_ASSERT_EQUAL((string) "", domain_transfer_rsp->get_exDate());
}

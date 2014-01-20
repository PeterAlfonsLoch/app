/* ${copyri%ght}$ */
/* $Id$ */
/** @file ContactTransferTest.H
 *  @brief Contact Transfer Action Test
 */

#ifndef __CONTACT_TRANSFER_TEST_H__
#define __CONTACT_TRANSFER_TEST_H__

#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

/// Contact Info Test Class
class ContactTransferTest : public CppUnit::TestFixture  
{
public:
  /// Constructor
  ContactTransferTest();

  /// Destructor
  ~ContactTransferTest();

  /// Allocate resources
  void setUp();

  /// Release resources
  void tearDown();

  /// Test set_XML_template method
  void set_xml_template_test();

  // Tests a contact info command
  void command_test();

  // Tests a contact info response
  void response_test();
  
private:

  CPPUNIT_TEST_SUITE(ContactTransferTest);
  CPPUNIT_TEST(set_xml_template_test);
  CPPUNIT_TEST(command_test);
  CPPUNIT_TEST(response_test);
  CPPUNIT_TEST_SUITE_END();
};

#endif // __CONTACT_TRANSFER_TEST_H__

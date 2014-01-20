/* 
 * libepp-nicbr 1.10 on 2010-14-10 2009 Registro.br
 * 
 */
/* $Id: DomErrorHandler.H 1044 2009-10-19 14:39:10Z koji $ */
/** @file DomErrorHandler.H
 *  @brief EPP DomErrorHandler Class
 */
#pragma once


namespace libepp
{

   /// EPP DomErrorHandler Class
   class DomErrorHandler : public ErrorHandler
   {
   public:

     /// Default Constructor
     DomErrorHandler() {}

     /// Default Destructor
     ~DomErrorHandler() {}

     /// Handles parsing warning
     /**
        @param exception The warning info encapsulated in a SAX parse exception. 
      */
     void warning(const string & exception);

     /// Handles parsing errors
     /**
        @param exception The error info encapsulated in a SAX parse exception. 
      */
     void error(const string & exception);

     /// Handles parsing fatal errors
     /**
        @param exception The error info encapsulated in a SAX parse exception. 
      */
     void fatalError(const string & exception);

     /// Reset errors
     void resetErrors();
   };

} // namespace libepp


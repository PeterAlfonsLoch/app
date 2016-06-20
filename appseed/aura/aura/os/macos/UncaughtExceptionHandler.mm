//
//  UncaughtExceptionHandler.m
//  UncaughtExceptions
//
//  Created by Matt Gallagher on 2010/05/25.
//  Copyright 2010 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file, free of charge, in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//


#import "UncaughtExceptionHandler.h"
#include "macos_ns_exception.h"
#include <libkern/OSAtomic.h>
#include <execinfo.h>

volatile int32_t UncaughtExceptionCount = 0;
const int32_t UncaughtExceptionMaximum = 10;

//extern void translator_signal_handler(int signal);
//void SignalHandler(int signal)
//{
//   int32_t exceptionCount = OSAtomicIncrement32(&UncaughtExceptionCount);
//   if (exceptionCount > UncaughtExceptionMaximum)
//   {
//      return;
//   }
//   translator_signal_handler(signal);
//}


//NSString * const UncaughtExceptionHandlerSignalExceptionName = @"UncaughtExceptionHandlerSignalExceptionName";
//NSString * const UncaughtExceptionHandlerSignalKey = @"UncaughtExceptionHandlerSignalKey";
//NSString * const UncaughtExceptionHandlerAddressesKey = @"UncaughtExceptionHandlerAddressesKey";

//volatile int32_t UncaughtExceptionCount = 0;
//const int32_t UncaughtExceptionMaximum = 10;

//const NSInteger UncaughtExceptionHandlerSkipAddressCount = 4;
//const NSInteger UncaughtExceptionHandlerReportAddressCount = 5;




void HandleException(NSException *exception)
{


   throw ns_exception();

}


void NullHandleException(NSException *exception)
{
    
    
}


void InstallUncaughtExceptionHandler()
{
    
	NSSetUncaughtExceptionHandler(&HandleException);
//   signal(SIGABRT, SignalHandler);
//   signal(SIGILL, SignalHandler);
//   signal(SIGSEGV, SignalHandler);
//   signal(SIGFPE, SignalHandler);
//   signal(SIGBUS, SignalHandler);
//   signal(SIGPIPE, SignalHandler);
}



void InstallNullExceptionHandler()
{
    
//	NSSetUncaughtExceptionHandler(&NullHandleException);
    
}




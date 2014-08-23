//////////////////////////////////////////////////////////////////////////////
// microtimer.cpp
// =========
// High Resolution microtimer.
// This microtimer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2006-01-13
//
// Copyright (ca) 2003 Song Ho Ahn
//////////////////////////////////////////////////////////////////////////////
#include "framework.h"


namespace axis
{

   ///////////////////////////////////////////////////////////////////////////////
   // constructor
   ///////////////////////////////////////////////////////////////////////////////
   microtimer::microtimer()
   {
#ifdef WIN32
      QueryPerformanceFrequency(&frequency);
      startCount.QuadPart = 0;
      endCount.QuadPart = 0;
#else
      startCount.tv_sec = startCount.tv_usec = 0;
      endCount.tv_sec = endCount.tv_usec = 0;
#endif

      stopped = 0;
      startTimeInMicroSec = 0;
      endTimeInMicroSec = 0;
   }



   ///////////////////////////////////////////////////////////////////////////////
   // distructor
   ///////////////////////////////////////////////////////////////////////////////
   microtimer::~microtimer()
   {
   }



   ///////////////////////////////////////////////////////////////////////////////
   // start microtimer.
   // startCount will be set at this point.
   ///////////////////////////////////////////////////////////////////////////////
   void microtimer::start()
   {
      stopped = 0; // reset stop flag
#ifdef WIN32
      QueryPerformanceCounter(&startCount);
#else
      gettimeofday(&startCount, NULL);
#endif
   }



   ///////////////////////////////////////////////////////////////////////////////
   // stop the microtimer.
   // endCount will be set at this point.
   ///////////////////////////////////////////////////////////////////////////////
   void microtimer::stop()
   {
      stopped = 1; // set microtimer stopped flag

#ifdef WIN32
      QueryPerformanceCounter(&endCount);
#else
      gettimeofday(&endCount, NULL);
#endif
   }



   ///////////////////////////////////////////////////////////////////////////////
   // compute elapsed time in micro-second resolution.
   // other getElapsedTime will call this first, then convert to correspond resolution.
   ///////////////////////////////////////////////////////////////////////////////
   double microtimer::getElapsedTimeInMicroSec()
   {
#ifdef WIN32
      if (!stopped)
         QueryPerformanceCounter(&endCount);

      startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
      endTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
#else
      if (!stopped)
         gettimeofday(&endCount, NULL);

      startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
      endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
#endif

      return endTimeInMicroSec - startTimeInMicroSec;
   }



   ///////////////////////////////////////////////////////////////////////////////
   // divide elapsedTimeInMicroSec by 1000
   ///////////////////////////////////////////////////////////////////////////////
   double microtimer::getElapsedTimeInMilliSec()
   {
      return this->getElapsedTimeInMicroSec() * 0.001;
   }



   ///////////////////////////////////////////////////////////////////////////////
   // divide elapsedTimeInMicroSec by 1000000
   ///////////////////////////////////////////////////////////////////////////////
   double microtimer::getElapsedTimeInSec()
   {
      return this->getElapsedTimeInMicroSec() * 0.000001;
   }


   ///////////////////////////////////////////////////////////////////////////////
   // compute time in micro-second resolution.
   // other getElapsedTime will call this first, then convert to correspond resolution.
   ///////////////////////////////////////////////////////////////////////////////
   double microtimer::getTimeInMicroSec()
   {

      double dTimeInMicroSec;

#ifdef WIN32

      QueryPerformanceCounter(&endCount);

      dTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);

#else

      gettimeofday(&endCount, NULL);

      dTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;

#endif

      return endTimeInMicroSec;

   }



   ///////////////////////////////////////////////////////////////////////////////
   // divide TimeInMicroSec by 1000
   ///////////////////////////////////////////////////////////////////////////////
   double microtimer::getTimeInMilliSec()
   {
      return this->getTimeInMicroSec() * 0.001;
   }



   ///////////////////////////////////////////////////////////////////////////////
   // divide TimeInMicroSec by 1000000
   ///////////////////////////////////////////////////////////////////////////////
   double microtimer::getTimeInSec()
   {
      return this->getTimeInMicroSec() * 0.000001;
   }



   ///////////////////////////////////////////////////////////////////////////////
   // same as getElapsedTimeInSec()
   ///////////////////////////////////////////////////////////////////////////////
   double microtimer::getElapsedTime()
   {
      return this->getElapsedTimeInSec();
   }


} // namespace core




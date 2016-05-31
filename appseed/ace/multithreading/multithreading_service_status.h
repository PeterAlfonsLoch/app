//*****************************************************************************
//
//      Class:          service_status
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides default initialization for SERVICE_STATUS.
//
//*****************************************************************************
#pragma once


#ifdef WINDOWSEX


class CLASS_DECL_AURA service_status : public SERVICE_STATUS
{
public:

   service_status()
   {
      ASSERT(sizeof (*this) == sizeof (SERVICE_STATUS));

      ::ZeroMemory(this,
         sizeof (SERVICE_STATUS));
   }
};


#else


class CLASS_DECL_AURA service_status
{
public:


   uint32_t       dwServiceType;
   uint32_t       dwServiceState;


   service_status()
   {

      ASSERT(sizeof(*this) == sizeof(service_status));

      memset(this, 0, sizeof(service_status));

   }

};


#endif




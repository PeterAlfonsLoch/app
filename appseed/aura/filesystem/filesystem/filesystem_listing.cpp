#include "framework.h"


namespace file
{


   listing::listing(listing_provider * pprovider)
   {

      m_pprovider = pprovider;

   }


   listing::~listing()
   {

   }


   listing & listing::ls()
   {

      return m_pprovider->perform_file_listing(*this);

   }


} // namespace file






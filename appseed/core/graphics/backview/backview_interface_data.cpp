#include "framework.h"


namespace backview
{

   InterfaceData::InterfaceData()
   {

   }


   InterfaceData::~InterfaceData()
   {

   }


   void InterfaceData::signalize(EInterfaceData edata)
   {

      m_einterfacedataflags.signalize(edata);

   }


   bool InterfaceData::is_signalized(EInterfaceData edata)
   {

      return m_einterfacedataflags.is_signalized(edata);

   }


} // namespace backview

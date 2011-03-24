#pragma once

namespace tarsila
{

class area
{
public:
   area();
   ::CCriticalSection m_cs;
   CDC m_dcSource;
   dib m_dib1;
   dib m_dib2;
};

} // namespace tarsila
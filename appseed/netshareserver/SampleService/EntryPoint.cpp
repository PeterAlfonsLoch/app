#include "stdafx.h"
#include "SampleService.h"

int main()
{
    try
    {
        Kerr::CommandLineParser args;

#ifdef DEBUG
        if (args.IsFlagPresent(L"debugbreak"))
        {
            ::DebugBreak();
        }
 
        if (args.IsFlagPresent(L"console"))
        {
            SampleService service;
            service.Start(0);
            
            std::wcout << L"Press the Enter key to stop the service." << std::endl;
            std::wcin.get();

            service.Stop(0);
        }
        else
#endif
        if (args.IsFlagPresent(L"service"))
        {
            SampleService service;
            Kerr::ServiceBase::Run(service);
        }
    }
    catch (const CAtlException& e)
    {
        std::wcout.setf(std::ios_base::hex, 
                        std::ios_base::basefield);

        std::wcout << L"Error: 0x"
                   << e.m_hr
                   << std::endl;
    }
}

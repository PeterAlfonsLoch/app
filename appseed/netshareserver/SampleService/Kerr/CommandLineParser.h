//*****************************************************************************
//
//      Class:          CommandLineParser
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Parses the process command line and makes the flags
//                      readily available.
//
//*****************************************************************************

#pragma once

#include <map>

namespace Kerr
{
    class CommandLineParser
    {
    public:

        CommandLineParser();

        const std::wstring GetFlag(const std::wstring& name) const;
        bool IsFlagPresent(const std::wstring& name) const;

    private:

        typedef std::map<std::wstring, std::wstring> Map;
        Map m_map;
    };
}

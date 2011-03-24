//*****************************************************************************
//
//      Class:          CommandLineParser
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Parses the process command line and makes the flags
//                      readily available.
//
//*****************************************************************************

#include "stdafx.h"
#include "CommandLineParser.h"
#include "LocalMemory.h"
#include "HelperFunctions.h"

//*****************************************************************************
//
//      Name:           CommandLineParser
//      Description:    The default constructor - loads and parses the command
//                      line.
//
//*****************************************************************************
Kerr::CommandLineParser::CommandLineParser()
{
    //
    // Loads the command line arguments.
    //

    int argumentCount = 0;
    
    LocalMemory<PWSTR> commandLineArgs(::CommandLineToArgvW(::GetCommandLine(),
                                                            &argumentCount));

    if (0 == commandLineArgs.m_pBuffer)
    {
        AtlThrowLastWin32();
    }

    //
    // Builds a regular expression to select the flag's name and value.
    //

    CAtlRegExp<> regex;

    Parse(regex,
          L"^/{[^=]*}(={.*})?");

    //
    // For each flag, match the regural expression and add the 
    // matching name and value to the map.
    //

    for (int i = 0; i < argumentCount; ++i)
    {
        PCWSTR argument = commandLineArgs.m_pBuffer[i];
        CAtlREMatchContext<> match;

        if (regex.Match(argument,
                        &match))
        {
            ATLASSERT(2 == match.m_uNumGroups);

            std::wstring name = GetMatchGroupValue(match,
                                                   0);

            std::wstring value = GetMatchGroupValue(match,
                                                    1);

            m_map[ToLower(name)] = ToLower(value);
        }
    }
}

//*****************************************************************************
//
//      Name:           GetFlag
//      Description:    Get the value of the flag. If the flag is not present, 
//                      an empty string is returned.
//
//*****************************************************************************
const std::wstring Kerr::CommandLineParser::GetFlag(const std::wstring& name) const
{
    std::wstring value;
    Map::const_iterator iter = m_map.find(ToLower(name));

    if (iter != m_map.end())
    {
        value = iter->second;
    }

    return value;
}

//*****************************************************************************
//
//      Name:           IsFlagPresent
//      Description:    Determines whether a flag is present.
//
//*****************************************************************************
bool Kerr::CommandLineParser::IsFlagPresent(const std::wstring& name) const
{
    Map::const_iterator iter = m_map.find(ToLower(name));
    return iter != m_map.end();
}

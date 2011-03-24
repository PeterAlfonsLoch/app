//*****************************************************************************
//
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Helper functions used by this project.
//
//*****************************************************************************

#include "stdafx.h"
#include "HelperFunctions.h"

#include <algorithm>

//*****************************************************************************
//
//      Name:           ToLower
//      Description:    Converts the string to lower case.
//
//*****************************************************************************
const std::wstring Kerr::ToLower(const std::wstring& rhs)
{
    std::wstring lhs;
    lhs.resize(rhs.size());

    std::transform(rhs.begin(),
                   rhs.end(),
                   lhs.begin(),
                   ::towlower);

    return lhs;
}

//*****************************************************************************
//
//      Name:           GetMatchGroupValue
//      Description:    Returns the value of the matching group.
//
//*****************************************************************************
const std::wstring Kerr::GetMatchGroupValue(CAtlREMatchContext<>& match,
                                            int index)
{
    PCWSTR start = 0;
    PCWSTR end = 0;

    match.GetMatch(index,
                   &start,
                   &end);

    return std::wstring(start, 
                        end - start);
}

//*****************************************************************************
//
//      Name:           Parse
//      Description:    Handles the error codes returned by the 
//                      CAtlRegExp<>::Parse method and throws an exception on
//                      failure.
//
//*****************************************************************************
void Kerr::Parse(CAtlRegExp<>& regex,
                 const std::wstring& expression)
{
    REParseError result = regex.Parse(expression.c_str());

    if (REPARSE_ERROR_OK != result)
    {
        if (REPARSE_ERROR_OUTOFMEMORY == result)
        {
            AtlThrow(E_OUTOFMEMORY);
        }
        else
        {
            AtlThrow(E_UNEXPECTED);
        }
    }
}

//*****************************************************************************
//
//      Name:           Win32FromHResult
//      Description:    Converts and HRESULT to a Win32 error code. This 
//                      assumes that the HRESULT was actually a Win32 error code
//                      to begin with.
//
//*****************************************************************************
DWORD Kerr::Win32FromHResult(HRESULT value)
{
    ATLASSERT(FACILITY_WIN32 == HRESULT_FACILITY(value));
    return value & ~0x80070000;
}


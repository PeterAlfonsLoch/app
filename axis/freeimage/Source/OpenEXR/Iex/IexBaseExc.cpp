#include "Imf.h"



//---------------------------------------------------------------------
//
//	Constructors and destructors for our exception base class.
//
//---------------------------------------------------------------------

//#include "IexBaseExc.h"

namespace Iex {
namespace {


StackTracer currentStackTracer = 0;


} // namespace


void	
setStackTracer (StackTracer stackTracer)
{
    currentStackTracer = stackTracer;
}


StackTracer
stackTracer ()
{
    return currentStackTracer;
}


BaseExc::BaseExc (const char* s) throw () :
    std::string (s? s: ""),
    _stackTrace (currentStackTracer? currentStackTracer(): "")
{
    // empty
}


BaseExc::BaseExc (const std::string &s) throw () :
    std::string (s),
    _stackTrace (currentStackTracer? currentStackTracer(): "")
{
    // empty
}


BaseExc::BaseExc (std::stringstream &s) throw () :
    std::string (s.str()),
    _stackTrace (currentStackTracer? currentStackTracer(): "")
{
    // empty
}


BaseExc::BaseExc (const BaseExc &be) throw () :
    std::string (be),
    _stackTrace (be._stackTrace)
{
    // empty
}


BaseExc::~BaseExc () throw ()
{
    // empty
}


const char *
BaseExc::what () const throw ()
{
    return c_str();
}


BaseExc &
BaseExc::assign (std::stringstream &s)
{
    std::string::assign (s.str());
    return *this;
}

BaseExc &
BaseExc::append (std::stringstream &s)
{
    std::string::append (s.str());
    return *this;
}


} // namespace Iex

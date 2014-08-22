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
    _stackTrace (currentStackTracer? currentStackTracer(): "")
{
       m_strMessage = s;
}


BaseExc::BaseExc (const std::string &s) throw () :
    _stackTrace (currentStackTracer? currentStackTracer(): "")
{
   m_strMessage = s;
}


BaseExc::BaseExc (std::stringstream &s) throw () :
    _stackTrace (currentStackTracer? currentStackTracer(): "")
{
       m_strMessage = s.str();
}


BaseExc::BaseExc (const BaseExc &be) throw () :
    _stackTrace (be._stackTrace)
{
   m_strMessage = be.m_strMessage;
}


BaseExc::~BaseExc () throw ()
{
    // empty
}


const char *
BaseExc::what () const throw ()
{
    return m_strMessage;
}


BaseExc &
BaseExc::assign (std::stringstream &s)
{
    m_strMessage = s.str();
    return *this;
}

BaseExc &
BaseExc::append (std::stringstream &s)
{
    m_strMessage += s.str();
    return *this;
}


} // namespace Iex

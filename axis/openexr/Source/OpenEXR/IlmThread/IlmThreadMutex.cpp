#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class Mutex, class Lock -- dummy implementation
//	for platforms that do not support threading
//
//-----------------------------------------------------------------------------

#include "IlmBaseConfig.h"

//#if !defined (_WIN32) && !(_WIN64) && !(HAVE_PTHREAD)

//#include "Iex.h"

namespace IlmThread {


Mutex::Mutex () {}
Mutex::~Mutex () {}
void Mutex::lock () const {}
void Mutex::unlock () const {}


} // namespace IlmThread

//#endif

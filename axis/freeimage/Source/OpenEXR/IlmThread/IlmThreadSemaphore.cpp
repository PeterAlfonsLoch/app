#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	class Semaphore -- dummy implementation for
//	for platforms that do not support threading
//
//-----------------------------------------------------------------------------

#include "IlmBaseConfig.h"

//#if !defined (_WIN32) && !(_WIN64) && !(HAVE_PTHREAD)
//#include "IlmThreadSemaphore.h"

namespace IlmThread {


Semaphore::Semaphore (unsigned int value) {}
Semaphore::~Semaphore () {}
void Semaphore::wait () {}
bool Semaphore::tryWait () {return true;}
void Semaphore::post () {}
int Semaphore::value () const {return 0;}


} // namespace IlmThread

//#endif

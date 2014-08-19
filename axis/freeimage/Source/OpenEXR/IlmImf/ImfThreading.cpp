#include "Imf.h"

//-----------------------------------------------------------------------------
//
//	Threading support for the IlmImf library
//
//-----------------------------------------------------------------------------

//#include "IlmThreadPool.h"

namespace Imf {


int
globalThreadCount ()
{
    return IlmThread::ThreadPool::globalThreadPool().numThreads();
}


void
setGlobalThreadCount (int count)
{
    IlmThread::ThreadPool::globalThreadPool().setNumThreads (count);
}


} // namespace Imf

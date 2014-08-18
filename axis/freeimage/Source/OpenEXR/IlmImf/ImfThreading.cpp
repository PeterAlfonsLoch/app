#include "Imf.h"

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

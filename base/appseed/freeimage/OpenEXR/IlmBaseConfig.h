#include "base/base/base/base.h"


//
// Define and set to 1 if the target system has POSIX thread support
// and you want OpenEXR to use it for multithreaded file I/O.
//

#if defined(__APPLE__) || defined(ANDROID) || defined(LINUX)
#define HAVE_PTHREAD 1
#else
#undef HAVE_PTHREAD		// currently disabled in FreeImage
#endif

//
// Define and set to 1 if the target system supports POSIX semaphores
// and you want OpenEXR to use them; otherwise, OpenEXR will use its
// own semaphore implementation.
//

#if defined(__APPLE__) || defined(ANDROID)
#define HAVE_POSIX_SEMAPHORES 1
#else
#undef HAVE_POSIX_SEMAPHORES
#endif
//
// Define and set to 1 if the target system is a Darwin-based system
// (e.g., OS X).
//

#if defined(__APPLE__)
#define HAVE_DARWIN 1
#else
#undef HAVE_DARWIN
#endif

//
// Define and set to 1 if the target system supports a proc filesystem
// compatible with the Linux kernel's proc filesystem.  Note that this
// is only used by a program in the IlmImfTest test suite, it's not
// used by any OpenEXR library or application code.
//

#undef HAVE_LINUX_PROCFS

//
// Define and set to 1 if the target system includes the NVIDIA Cg
// runtime.  The exrdisplay program will use a fragment shader to
// accelerate the display of OpenEXR images.
//

#undef HAVE_FRAGMENT_SHADERS

//
// Define and set to 1 if the target system has a complete <iomanip>
// implementation, specifically if it supports the std::right
// formatter.
//

#undef HAVE_COMPLETE_IOMANIP

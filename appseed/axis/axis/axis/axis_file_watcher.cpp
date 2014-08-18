/**
	Copyright (c) 2009 James Wynn (james@jameswynn.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/
#include "framework.h"


#if defined(WINDOWSEX)
#include "base/os/windows/windows_file_watcher.h"
#elif defined(APPLEOS)
#include "base/os/macos/macos_file_watcher.h"
#elif defined(LINUX)
#include "base/os/linux/linux_file_watcher.h"
#elif defined(ANDROID)
#include "base/os/android/android_file_watcher.h"
#elif defined(METROWIN)
#include "base/os/metrowin/metrowin_file_watcher.h"
#endif


namespace file_watcher
{


	file_watcher::file_watcher()
	{

      m_bUpdating = false;

		m_pimpl = new os_file_watcher();

	}


	file_watcher::~file_watcher()
	{

      if(m_pimpl != NULL)
      {

         delete m_pimpl;

         m_pimpl = NULL;

      }

	}


	id file_watcher::add_watch(const char * directory, file_watch_listener * pwatcher, bool bRecursive)
	{

      return m_pimpl->add_watch(directory, pwatcher, bRecursive);

	}

	void file_watcher::remove_watch(const char * directory)
	{

		m_pimpl->remove_watch(directory);

	}

	void file_watcher::remove_watch(id id)
	{

		m_pimpl->remove_watch(id);

	}
   void file_watcher::update()
	{

      keep_true updating(m_bUpdating);

		m_pimpl->update();

	}


} //namespace file_watcher






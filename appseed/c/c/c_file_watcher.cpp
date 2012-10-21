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


#if FILEWATCHER_PLATFORM == FILEWATCHER_PLATFORM_WIN32
#include "c/windows/c_os_file_watcher.h"
#elif FILEWATCHER_PLATFORM == FILEWATCHER_PLATFORM_KQUEUE
#include "c/macos/c_os_file_watcher.h"
#elif FILEWATCHER_PLATFORM == FILEWATCHER_PLATFORM_INOTIFY
#include "c/linux/c_os_file_watcher.h"
#elif FILEWATCHER_PLATFORM == FILEWATCHER_PLATFORM_MERDWIN
#include "c/merdes_windows/c_os_file_watcher.h"
#endif

namespace file_watcher
{


	file_watcher::file_watcher()
	{
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

	id file_watcher::add_watch(const char * directory, file_watch_listener* pwatcher)
	{
		return m_pimpl->add_watch(directory, pwatcher);
	}

	id_array file_watcher::radd_watch(const char * directory, file_watch_listener* pwatcher)
	{
      id_array ida;
      stra_dup stra;
      stra.add(directory);
      dir::rls_dir(stra, directory);
		for(index i = 0; i < ida.get_count(); i++)
      {
         ida.add(m_pimpl->add_watch(directory, pwatcher));
      }
      return ida;
	}


	void file_watcher::remove_watch(const char * directory)
	{
		m_pimpl->remove_watch(directory);
	}

	void file_watcher::remove_watch(id watchid)
	{
		m_pimpl->remove_watch(watchid);
	}

	void file_watcher::update()
	{
		m_pimpl->update();
	}

   
} //namespace file_watcher



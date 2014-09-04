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

	James Wynn james@jameswynn.com
*/
#include "framework.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/inotify.h>
#include <unistd.h>

#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*1024)

namespace file_watcher
{

	struct watch_struct_item
	{
		id m_id;
		string m_strDirName;
	};


	struct watch_struct :
      public watch_struct_item
	{
	   bool m_bRecursive;
		file_watch_listener* m_plistener;
	   ::array < watch_struct_item > m_itema;
	};


	//--------
	os_file_watcher::os_file_watcher()
	{
		mFD = inotify_init();
		if (mFD < 0)
			fprintf (stderr, "Error: %s\n", strerror(errno));

		mTimeOut.tv_sec = 0;
		mTimeOut.tv_usec = 0;

		FD_ZERO(&mDescriptorSet);
	}

	//--------
	os_file_watcher::~os_file_watcher()
	{
		WatchMap::pair * ppair = m_watchmap.PGetFirstAssoc();
		for(; ppair != NULL; ppair = m_watchmap.PGetNextAssoc(ppair))
		{
			delete ppair->m_element2;
		}
		m_watchmap.remove_all();
	}

	//--------
	id os_file_watcher::add_watch(const string & directory,  file_watch_listener * pwatcher, bool bRecursive)
	{
		int32_t wd = inotify_add_watch (mFD, directory, IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);
		if (wd < 0)
		{
			if(errno == ENOENT)
				throw file_not_found_exception(directory);
			else
				throw exception(strerror(errno));

//			fprintf (stderr, "Error: %s\n", strerror(errno));
//			return -1;
		}

		watch_struct* pWatch = new watch_struct();
		pWatch->m_plistener = pwatcher;
		pWatch->m_id = wd;
		pWatch->m_strDirName = directory;
		if(bRecursive)
		{

         pWatch->m_bRecursive = true;

		   stringa stra;

		   dir::rls_dir(stra, directory);

		   for(index index = 0; index < stra.get_count(); index++)
		   {

		      int32_t inaw = inotify_add_watch (mFD, stra[index], IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);

            if(inaw < 0)
            {
               if(errno == ENOENT)
                  throw file_not_found_exception(directory);
               else
                  throw exception(strerror(errno));
            }

            watch_struct_item item;

            item.m_strDirName = stra[index];

            item.m_id = inaw;

            pWatch->m_itema.add(item);

		   }

		}
		else
		{
		   pWatch->m_bRecursive = false;
		}

		m_watchmap.set_at(wd, pWatch);

		return wd;
	}

	//--------
	void os_file_watcher::remove_watch(const string & directory)
	{
		WatchMap::pair * ppair = m_watchmap.PGetFirstAssoc();
		for(; ppair != NULL; ppair = m_watchmap.PGetNextAssoc(ppair))
		{
			if(directory == ppair->m_element2->m_strDirName)
			{
				remove_watch(ppair->m_element1);
				return;
			}
		}

	}

	//--------
	void os_file_watcher::remove_watch(id watchid)
	{
		WatchMap::pair * ppair = m_watchmap.PLookup(watchid);

		if(ppair == NULL)
			return;

		watch_struct* watch = ppair->m_element2;
		m_watchmap.remove_key(ppair->first);

		inotify_rm_watch(mFD, watchid);

		delete watch;
		watch = 0;
	}

	string os_file_watcher::watch_path(id id)
	{
		return m_watchmap[id]->m_strDirName;
	}

	//--------
	void os_file_watcher::update()
	{

		FD_SET(mFD, &mDescriptorSet);

		int32_t ret = select(mFD + 1, &mDescriptorSet, NULL, NULL, &mTimeOut);

		if(ret < 0)
		{
			perror("select");
		}
		else if(FD_ISSET(mFD, &mDescriptorSet))
		{

			ssize_t len, i = 0;
			char action[81+FILENAME_MAX] = {0};
			char buff[BUFF_SIZE] = {0};

			len = read (mFD, buff, BUFF_SIZE);

			file_watcher_impl::action a;

			while (i < len)
			{
				struct inotify_event *pevent = (struct inotify_event *)&buff[i];

				a.watch = m_watchmap[(id &)pevent->wd];
				a.filename = pevent->name;
				a.ulOsAction = pevent->mask;
				handle_action(&a);
				i += sizeof(struct inotify_event) + pevent->len;
			}

		}

	}

	//--------
	void os_file_watcher::handle_action(action * paction)
	{

	    if(!paction->watch)
	    return;

		if(!paction->watch->m_plistener)
			return;

		if(IN_CLOSE_WRITE & paction->ulOsAction)
		{
			paction->watch->m_plistener->handle_file_action(paction->watch->m_id, paction->watch->m_strDirName, paction->filename, action_modify);
		}

		if(IN_MOVED_TO & paction->ulOsAction || IN_CREATE & paction->ulOsAction)
		{
			paction->watch->m_plistener->handle_file_action(paction->watch->m_id, paction->watch->m_strDirName, paction->filename, action_add);
		}

		if(IN_MOVED_FROM & paction->ulOsAction || IN_DELETE & paction->ulOsAction)
		{
			paction->watch->m_plistener->handle_file_action(paction->watch->m_id, paction->watch->m_strDirName, paction->filename, action_delete);
		}

	}


} // namespace file_watcher



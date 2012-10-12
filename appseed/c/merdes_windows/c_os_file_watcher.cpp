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


namespace file_watcher
{
	/// Internal watch data
	struct watch_struct
	{
		OVERLAPPED mOverlapped;
		HANDLE mDirHandle;
		BYTE mBuffer[32 * 1024];
		LPARAM lParam;
		DWORD mNotifyFilter;
		bool mStopNow;
		file_watcher_impl* mFileWatcher;
		file_watch_listener* mFileWatchListener;
		vsstring m_strDirName;
		id mWatchid;
	};


	os_file_watcher::os_file_watcher()
		: m_idLast(0)
	{
	}

	os_file_watcher::~os_file_watcher()
	{
      watch_map::pair * ppair = m_watchmap.PGetFirstAssoc();
		for(; ppair != NULL; m_watchmap.PGetNextAssoc(ppair))
		{
			DestroyWatch(ppair->m_value);
		}
		m_watchmap.remove_all();
	}

	id os_file_watcher::addWatch(const char * directory, file_watch_listener* watcher)
	{
		id watchid = ++m_idLast;

		watch_struct* watch = CreateWatch(directory, FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_FILE_NAME);

		if(!watch)
			throw file_not_found_exception(directory);

		watch->mWatchid = watchid;
		watch->mFileWatcher = this;
		watch->mFileWatchListener = watcher;
		watch->m_strDirName = directory;
		strcpy(watch->m_strDirName, directory);

		m_watchmap.insert(std::make_pair(watchid, watch));

		return watchid;
	}

	void os_file_watcher::removeWatch(const String& directory)
	{
		watch_map::iterator iter = m_watchmap.begin();
		watch_map::iterator end = m_watchmap.end();
		for(; iter != end; ++iter)
		{
			if(directory == iter->second->m_strDirName)
			{
				removeWatch(iter->first);
				return;
			}
		}
	}

	void os_file_watcher::removeWatch(id watchid)
	{
		watch_map::iterator iter = m_watchmap.find(watchid);

		if(iter == m_watchmap.end())
			return;

		watch_struct* watch = iter->second;
		m_watchmap.erase(iter);

		DestroyWatch(watch);
	}

	void os_file_watcher::update()
	{
		MsgWaitForMultipleObjectsEx(0, NULL, 0, QS_ALLINPUT, MWMO_ALERTABLE);
	}

	void os_file_watcher::handleAction(watch_struct* watch, const String& filename, unsigned long action)
	{
		Action fwAction;

		switch(action)
		{
		case FILE_ACTION_RENAMED_NEW_NAME:
		case FILE_ACTION_ADDED:
			fwAction = Actions::Add;
			break;
		case FILE_ACTION_RENAMED_OLD_NAME:
		case FILE_ACTION_REMOVED:
			fwAction = Actions::Delete;
			break;
		case FILE_ACTION_MODIFIED:
			fwAction = Actions::Modified;
			break;
		};

		watch->mFileWatchListener->handleFileAction(watch->mWatchid, watch->m_strDirName, filename, fwAction);
	}

} // namespace file_watcher





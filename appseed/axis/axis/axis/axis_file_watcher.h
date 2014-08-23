/**
	Main header for the file_watcher class. Declares all implementation
	classes to reduce compilation overhead.

	@author James Wynn
	@date 4/15/2009

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

#pragma once


namespace file_watcher
{


	/// Type for a watch id
	typedef uint64_t id;
	typedef array < id > id_array;

	// forward declarations
	class file_watcher_impl;
	class file_watch_listener;

	/// Base exception class
	/// @class Exception
	class CLASS_DECL_AXIS exception
	{
	public:

      string    m_strMessage;
		exception(const char *  message) :
         m_strMessage(message)
		{
		}
      
	};

	/// Exception thrown when a file is not found.
	/// @class file_not_found_exception
	class CLASS_DECL_AXIS file_not_found_exception : public exception
	{
	public:
		file_not_found_exception()
			: exception("File not found")
		{}

		file_not_found_exception(const char * filename)
			: exception("File not found (" + string(filename) + ")")
		{}
	};

	/// Actions to listen for. Rename will send two events, one for
	/// the deletion of the old file, and one for the creation of the
	/// new file.
	enum e_action
	{
		/// Sent when a file is created or renamed
		action_add = 1,
		/// Sent when a file is deleted or renamed
		action_delete = 2,
		/// Sent when a file is modified
		action_modify = 4

	};
   
   
	/// Listens to files and directories and dispatches events
	/// to notify the parent program of the changes.
	/// @class file_watcher
	class CLASS_DECL_AXIS file_watcher
	{
	private:
		
      /// The implementation
		file_watcher_impl       * m_pimpl;

	public:

      bool  m_bUpdating;



		file_watcher();
		virtual ~file_watcher();

		/// Add a directory watch
		/// @exception file_not_found_exception Thrown when the requested directory does not exist
		id add_watch(const char * directory, file_watch_listener * pwatcher, bool bRecursive);

		/// Remove a directory watch. This is a brute force search O(nlogn).
		void remove_watch(const char * directory);

      void remove_watch(id id);

		/// Updates the watcher. Must be called often.
		void update();


	};//end file_watcher


	/// Basic interface for listening for file events.
	/// @class file_watch_listener
	class CLASS_DECL_AXIS file_watch_listener
	{
	public:
      
      
		file_watch_listener() {}
		virtual ~file_watch_listener() {}

		/// Handles the action file action
		/// @param watchid The watch id for the directory
		/// @param dir The directory
		/// @param filename The filename that was accessed (not full path)
		/// @param action Action that was performed
		virtual void handle_file_action(id watchid, const char * dir, const char * filename, e_action action) = 0;

      
	}; // class file_watch_listener


} // namespace file_watcher





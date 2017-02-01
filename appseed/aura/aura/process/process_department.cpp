#include "framework.h"



#ifndef TINY_PROCESS_LIBRARY_HPP_
#define TINY_PROCESS_LIBRARY_HPP_

//#include <string>
//#include <functional>
//#include <vector>
//#include <mutex>
//#include <thread>
//#include <memory>
#ifndef _WIN32
#include <sys/wait.h>
#endif

///Platform independent class for creating processes
class Process :
   virtual public object
{
public:
#ifdef _WIN32
  typedef unsigned long id_type; //Process id type
  typedef void *fd_type; //File descriptor type
#ifdef UNICODE
  typedef std::wstring string_type;
#else
  typedef string string_type;
#endif
#else
  typedef pid_t id_type;
  typedef int fd_type;
  typedef string string_type;
#endif
private:
  class Data {
  public:
    Data();
    id_type id;
#ifdef _WIN32
    void *handle;
#endif
  };
public:
  ///Note on Windows: it seems not possible to specify which pipes to redirect.
  ///Thus, at the moment, if read_stdout==nullptr, read_stderr==nullptr and open_stdin==false,
  ///the stdout, stderr and stdin are sent to the parent process instead.
  Process(::aura::application * papp, const string_type &command, const string_type &path,
          //PFN_PROCESS_OUTPUT read_stdout=NULL,
          //PFN_PROCESS_OUTPUT read_stderr=NULL,
          bool open_stdout = true,
          bool open_stderr = true,
          bool open_stdin=false,
          size_t buffer_size=131072);
//#ifndef _WIN32
//  /// Supported on Unix-like systems only.
//  Process(std::function<void()> function,
//          PFN_PROCESS_OUTPUT read_stdout=NULL,
//          PFN_PROCESS_OUTPUT read_stderr=NULL,
//          bool open_stdin=false,
//          size_t buffer_size=131072);
//#endif
  ~Process();

  ///Get the process id of the started process.
  id_type get_id();
  ///Wait until process is finished, and return exit status.
  int get_exit_status();
  ///Write to stdin.
  bool write(const char *bytes, size_t n);
  ///Write to stdin. Convenience function using write(const char *, size_t).
  bool write(const string &data);
  ///Close stdin. If the process takes parameters from stdin, use this to notify that all parameters have been sent.
  void close_stdin();

  ///Kill the process. force=true is only supported on Unix-like systems.
  void kill(bool force=false);
  ///Kill a given process id. Use kill(bool force) instead if possible. force=true is only supported on Unix-like systems.
  static void kill(id_type id, bool force=false);

//private:
  Data data;
  bool closed;
  mutex close_mutex;
  memory read_stdout;
  memory read_stderr;
  thread * stdout_thread;
  thread * stderr_thread;
  bool open_stdin;
  bool open_stdout;
  bool open_stderr;
  mutex stdin_mutex;
  size_t buffer_size;

  pointer < fd_type > stdout_fd;
   pointer < fd_type > stderr_fd;
   pointer < fd_type >  stdin_fd;

  id_type open(const string_type &command, const string_type &path);
  void async_read();
  void close_fds();

  #ifndef _WIN32

    /// Supported on Unix-like systems only.
    template < typename PRED >
  Process(::aura::application * papp,    bool open_stdout,
         bool open_stderr,
          bool open_stdin,

PRED function,
          size_t buffer_size=131072);

  template < typename PRED >
  Process::id_type Process::open(PRED function)
  {
  if(open_stdin)
    stdin_fd=new fd_type;
  if(open_stdout)
    stdout_fd=new fd_type;
  if(open_stderr)
    stderr_fd=new fd_type;

  int stdin_p[2], stdout_p[2], stderr_p[2];

  if(stdin_fd && pipe(stdin_p)!=0)
    return -1;
  if(stdout_fd && pipe(stdout_p)!=0) {
    if(stdin_fd) {close(stdin_p[0]);close(stdin_p[1]);}
    return -1;
  }
  if(stderr_fd && pipe(stderr_p)!=0) {
    if(stdin_fd) {close(stdin_p[0]);close(stdin_p[1]);}
    if(stdout_fd) {close(stdout_p[0]);close(stdout_p[1]);}
    return -1;
  }

  id_type pid = ::fork();

  if (pid < 0) {
    if(stdin_fd) {close(stdin_p[0]);close(stdin_p[1]);}
    if(stdout_fd) {close(stdout_p[0]);close(stdout_p[1]);}
    if(stderr_fd) {close(stderr_p[0]);close(stderr_p[1]);}
    return pid;
  }
  else if (pid == 0) {
    if(stdin_fd) dup2(stdin_p[0], 0);
    if(stdout_fd) dup2(stdout_p[1], 1);
    if(stderr_fd) dup2(stderr_p[1], 2);
    if(stdin_fd) {close(stdin_p[0]);close(stdin_p[1]);}
    if(stdout_fd) {close(stdout_p[0]);close(stdout_p[1]);}
    if(stderr_fd) {close(stderr_p[0]);close(stderr_p[1]);}

    //Based on http://stackoverflow.com/a/899533/3808293
    int fd_max=sysconf(_SC_OPEN_MAX);
    for(int fd=3;fd<fd_max;fd++)
      close(fd);

    setpgid(0, 0);
    //TODO: See here on how to emulate tty for colors: http://stackoverflow.com/questions/1401002/trick-an-application-into-thinking-its-stdin-is-interactive-not-a-pipe
    //TODO: One solution is: echo "command;exit"|script -q /dev/null

    function();

    _exit(EXIT_FAILURE);
  }

  if(stdin_fd) close(stdin_p[0]);
  if(stdout_fd) close(stdout_p[1]);
  if(stderr_fd) close(stderr_p[1]);

  if(stdin_fd) *stdin_fd = stdin_p[1];
  if(stdout_fd) *stdout_fd = stdout_p[0];
  if(stderr_fd) *stderr_fd = stderr_p[0];

  closed=false;
  data.id=pid;
  return pid;
}

#endif

};

#endif  // TINY_PROCESS_LIBRARY_HPP_

Process::Process(::aura::application * papp,const string_type &command, const string_type &path,
                 bool open_stdout, bool open_stderr, bool open_stdin, size_t buffer_size):object(papp),
                 closed(true), open_stdout(open_stdout), open_stderr(open_stderr), open_stdin(open_stdin), buffer_size(buffer_size) {
  open(command, path);
  async_read();
}

Process::~Process() {
  close_fds();
}

Process::id_type Process::get_id() {
  return data.id;
}

bool Process::write(const string &data) {
  return write(data.c_str(), data.size());
}

#ifdef _WIN32

#include "process.hpp"
#include <windows.h>
#include <cstring>
#include <TlHelp32.h>
#include <stdexcept>

Process::Data::Data(): id(0), handle(NULL) {}

namespace {
  // Simple HANDLE wrapper to close it automatically from the destructor.
  class Handle {
  public:
    Handle() : handle(INVALID_HANDLE_VALUE) { }
    ~Handle() {
      close();
    }
    void close() {
      if (handle != INVALID_HANDLE_VALUE)
        ::CloseHandle(handle);
    }
    HANDLE detach() {
      HANDLE old_handle = handle;
      handle = INVALID_HANDLE_VALUE;
      return old_handle;
    }
    operator HANDLE() const { return handle; }
    HANDLE* operator&() { return &handle; }
  private:
    HANDLE handle;
  };

  //Based on the discussion thread: https://www.reddit.com/r/cpp/comments/3vpjqg/a_new_platform_independent_process_library_for_c11/cxq1wsj
  std::mutex create_process_mutex;
}

//Based on the example at https://msdn.microsoft.com/en-us/library/windows/desktop/ms682499(v=vs.85).aspx.
Process::id_type Process::open(const string_type &command, const string_type &path) {
  if(open_stdin)
    stdin_fd=std::unique_ptr<fd_type>(new fd_type(NULL));
  if(read_stdout)
    stdout_fd=std::unique_ptr<fd_type>(new fd_type(NULL));
  if(read_stderr)
    stderr_fd=std::unique_ptr<fd_type>(new fd_type(NULL));

  Handle stdin_rd_p;
  Handle stdin_wr_p;
  Handle stdout_rd_p;
  Handle stdout_wr_p;
  Handle stderr_rd_p;
  Handle stderr_wr_p;

  SECURITY_ATTRIBUTES security_attributes;

  security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
  security_attributes.bInheritHandle = TRUE;
  security_attributes.lpSecurityDescriptor = nullptr;

  std::lock_guard<std::mutex> lock(create_process_mutex);
  if(stdin_fd) {
    if (!CreatePipe(&stdin_rd_p, &stdin_wr_p, &security_attributes, 0) ||
        !SetHandleInformation(stdin_wr_p, HANDLE_FLAG_INHERIT, 0))
      return 0;
  }
  if(stdout_fd) {
    if (!CreatePipe(&stdout_rd_p, &stdout_wr_p, &security_attributes, 0) ||
        !SetHandleInformation(stdout_rd_p, HANDLE_FLAG_INHERIT, 0)) {
      return 0;
    }
  }
  if(stderr_fd) {
    if (!CreatePipe(&stderr_rd_p, &stderr_wr_p, &security_attributes, 0) ||
        !SetHandleInformation(stderr_rd_p, HANDLE_FLAG_INHERIT, 0)) {
      return 0;
    }
  }

  PROCESS_INFORMATION process_info;
  STARTUPINFO startup_info;

  ZeroMemory(&process_info, sizeof(PROCESS_INFORMATION));

  ZeroMemory(&startup_info, sizeof(STARTUPINFO));
  startup_info.cb = sizeof(STARTUPINFO);
  startup_info.hStdInput = stdin_rd_p;
  startup_info.hStdOutput = stdout_wr_p;
  startup_info.hStdError = stderr_wr_p;
  if(stdin_fd || stdout_fd || stderr_fd)
    startup_info.dwFlags |= STARTF_USESTDHANDLES;

  string_type process_command=command;
#ifdef MSYS_PROCESS_USE_SH
  size_t pos=0;
  while((pos=process_command.find('\\', pos))!=string_type::npos) {
    process_command.replace(pos, 1, "\\\\\\\\");
    pos+=4;
  }
  pos=0;
  while((pos=process_command.find('\"', pos))!=string_type::npos) {
    process_command.replace(pos, 1, "\\\"");
    pos+=2;
  }
  process_command.insert(0, "sh -c \"");
  process_command+="\"";
#endif

  BOOL bSuccess = CreateProcess(nullptr, process_command.empty()?nullptr:&process_command[0], nullptr, nullptr, TRUE, 0,
                                nullptr, path.empty()?nullptr:path.c_str(), &startup_info, &process_info);

  if(!bSuccess) {
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);
    return 0;
  }
  else {
    CloseHandle(process_info.hThread);
  }

  if(stdin_fd) *stdin_fd=stdin_wr_p.detach();
  if(stdout_fd) *stdout_fd=stdout_rd_p.detach();
  if(stderr_fd) *stderr_fd=stderr_rd_p.detach();

  closed=false;
  data.id=process_info.dwProcessId;
  data.handle=process_info.hProcess;
  return process_info.dwProcessId;
}

void Process::async_read() {
  if(data.id==0)
    return;
  if(stdout_fd) {
    stdout_thread=std::thread([this](){
      DWORD n;
      std::unique_ptr<char[]> buffer(new char[buffer_size]);
      for (;;) {
        BOOL bSuccess = ReadFile(*stdout_fd, static_cast<CHAR*>(buffer.get()), static_cast<DWORD>(buffer_size), &n, nullptr);
        if(!bSuccess || n == 0)
          break;
        read_stdout(buffer.get(), static_cast<size_t>(n));
      }
    });
  }
  if(stderr_fd) {
    stderr_thread=std::thread([this](){
      DWORD n;
      std::unique_ptr<char[]> buffer(new char[buffer_size]);
      for (;;) {
        BOOL bSuccess = ReadFile(*stderr_fd, static_cast<CHAR*>(buffer.get()), static_cast<DWORD>(buffer_size), &n, nullptr);
        if(!bSuccess || n == 0)
          break;
        read_stderr(buffer.get(), static_cast<size_t>(n));
      }
    });
  }
}

int Process::get_exit_status() {
  if(data.id==0)
    return -1;
  DWORD exit_status;
  WaitForSingleObject(data.handle, INFINITE);
  if(!GetExitCodeProcess(data.handle, &exit_status))
    exit_status=-1;
  {
    std::lock_guard<std::mutex> lock(close_mutex);
    CloseHandle(data.handle);
    closed=true;
  }
  close_fds();

  return static_cast<int>(exit_status);
}

void Process::close_fds() {
  if(stdout_thread.joinable())
    stdout_thread.join();
  if(stderr_thread.joinable())
    stderr_thread.join();

  if(stdin_fd)
    close_stdin();
  if(stdout_fd) {
    if(*stdout_fd!=NULL) CloseHandle(*stdout_fd);
    stdout_fd.reset();
  }
  if(stderr_fd) {
    if(*stderr_fd!=NULL) CloseHandle(*stderr_fd);
    stderr_fd.reset();
  }
}

bool Process::write(const char *bytes, size_t n) {
  if(!open_stdin)
    throw std::invalid_argument("Can't write to an unopened stdin pipe. Please set open_stdin=true when constructing the process.");

  std::lock_guard<std::mutex> lock(stdin_mutex);
  if(stdin_fd) {
    DWORD written;
    BOOL bSuccess=WriteFile(*stdin_fd, bytes, static_cast<DWORD>(n), &written, nullptr);
    if(!bSuccess || written==0) {
      return false;
    }
    else {
      return true;
    }
  }
  return false;
}

void Process::close_stdin() {
  std::lock_guard<std::mutex> lock(stdin_mutex);
  if(stdin_fd) {
    if(*stdin_fd!=NULL) CloseHandle(*stdin_fd);
    stdin_fd.reset();
  }
}

//Based on http://stackoverflow.com/a/1173396
void Process::kill(bool force) {
  std::lock_guard<std::mutex> lock(close_mutex);
  if(data.id>0 && !closed) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(snapshot) {
      PROCESSENTRY32 process;
      ZeroMemory(&process, sizeof(process));
      process.dwSize = sizeof(process);
      if(Process32First(snapshot, &process)) {
        do {
          if(process.th32ParentProcessID==data.id) {
            HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, FALSE, process.th32ProcessID);
            if(process_handle) {
              TerminateProcess(process_handle, 2);
              CloseHandle(process_handle);
            }
          }
        } while (Process32Next(snapshot, &process));
      }
      CloseHandle(snapshot);
    }
    TerminateProcess(data.handle, 2);
  }
}

//Based on http://stackoverflow.com/a/1173396
void Process::kill(id_type id, bool force) {
  if(id==0)
    return;
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if(snapshot) {
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);
    if(Process32First(snapshot, &process)) {
      do {
        if(process.th32ParentProcessID==id) {
          HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, FALSE, process.th32ProcessID);
          if(process_handle) {
            TerminateProcess(process_handle, 2);
            CloseHandle(process_handle);
          }
        }
      } while (Process32Next(snapshot, &process));
    }
    CloseHandle(snapshot);
  }
  HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, FALSE, id);
  if(process_handle) TerminateProcess(process_handle, 2);
}
#else
//#include "process.hpp"
//#include <cstdlib>
#include <unistd.h>
#include <signal.h>
//#include <stdexcept>

Process::Data::Data(): id(-1) {}

//Process::Process(std::function<void()> function,
//                 std::function<void (const char *, size_t)> read_stdout,
//                 std::function<void (const char *, size_t)> read_stderr,
//                 bool open_stdin, size_t buffer_size) :
//                 closed(true), read_stdout(read_stdout), read_stderr(read_stderr), open_stdin(open_stdin), buffer_size(buffer_size) {
//  open(function);
//  async_read();
//}

//Process::id_type Process::open(std::function<void()> function) {
//  if(open_stdin)
//    stdin_fd=std::unique_ptr<fd_type>(new fd_type);
//  if(read_stdout)
//    stdout_fd=std::unique_ptr<fd_type>(new fd_type);
//  if(read_stderr)
//    stderr_fd=std::unique_ptr<fd_type>(new fd_type);
//
//  int stdin_p[2], stdout_p[2], stderr_p[2];
//
//  if(stdin_fd && pipe(stdin_p)!=0)
//    return -1;
//  if(stdout_fd && pipe(stdout_p)!=0) {
//    if(stdin_fd) {close(stdin_p[0]);close(stdin_p[1]);}
//    return -1;
//  }
//  if(stderr_fd && pipe(stderr_p)!=0) {
//    if(stdin_fd) {close(stdin_p[0]);close(stdin_p[1]);}
//    if(stdout_fd) {close(stdout_p[0]);close(stdout_p[1]);}
//    return -1;
//  }
//
//  id_type pid = fork();
//
//  if (pid < 0) {
//    if(stdin_fd) {close(stdin_p[0]);close(stdin_p[1]);}
//    if(stdout_fd) {close(stdout_p[0]);close(stdout_p[1]);}
//    if(stderr_fd) {close(stderr_p[0]);close(stderr_p[1]);}
//    return pid;
//  }
//  else if (pid == 0) {
//    if(stdin_fd) dup2(stdin_p[0], 0);
//    if(stdout_fd) dup2(stdout_p[1], 1);
//    if(stderr_fd) dup2(stderr_p[1], 2);
//    if(stdin_fd) {close(stdin_p[0]);close(stdin_p[1]);}
//    if(stdout_fd) {close(stdout_p[0]);close(stdout_p[1]);}
//    if(stderr_fd) {close(stderr_p[0]);close(stderr_p[1]);}
//
//    //Based on http://stackoverflow.com/a/899533/3808293
//    int fd_max=sysconf(_SC_OPEN_MAX);
//    for(int fd=3;fd<fd_max;fd++)
//      close(fd);
//
//    setpgid(0, 0);
//    //TODO: See here on how to emulate tty for colors: http://stackoverflow.com/questions/1401002/trick-an-application-into-thinking-its-stdin-is-interactive-not-a-pipe
//    //TODO: One solution is: echo "command;exit"|script -q /dev/null
//
//    if(function)
//      function();
//
//    _exit(EXIT_FAILURE);
//  }
//
//  if(stdin_fd) close(stdin_p[0]);
//  if(stdout_fd) close(stdout_p[1]);
//  if(stderr_fd) close(stderr_p[1]);
//
//  if(stdin_fd) *stdin_fd = stdin_p[1];
//  if(stdout_fd) *stdout_fd = stdout_p[0];
//  if(stderr_fd) *stderr_fd = stderr_p[0];
//
//  closed=false;
//  data.id=pid;
//  return pid;
//}

Process::id_type Process::open(const string &command, const string &path) {
  return open([&command, &path] {
    if(!path.empty()) {
      auto path_escaped=path;
      size_t pos=0;
      //Based on https://www.reddit.com/r/cpp/comments/3vpjqg/a_new_platform_independent_process_library_for_c11/cxsxyb7
      while((pos=path_escaped.find('\'', pos))!=string::npos) {
        path_escaped.replace(pos, 1, "'\\''");
        pos+=4;
      }
      execl("/bin/sh", "sh", "-c", ("cd '"+path_escaped+"' && "+command).c_str(), NULL);
    }
    else
      execl("/bin/sh", "sh", "-c", command.c_str(), NULL);
  });
}

void Process::async_read() {
  if(data.id<=0)
    return;
  if(stdout_fd) {
    stdout_thread=::fork(get_app(),[&](){
      pointer < char > buffer = new char[buffer_size];
      ssize_t n;
      while ((n=read(*stdout_fd, buffer.get(), buffer_size)) > 0)
        read_stdout.append(buffer.get(), static_cast<size_t>(n));
    });
  }
  if(stderr_fd) {
    stderr_thread=::fork(get_app(), [&](){
      pointer < char > buffer = ( new char[buffer_size] );
      ssize_t n;
      while ((n=read(*stderr_fd, buffer.get(), buffer_size)) > 0)
        read_stderr.append(buffer.get(), static_cast<size_t>(n));
    });
  }
}

int Process::get_exit_status() {
  if(data.id<=0)
    return -1;
  int exit_status;
  waitpid(data.id, &exit_status, 0);
  {
    synch_lock lock(&close_mutex);
    closed=true;
  }
  close_fds();

  if(exit_status>=256)
    exit_status=exit_status>>8;
  return exit_status;
}

void Process::close_fds() {
  if(stdout_thread)
  {
   ::multithreading::post_quit_and_wait(stdout_thread, ::duration::infinite());
  }
  if(stderr_thread)
  {
   ::multithreading::post_quit_and_wait(stderr_thread, ::duration::infinite());
  }

  if(stdin_fd)
    close_stdin();
  if(stdout_fd) {
    if(data.id>0)
      close(*stdout_fd);
    stdout_fd = NULL;
  }
  if(stderr_fd) {
    if(data.id>0)
      close(*stderr_fd);
    stderr_fd = NULL;
  }
}

bool Process::write(const char *bytes, size_t n) {
  if(!open_stdin)
    throw invalid_argument_exception(get_app(), "Can't write to an unopened stdin pipe. Please set open_stdin=true when constructing the process.");

  synch_lock lock(&stdin_mutex);
  if(stdin_fd) {
    if(::write(*stdin_fd, bytes, n)>=0) {
      return true;
    }
    else {
      return false;
    }
  }
  return false;
}

void Process::close_stdin() {
  synch_lock  lock(&stdin_mutex);
  if(stdin_fd) {
    if(data.id>0)
      close(*stdin_fd);
    stdin_fd = NULL;
  }
}

void Process::kill(bool force) {
  synch_lock lock(&close_mutex);
  if(data.id>0 && !closed) {
    if(force)
      ::kill(-data.id, SIGTERM);
    else
      ::kill(-data.id, SIGINT);
  }
}

void Process::kill(id_type id, bool force) {
  if(id<=0)
    return;
  if(force)
    ::kill(-id, SIGTERM);
  else
    ::kill(-id, SIGINT);
}
#endif

namespace process
{


   department::department(::aura::application * papp):
      object(papp),
      ::aura::department(papp)
   {

   }


   department::~department()
   {

   }


   var department::get_output(const char * pszCmdLine,const ::duration & dur,int32_t iShow, bool * pbPotentialTimeout)
   {

      string strRead;

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout, &strRead);

      //Process proc(get_app(), pszCmdLine, "");

      //strRead = proc.read_stdout.to_string();

      //strRead += proc.read_stderr.to_string();

      return strRead;

   }



   uint32_t department::retry(const char * pszCmdLine,const ::duration & dur,int32_t iShow, bool * pbPotentialTimeout)
   {

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout);

      return proc.m_uiRetCode;


   }


   uint32_t department::synch(const char * pszCmdLine,int32_t iShow, const ::duration & dur, bool * pbPotentialTimeout)
   {

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout);

      return proc.m_uiRetCode;

   }


   bool department::launch(const char * pszCmdLine,int32_t iShow, const char * pszDir)
   {

      const char * pszEnd = NULL;

      string strBin = consume_param(pszCmdLine,&pszEnd);

#ifndef METROWIN

      int32_t iOk = call_async(strBin,pszEnd,pszDir,iShow, false);

      return iOk != 0;

#else

      throw todo(get_app());

#endif

   }


   uint32_t department::elevated_synch(const char * pszCmdLine,int32_t iShow,const ::duration & dur,bool * pbPotentialTimeout)
   {

      process_processor proc(get_app(),pszCmdLine,dur,pbPotentialTimeout, NULL, true);

      return proc.m_uiRetCode;

   }


   department::process_thread::process_thread(::aura::application * papp,const string & strCmdLine,const ::duration & dur,bool * pbPotentialTimeout,string * pstrRead,bool bElevated):
      object(papp),
      thread(papp),
      simple_thread(papp),
      m_strCmdLine(strCmdLine),
      m_spprocess(allocer()),
      m_pstrRead(pstrRead)
      {

      if(dur.is_pos_infinity())
      {

         m_uiTimeout = 0;

      }
      else
      {

         m_uiTimeout =  dur.tick_duration();

      }


      m_pbPotentialTimeout    = pbPotentialTimeout;
      m_pbInitFailure         = NULL;
      m_bElevated             = bElevated;

   }


   int32_t department::process_thread::run()
   {

      int iRetCode;

      if(m_bElevated)
      {

         iRetCode = run_elevated();

      }
      else
      {

         iRetCode = run_normal();

      }

      return iRetCode;

   }



   int32_t department::process_thread::run_normal()
   {

      if(!m_spprocess->create_child_process(m_strCmdLine,true))
      {

         if(m_pbInitFailure != NULL)
         {

            *m_pbInitFailure = true;

         }

         if(m_pevReady != NULL)
         {

            m_pevReady->SetEvent();

         }

         return false;

      }

      m_uiStartTime = ::get_tick_count();

      string strRead;

      while(!m_spprocess->has_exited(m_puiRetCode))
      {

         strRead = m_spprocess->m_pipe.m_sppipeOut->read();

         if(m_pstrRead != NULL)
         {

            *m_pstrRead += strRead;

         }

         if(!retry())
            break;

         Sleep(100);

      }

      while(get_run_thread())
      {

         strRead = m_spprocess->m_pipe.m_sppipeOut->read();

         if(strRead.is_empty())
         {

            break;

         }
         else
         {

            if(m_pstrRead != NULL)
            {

               *m_pstrRead += strRead;

            }

         }

      }

      if(m_pevReady != NULL)
      {

         m_pevReady->SetEvent();

      }

      return 0;

   }

   int32_t department::process_thread::run_elevated()
   {

      int32_t iRetCode = m_spprocess->synch_elevated(m_strCmdLine,SW_HIDE,millis(m_uiTimeout),m_pbPotentialTimeout);

      if(m_puiRetCode != NULL)
      {

         *m_puiRetCode = iRetCode;

      }

      if(m_pevReady != NULL)
      {

         m_pevReady->SetEvent();

      }


      return 0;

   }

   bool department::process_thread::retry()
   {

      if(m_uiTimeout > 0 && ::get_tick_count() - m_uiStartTime > m_uiTimeout)
      {

         if(m_pbPotentialTimeout != NULL)
         {

            *m_pbPotentialTimeout = true;

         }

         return false;

      }

      return true;

   }


   department::process_processor::process_processor(::aura::application * papp,const string & strCmdLine,const duration & dur,bool * pbPotentialTimeout,string * pstrRead,bool bElevated):
      object(papp),
      m_evReady(papp)
   {

      m_uiRetCode = -1;

      m_bInitFailure = false;

      m_bPotentialTimeout = false;

      m_pbPotentialTimeout = pbPotentialTimeout;

      m_bElevated = bElevated;

      m_pthread = new process_thread(papp,strCmdLine,dur,&m_bPotentialTimeout,pstrRead, bElevated);

      m_pthread->m_bAutoDelete = true;

      m_pthread->m_pbInitFailure = &m_bInitFailure;

      m_pthread->m_pbPotentialTimeout = &m_bPotentialTimeout;

      m_pthread->m_pevReady = &m_evReady;

      m_pthread->m_puiRetCode = &m_uiRetCode;

      if(dur.is_pos_infinity())
      {

         m_pthread->run();

         ::aura::del(m_pthread);

      }
      else
      {

         m_evReady.ResetEvent();

         m_pthread->begin();

         m_evReady.wait();

      }

   }

   department::process_processor::~process_processor()
   {

      if(m_pbPotentialTimeout != NULL)
      {

         *m_pbPotentialTimeout = m_bPotentialTimeout;

      }

   }



} // namespace process





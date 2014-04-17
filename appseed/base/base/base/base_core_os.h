#ifndef BASE_BASE_CORE_OS_H
#define BASE_BASE_CORE_OS_H


#pragma once

namespace xxx {

    namespace xxx2 {

        class xxx23teste {
        public:

            xxx23teste() {
            }

            ~xxx23teste() {
            }
        };
    }
}

namespace xxx2 {
    namespace xxx {

        class xxx2teste {
        public:

            xxx2teste() {
            };

            ~xxx2teste() {
            };
        };

    }
}


namespace core {

    class CLASS_DECL_BASE os :
    public object {
    public:


        os(sp(base_application) papp);
        virtual ~os();


        virtual bool reboot();
        virtual bool shutdown(bool bPowerOff);

        virtual void terminate_processes_by_title(const char * pszName);
#ifdef WINDOWS
        virtual string get_module_path(HMODULE hmodule);
#endif
        virtual bool get_pid_by_path(const char * pszName, uint32_t & dwPid);
        virtual bool get_pid_by_title(const char * pszName, uint32_t & dwPid);
        virtual void get_all_processes(uint_array & dwa);
        virtual string get_process_path(uint32_t dwPid);


        virtual bool connection_settings_get_auto_detect();
        virtual string connection_settings_get_auto_config_url();


        virtual bool local_machine_set_run(const char * pszKey, const char * pszCommand);
        virtual bool local_machine_set_run_once(const char * pszKey, const char * pszCommand);
        virtual bool current_user_set_run(const char * pszKey, const char * pszCommand);
        virtual bool current_user_set_run_once(const char * pszKey, const char * pszCommand);

        virtual bool defer_register_ca2_plugin_for_mozilla();


        virtual bool file_extension_get_open_with_list_keys(stringa & straKey, const char * pszExtension);
        virtual bool file_extension_get_open_with_list_commands(stringa & straCommand, const char * pszExtension);

        virtual bool file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath);
        virtual bool file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszCommand, const char * pszParam);
        virtual bool file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam);

#ifdef WINDOWS

        virtual bool open_in_ie(const char * lpcsz);

#endif


        virtual bool create_service(sp(::base_application) papp);
        virtual bool remove_service(sp(::base_application) papp);

        virtual bool start_service(sp(::base_application) papp);
        virtual bool stop_service(sp(::base_application) papp);


        virtual bool resolve_link(string & strTarget, const char * pszSource, sp(::user::interaction) puiMessageParentOptional = NULL);

        DECLSPEC_NO_RETURN void raise_exception(uint32_t dwExceptionCode, uint32_t dwExceptionFlags = EXCEPTION_NONCONTINUABLE);


        virtual bool is_remote_session();

        virtual void post_to_all_threads(UINT message, WPARAM wparam, LPARAM lparam);


        virtual void set_file_status(const char * lpszFileName, const ::file::file_status& status);

    };


    typedef smart_pointer < os > os_sp;


} // namespace core


#endif // BASE_BASE_CORE_OS_H











#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=cc
CCC=CC
CXX=CC
FC=f95
AS=as

# Macros
CND_PLATFORM=OracleSolarisStudio-Solaris-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/43900685/ca_wstringtovss.o \
	${OBJECTDIR}/_ext/1360937173/spa_starter_start.o \
	${OBJECTDIR}/_ext/2111841970/simple_password.o \
	${OBJECTDIR}/_ext/1684649001/simple_graphics.o \
	${OBJECTDIR}/_ext/9007153/hotplugin_plugin.o \
	${OBJECTDIR}/_ext/43900685/ca_file_watcher_thread.o \
	${OBJECTDIR}/_ext/43900685/ca_stra.o \
	${OBJECTDIR}/_ext/1360937173/spa.o \
	${OBJECTDIR}/_ext/1360937173/spa_focus.o \
	${OBJECTDIR}/_ext/1360937173/spa_installer_square.o \
	${OBJECTDIR}/_ext/43900685/ca_net.o \
	${OBJECTDIR}/_ext/43900685/ca_dir.o \
	${OBJECTDIR}/_ext/1360937173/spa_machine_event.o \
	${OBJECTDIR}/_ext/43900685/ca_verisimple_wstring.o \
	${OBJECTDIR}/_ext/1360937173/spa_install_ca2.o \
	${OBJECTDIR}/_ext/1360937173/spa_machine_event_data.o \
	${OBJECTDIR}/_ext/583780700/ca_os_file.o \
	${OBJECTDIR}/_ext/43900685/ca_mktime.o \
	${OBJECTDIR}/_ext/43900685/ca_printf.o \
	${OBJECTDIR}/_ext/1295684859/main_bsdiff.o \
	${OBJECTDIR}/_ext/9007153/hotplugin_host.o \
	${OBJECTDIR}/_ext/583780700/ca_os.o \
	${OBJECTDIR}/_ext/43900685/ca_string_to_integer.o \
	${OBJECTDIR}/_ext/43900685/ca_simple_event.o \
	${OBJECTDIR}/_ext/43900685/ca_simple_list.o \
	${OBJECTDIR}/_ext/1295684859/bspatch.o \
	${OBJECTDIR}/_ext/43900685/ca_simple_obj.o \
	${OBJECTDIR}/_ext/43900685/ca.o \
	${OBJECTDIR}/_ext/2119092129/nessie.o \
	${OBJECTDIR}/_ext/43900685/ca_strx.o \
	${OBJECTDIR}/_ext/43900685/_initterm.o \
	${OBJECTDIR}/_ext/1295684859/crctable.o \
	${OBJECTDIR}/_ext/583780700/ca_os_process.o \
	${OBJECTDIR}/_ext/43900685/ca_strw.o \
	${OBJECTDIR}/_ext/43900685/ca_mem.o \
	${OBJECTDIR}/_ext/416166309/windows_thread.o \
	${OBJECTDIR}/_ext/43900685/ca_heap.o \
	${OBJECTDIR}/_ext/43900685/ca_version.o \
	${OBJECTDIR}/_ext/1295684859/blocksort.o \
	${OBJECTDIR}/_ext/43900685/ca_debug.o \
	${OBJECTDIR}/_ext/2111841970/simple_tap.o \
	${OBJECTDIR}/_ext/2111841970/simple_ui.o \
	${OBJECTDIR}/_ext/583780700/ca_os_win_base.o \
	${OBJECTDIR}/_ext/43900685/ca_file_spa.o \
	${OBJECTDIR}/_ext/43901075/os_process.o \
	${OBJECTDIR}/_ext/583780700/ca_os_simple_brush.o \
	${OBJECTDIR}/_ext/43900685/ca_str.o \
	${OBJECTDIR}/_ext/1360937173/spa_installer.o \
	${OBJECTDIR}/_ext/1360937173/spa_trace.o \
	${OBJECTDIR}/_ext/1295684859/compress.o \
	${OBJECTDIR}/_ext/2111841970/simple_edit_box.o \
	${OBJECTDIR}/_ext/43900685/ca_verisimple_string.o \
	${OBJECTDIR}/_ext/43900685/ca_geometric_types.o \
	${OBJECTDIR}/_ext/2119092129/crypt.o \
	${OBJECTDIR}/_ext/1328484458/ansios_thread.o \
	${OBJECTDIR}/_ext/43900685/ca_xmlite.o \
	${OBJECTDIR}/_ext/43900685/ca_simple_memory.o \
	${OBJECTDIR}/_ext/43900685/ca_file_watcher.o \
	${OBJECTDIR}/_ext/1360937173/spa_login.o \
	${OBJECTDIR}/_ext/583780700/ca_os_file_watcher.o \
	${OBJECTDIR}/_ext/1295684859/huffman.o \
	${OBJECTDIR}/_ext/1295684859/randtable.o \
	${OBJECTDIR}/_ext/9007153/hotplugin_container_launcher.o \
	${OBJECTDIR}/_ext/1295684859/decompress.o \
	${OBJECTDIR}/_ext/1328484458/ansios_file_std.o \
	${OBJECTDIR}/_ext/1295684859/bsdiff.o \
	${OBJECTDIR}/_ext/43900685/ca_file_watcher_impl.o \
	${OBJECTDIR}/_ext/43900685/ca_vsstringtow.o \
	${OBJECTDIR}/_ext/583780700/ca_os_small_ipca_channel.o \
	${OBJECTDIR}/_ext/583780700/ca_os_simple_path.o \
	${OBJECTDIR}/_ext/1328484458/ansios_cross_win_file.o \
	${OBJECTDIR}/_ext/43900685/ca_simple_shell_launcher.o \
	${OBJECTDIR}/_ext/43900685/ca_international.o \
	${OBJECTDIR}/_ext/1360937173/spa_plugin.o \
	${OBJECTDIR}/_ext/583780700/ca_os_http_lib.o \
	${OBJECTDIR}/_ext/1328484458/ansios_cross_win.o \
	${OBJECTDIR}/_ext/43900685/ca_window_graphics.o \
	${OBJECTDIR}/_ext/1684649001/simple_path.o \
	${OBJECTDIR}/_ext/1360937173/spa_main.o \
	${OBJECTDIR}/_ext/43900685/ca_small_ipca_channel.o \
	${OBJECTDIR}/_ext/43901075/os_thread.o \
	${OBJECTDIR}/_ext/43900685/ca_dir2.o \
	${OBJECTDIR}/_ext/43900685/ca_integer_to_string.o \
	${OBJECTDIR}/_ext/583780700/ca_os_window.o \
	${OBJECTDIR}/_ext/43901075/os_binreloc.o \
	${OBJECTDIR}/_ext/583780700/ca_os_simple_font.o \
	${OBJECTDIR}/_ext/43900685/ca_file_watcher_listener_thread.o \
	${OBJECTDIR}/_ext/1360937173/spa_spa.o \
	${OBJECTDIR}/_ext/583780700/ca_os_library.o \
	${OBJECTDIR}/_ext/583780700/ca_os_cross_win_file.o \
	${OBJECTDIR}/_ext/1360937173/spa_cube_run.o \
	${OBJECTDIR}/_ext/1295684859/bzlib.o \
	${OBJECTDIR}/_ext/43900685/ca_file.o \
	${OBJECTDIR}/_ext/43901075/os_http.o \
	${OBJECTDIR}/_ext/583780700/ca_os_window_cairo.o \
	${OBJECTDIR}/_ext/43900685/ca_user.o \
	${OBJECTDIR}/_ext/43900685/ca_c.o \
	${OBJECTDIR}/_ext/43900685/ca_std_file.o \
	${OBJECTDIR}/_ext/43900685/ca_conv.o \
	${OBJECTDIR}/_ext/1295684859/main_bspatch.o \
	${OBJECTDIR}/_ext/43900685/ca_simple_critical_section.o \
	${OBJECTDIR}/_ext/416166309/windows_user.o \
	${OBJECTDIR}/_ext/583780700/ca_os_simple_shell_launcher.o \
	${OBJECTDIR}/_ext/1360937173/spa_http.o \
	${OBJECTDIR}/_ext/1360937173/spa_boot.o \
	${OBJECTDIR}/_ext/583780700/ca_os_launcher.o \
	${OBJECTDIR}/_ext/583780700/ca_os_display.o \
	${OBJECTDIR}/_ext/1360937173/spa_bz.o \
	${OBJECTDIR}/_ext/583780700/ca_os_thread.o \
	${OBJECTDIR}/_ext/43900685/ca_simple_mutex.o \
	${OBJECTDIR}/_ext/1360937173/spa_window.o \
	${OBJECTDIR}/_ext/583780700/ca_os_http.o \
	${OBJECTDIR}/_ext/583780700/ca_os_simple_pen.o \
	${OBJECTDIR}/_ext/583780700/ca_os_simple_bitmap.o \
	${OBJECTDIR}/_ext/43900685/ca_mutex_lock.o \
	${OBJECTDIR}/_ext/43900685/ca_argcargv.o \
	${OBJECTDIR}/_ext/43900685/ca_template.o \
	${OBJECTDIR}/_ext/583780700/ca_os_simple_graphics.o \
	${OBJECTDIR}/_ext/1328484458/ansios_file.o \
	${OBJECTDIR}/_ext/43900685/ca_strdup.o \
	${OBJECTDIR}/_ext/2111841970/simple_label.o \
	${OBJECTDIR}/_ext/583780700/ca_os_cairo_keep.o \
	${OBJECTDIR}/_ext/583780700/ca_os_message_loop.o \
	${OBJECTDIR}/_ext/583780700/ca_os_cross_win_gdi.o \
	${OBJECTDIR}/_ext/583780700/ca_os_lock.o \
	${OBJECTDIR}/_ext/43900685/ca_url.o \
	${OBJECTDIR}/_ext/43900685/ca_math.o \
	${OBJECTDIR}/_ext/43900685/ca_md5.o \
	${OBJECTDIR}/_ext/1360937173/spa_small_bell.o \
	${OBJECTDIR}/_ext/43900685/ca_simple_array.o \
	${OBJECTDIR}/_ext/1360937173/spa_canvas.o \
	${OBJECTDIR}/_ext/43900685/ca_sprintf.o \
	${OBJECTDIR}/_ext/583780700/ca_os_process_pid.o \
	${OBJECTDIR}/_ext/43900685/ca_base64.o \
	${OBJECTDIR}/_ext/2119092129/whirpool.o \
	${OBJECTDIR}/_ext/43900685/ca_cpu_architecture.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/OracleSolarisStudio-Solaris-x86/libca.sol.so

dist/Debug/OracleSolarisStudio-Solaris-x86/libca.sol.so: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/OracleSolarisStudio-Solaris-x86
	${LINK.cc} -G -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libca.sol.so -KPIC -norunpath -h libca.sol.so ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/43900685/ca_wstringtovss.o: ../ca/ca_wstringtovss.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_wstringtovss.o ../ca/ca_wstringtovss.cpp

${OBJECTDIR}/_ext/1360937173/spa_starter_start.o: ../spa/spa_starter_start.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_starter_start.o ../spa/spa_starter_start.cpp

${OBJECTDIR}/_ext/2111841970/simple_password.o: ../simple_ui/simple_password.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111841970
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/2111841970/simple_password.o ../simple_ui/simple_password.cpp

${OBJECTDIR}/_ext/1684649001/simple_graphics.o: ../simple_graphics/simple_graphics.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1684649001
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1684649001/simple_graphics.o ../simple_graphics/simple_graphics.cpp

${OBJECTDIR}/_ext/9007153/hotplugin_plugin.o: ../hotplugin/hotplugin_plugin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/9007153
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/9007153/hotplugin_plugin.o ../hotplugin/hotplugin_plugin.cpp

${OBJECTDIR}/_ext/43900685/ca_file_watcher_thread.o: ../ca/ca_file_watcher_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_file_watcher_thread.o ../ca/ca_file_watcher_thread.cpp

${OBJECTDIR}/_ext/43900685/ca_stra.o: ../ca/ca_stra.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_stra.o ../ca/ca_stra.cpp

${OBJECTDIR}/_ext/1360937173/spa.o: ../spa/spa.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa.o ../spa/spa.cpp

${OBJECTDIR}/_ext/1360937173/spa_focus.o: ../spa/spa_focus.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_focus.o ../spa/spa_focus.cpp

${OBJECTDIR}/_ext/1360937173/spa_installer_square.o: ../spa/spa_installer_square.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_installer_square.o ../spa/spa_installer_square.cpp

${OBJECTDIR}/_ext/43900685/ca_net.o: ../ca/ca_net.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_net.o ../ca/ca_net.cpp

${OBJECTDIR}/_ext/43900685/ca_dir.o: ../ca/ca_dir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_dir.o ../ca/ca_dir.cpp

${OBJECTDIR}/_ext/1360937173/spa_machine_event.o: ../spa/spa_machine_event.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_machine_event.o ../spa/spa_machine_event.cpp

${OBJECTDIR}/_ext/43900685/ca_verisimple_wstring.o: ../ca/ca_verisimple_wstring.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_verisimple_wstring.o ../ca/ca_verisimple_wstring.cpp

${OBJECTDIR}/_ext/1360937173/spa_install_ca2.o: ../spa/spa_install_ca2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_install_ca2.o ../spa/spa_install_ca2.cpp

${OBJECTDIR}/_ext/1360937173/spa_machine_event_data.o: ../spa/spa_machine_event_data.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_machine_event_data.o ../spa/spa_machine_event_data.cpp

${OBJECTDIR}/_ext/583780700/ca_os_file.o: ../solaris/ca_os_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_file.o ../solaris/ca_os_file.cpp

${OBJECTDIR}/_ext/43900685/ca_mktime.o: ../ca/ca_mktime.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_mktime.o ../ca/ca_mktime.cpp

${OBJECTDIR}/_ext/43900685/ca_printf.o: ../ca/ca_printf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_printf.o ../ca/ca_printf.cpp

${OBJECTDIR}/_ext/1295684859/main_bsdiff.o: ../bsdiff/main_bsdiff.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/main_bsdiff.o ../bsdiff/main_bsdiff.cpp

${OBJECTDIR}/_ext/9007153/hotplugin_host.o: ../hotplugin/hotplugin_host.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/9007153
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/9007153/hotplugin_host.o ../hotplugin/hotplugin_host.cpp

${OBJECTDIR}/_ext/583780700/ca_os.o: ../solaris/ca_os.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os.o ../solaris/ca_os.cpp

${OBJECTDIR}/_ext/43900685/ca_string_to_integer.o: ../ca/ca_string_to_integer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_string_to_integer.o ../ca/ca_string_to_integer.cpp

${OBJECTDIR}/_ext/43900685/ca_simple_event.o: ../ca/ca_simple_event.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_simple_event.o ../ca/ca_simple_event.cpp

${OBJECTDIR}/_ext/43900685/ca_simple_list.o: ../ca/ca_simple_list.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_simple_list.o ../ca/ca_simple_list.cpp

${OBJECTDIR}/_ext/1295684859/bspatch.o: ../bsdiff/bspatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/bspatch.o ../bsdiff/bspatch.cpp

${OBJECTDIR}/_ext/43900685/ca_simple_obj.o: ../ca/ca_simple_obj.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_simple_obj.o ../ca/ca_simple_obj.cpp

${OBJECTDIR}/_ext/43900685/ca.o: ../ca/ca.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca.o ../ca/ca.cpp

${OBJECTDIR}/_ext/2119092129/nessie.o: ../crypt/nessie.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2119092129
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/2119092129/nessie.o ../crypt/nessie.cpp

${OBJECTDIR}/_ext/43900685/ca_strx.o: ../ca/ca_strx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_strx.o ../ca/ca_strx.cpp

${OBJECTDIR}/_ext/43900685/_initterm.o: ../ca/_initterm.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/_initterm.o ../ca/_initterm.cpp

${OBJECTDIR}/_ext/1295684859/crctable.o: ../bsdiff/crctable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/crctable.o ../bsdiff/crctable.cpp

${OBJECTDIR}/_ext/583780700/ca_os_process.o: ../solaris/ca_os_process.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_process.o ../solaris/ca_os_process.cpp

${OBJECTDIR}/_ext/43900685/ca_strw.o: ../ca/ca_strw.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_strw.o ../ca/ca_strw.cpp

${OBJECTDIR}/_ext/43900685/ca_mem.o: ../ca/ca_mem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_mem.o ../ca/ca_mem.cpp

${OBJECTDIR}/_ext/416166309/windows_thread.o: ../cross/windows/windows_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/416166309
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/416166309/windows_thread.o ../cross/windows/windows_thread.cpp

${OBJECTDIR}/_ext/43900685/ca_heap.o: ../ca/ca_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_heap.o ../ca/ca_heap.cpp

${OBJECTDIR}/_ext/43900685/ca_version.o: ../ca/ca_version.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_version.o ../ca/ca_version.cpp

${OBJECTDIR}/_ext/1295684859/blocksort.o: ../bsdiff/blocksort.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/blocksort.o ../bsdiff/blocksort.cpp

${OBJECTDIR}/_ext/43900685/ca_debug.o: ../ca/ca_debug.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_debug.o ../ca/ca_debug.cpp

${OBJECTDIR}/_ext/2111841970/simple_tap.o: ../simple_ui/simple_tap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111841970
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/2111841970/simple_tap.o ../simple_ui/simple_tap.cpp

${OBJECTDIR}/_ext/2111841970/simple_ui.o: ../simple_ui/simple_ui.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111841970
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/2111841970/simple_ui.o ../simple_ui/simple_ui.cpp

${OBJECTDIR}/_ext/583780700/ca_os_win_base.o: ../solaris/ca_os_win_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_win_base.o ../solaris/ca_os_win_base.cpp

${OBJECTDIR}/_ext/43900685/ca_file_spa.o: ../ca/ca_file_spa.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_file_spa.o ../ca/ca_file_spa.cpp

${OBJECTDIR}/_ext/43901075/os_process.o: ../os/os_process.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43901075
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43901075/os_process.o ../os/os_process.cpp

${OBJECTDIR}/_ext/583780700/ca_os_simple_brush.o: ../solaris/ca_os_simple_brush.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_simple_brush.o ../solaris/ca_os_simple_brush.cpp

${OBJECTDIR}/_ext/43900685/ca_str.o: ../ca/ca_str.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_str.o ../ca/ca_str.cpp

${OBJECTDIR}/_ext/1360937173/spa_installer.o: ../spa/spa_installer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_installer.o ../spa/spa_installer.cpp

${OBJECTDIR}/_ext/1360937173/spa_trace.o: ../spa/spa_trace.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_trace.o ../spa/spa_trace.cpp

${OBJECTDIR}/_ext/1295684859/compress.o: ../bsdiff/compress.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/compress.o ../bsdiff/compress.cpp

${OBJECTDIR}/_ext/2111841970/simple_edit_box.o: ../simple_ui/simple_edit_box.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111841970
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/2111841970/simple_edit_box.o ../simple_ui/simple_edit_box.cpp

${OBJECTDIR}/_ext/43900685/ca_verisimple_string.o: ../ca/ca_verisimple_string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_verisimple_string.o ../ca/ca_verisimple_string.cpp

${OBJECTDIR}/_ext/43900685/ca_geometric_types.o: ../ca/ca_geometric_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_geometric_types.o ../ca/ca_geometric_types.cpp

${OBJECTDIR}/_ext/2119092129/crypt.o: ../crypt/crypt.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2119092129
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/2119092129/crypt.o ../crypt/crypt.cpp

${OBJECTDIR}/_ext/1328484458/ansios_thread.o: ../ansios/ansios_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_thread.o ../ansios/ansios_thread.cpp

${OBJECTDIR}/_ext/43900685/ca_xmlite.o: ../ca/ca_xmlite.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_xmlite.o ../ca/ca_xmlite.cpp

${OBJECTDIR}/_ext/43900685/ca_simple_memory.o: ../ca/ca_simple_memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_simple_memory.o ../ca/ca_simple_memory.cpp

${OBJECTDIR}/_ext/43900685/ca_file_watcher.o: ../ca/ca_file_watcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_file_watcher.o ../ca/ca_file_watcher.cpp

${OBJECTDIR}/_ext/1360937173/spa_login.o: ../spa/spa_login.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_login.o ../spa/spa_login.cpp

${OBJECTDIR}/_ext/583780700/ca_os_file_watcher.o: ../solaris/ca_os_file_watcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_file_watcher.o ../solaris/ca_os_file_watcher.cpp

${OBJECTDIR}/_ext/1295684859/huffman.o: ../bsdiff/huffman.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/huffman.o ../bsdiff/huffman.cpp

${OBJECTDIR}/_ext/1295684859/randtable.o: ../bsdiff/randtable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/randtable.o ../bsdiff/randtable.cpp

${OBJECTDIR}/_ext/9007153/hotplugin_container_launcher.o: ../hotplugin/hotplugin_container_launcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/9007153
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/9007153/hotplugin_container_launcher.o ../hotplugin/hotplugin_container_launcher.cpp

${OBJECTDIR}/_ext/1295684859/decompress.o: ../bsdiff/decompress.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/decompress.o ../bsdiff/decompress.cpp

${OBJECTDIR}/_ext/1328484458/ansios_file_std.o: ../ansios/ansios_file_std.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_file_std.o ../ansios/ansios_file_std.cpp

${OBJECTDIR}/_ext/1295684859/bsdiff.o: ../bsdiff/bsdiff.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/bsdiff.o ../bsdiff/bsdiff.cpp

${OBJECTDIR}/_ext/43900685/ca_file_watcher_impl.o: ../ca/ca_file_watcher_impl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_file_watcher_impl.o ../ca/ca_file_watcher_impl.cpp

${OBJECTDIR}/_ext/43900685/ca_vsstringtow.o: ../ca/ca_vsstringtow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_vsstringtow.o ../ca/ca_vsstringtow.cpp

${OBJECTDIR}/_ext/583780700/ca_os_small_ipca_channel.o: ../solaris/ca_os_small_ipca_channel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_small_ipca_channel.o ../solaris/ca_os_small_ipca_channel.cpp

${OBJECTDIR}/_ext/583780700/ca_os_simple_path.o: ../solaris/ca_os_simple_path.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_simple_path.o ../solaris/ca_os_simple_path.cpp

${OBJECTDIR}/_ext/1328484458/ansios_cross_win_file.o: ../ansios/ansios_cross_win_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_cross_win_file.o ../ansios/ansios_cross_win_file.cpp

${OBJECTDIR}/_ext/43900685/ca_simple_shell_launcher.o: ../ca/ca_simple_shell_launcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_simple_shell_launcher.o ../ca/ca_simple_shell_launcher.cpp

${OBJECTDIR}/_ext/43900685/ca_international.o: ../ca/ca_international.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_international.o ../ca/ca_international.cpp

${OBJECTDIR}/_ext/1360937173/spa_plugin.o: ../spa/spa_plugin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_plugin.o ../spa/spa_plugin.cpp

${OBJECTDIR}/_ext/583780700/ca_os_http_lib.o: ../solaris/ca_os_http_lib.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_http_lib.o ../solaris/ca_os_http_lib.cpp

${OBJECTDIR}/_ext/1328484458/ansios_cross_win.o: ../ansios/ansios_cross_win.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_cross_win.o ../ansios/ansios_cross_win.cpp

${OBJECTDIR}/_ext/43900685/ca_window_graphics.o: ../ca/ca_window_graphics.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_window_graphics.o ../ca/ca_window_graphics.cpp

${OBJECTDIR}/_ext/1684649001/simple_path.o: ../simple_graphics/simple_path.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1684649001
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1684649001/simple_path.o ../simple_graphics/simple_path.cpp

${OBJECTDIR}/_ext/1360937173/spa_main.o: ../spa/spa_main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_main.o ../spa/spa_main.cpp

${OBJECTDIR}/_ext/43900685/ca_small_ipca_channel.o: ../ca/ca_small_ipca_channel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_small_ipca_channel.o ../ca/ca_small_ipca_channel.cpp

${OBJECTDIR}/_ext/43901075/os_thread.o: ../os/os_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43901075
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43901075/os_thread.o ../os/os_thread.cpp

${OBJECTDIR}/_ext/43900685/ca_dir2.o: ../ca/ca_dir2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_dir2.o ../ca/ca_dir2.cpp

${OBJECTDIR}/_ext/43900685/ca_integer_to_string.o: ../ca/ca_integer_to_string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_integer_to_string.o ../ca/ca_integer_to_string.cpp

${OBJECTDIR}/_ext/583780700/ca_os_window.o: ../solaris/ca_os_window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_window.o ../solaris/ca_os_window.cpp

${OBJECTDIR}/_ext/43901075/os_binreloc.o: ../os/os_binreloc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43901075
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43901075/os_binreloc.o ../os/os_binreloc.cpp

${OBJECTDIR}/_ext/583780700/ca_os_simple_font.o: ../solaris/ca_os_simple_font.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_simple_font.o ../solaris/ca_os_simple_font.cpp

${OBJECTDIR}/_ext/43900685/ca_file_watcher_listener_thread.o: ../ca/ca_file_watcher_listener_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_file_watcher_listener_thread.o ../ca/ca_file_watcher_listener_thread.cpp

${OBJECTDIR}/_ext/1360937173/spa_spa.o: ../spa/spa_spa.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_spa.o ../spa/spa_spa.cpp

${OBJECTDIR}/_ext/583780700/ca_os_library.o: ../solaris/ca_os_library.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_library.o ../solaris/ca_os_library.cpp

${OBJECTDIR}/_ext/583780700/ca_os_cross_win_file.o: ../solaris/ca_os_cross_win_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_cross_win_file.o ../solaris/ca_os_cross_win_file.cpp

${OBJECTDIR}/_ext/1360937173/spa_cube_run.o: ../spa/spa_cube_run.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_cube_run.o ../spa/spa_cube_run.cpp

${OBJECTDIR}/_ext/1295684859/bzlib.o: ../bsdiff/bzlib.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/bzlib.o ../bsdiff/bzlib.cpp

${OBJECTDIR}/_ext/43900685/ca_file.o: ../ca/ca_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_file.o ../ca/ca_file.cpp

${OBJECTDIR}/_ext/43901075/os_http.o: ../os/os_http.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43901075
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43901075/os_http.o ../os/os_http.cpp

${OBJECTDIR}/_ext/583780700/ca_os_window_cairo.o: ../solaris/ca_os_window_cairo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_window_cairo.o ../solaris/ca_os_window_cairo.cpp

${OBJECTDIR}/_ext/43900685/ca_user.o: ../ca/ca_user.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_user.o ../ca/ca_user.cpp

${OBJECTDIR}/_ext/43900685/ca_c.o: ../ca/ca_c.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_c.o ../ca/ca_c.cpp

${OBJECTDIR}/_ext/43900685/ca_std_file.o: ../ca/ca_std_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_std_file.o ../ca/ca_std_file.cpp

${OBJECTDIR}/_ext/43900685/ca_conv.o: ../ca/ca_conv.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_conv.o ../ca/ca_conv.cpp

${OBJECTDIR}/_ext/1295684859/main_bspatch.o: ../bsdiff/main_bspatch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1295684859
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1295684859/main_bspatch.o ../bsdiff/main_bspatch.cpp

${OBJECTDIR}/_ext/43900685/ca_simple_critical_section.o: ../ca/ca_simple_critical_section.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_simple_critical_section.o ../ca/ca_simple_critical_section.cpp

${OBJECTDIR}/_ext/416166309/windows_user.o: ../cross/windows/windows_user.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/416166309
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/416166309/windows_user.o ../cross/windows/windows_user.cpp

${OBJECTDIR}/_ext/583780700/ca_os_simple_shell_launcher.o: ../solaris/ca_os_simple_shell_launcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_simple_shell_launcher.o ../solaris/ca_os_simple_shell_launcher.cpp

${OBJECTDIR}/_ext/1360937173/spa_http.o: ../spa/spa_http.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_http.o ../spa/spa_http.cpp

${OBJECTDIR}/_ext/1360937173/spa_boot.o: ../spa/spa_boot.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_boot.o ../spa/spa_boot.cpp

${OBJECTDIR}/_ext/583780700/ca_os_launcher.o: ../solaris/ca_os_launcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_launcher.o ../solaris/ca_os_launcher.cpp

${OBJECTDIR}/_ext/583780700/ca_os_display.o: ../solaris/ca_os_display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_display.o ../solaris/ca_os_display.cpp

${OBJECTDIR}/_ext/1360937173/spa_bz.o: ../spa/spa_bz.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_bz.o ../spa/spa_bz.cpp

${OBJECTDIR}/_ext/583780700/ca_os_thread.o: ../solaris/ca_os_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_thread.o ../solaris/ca_os_thread.cpp

${OBJECTDIR}/_ext/43900685/ca_simple_mutex.o: ../ca/ca_simple_mutex.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_simple_mutex.o ../ca/ca_simple_mutex.cpp

${OBJECTDIR}/_ext/1360937173/spa_window.o: ../spa/spa_window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_window.o ../spa/spa_window.cpp

${OBJECTDIR}/_ext/583780700/ca_os_http.o: ../solaris/ca_os_http.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_http.o ../solaris/ca_os_http.cpp

${OBJECTDIR}/_ext/583780700/ca_os_simple_pen.o: ../solaris/ca_os_simple_pen.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_simple_pen.o ../solaris/ca_os_simple_pen.cpp

${OBJECTDIR}/_ext/583780700/ca_os_simple_bitmap.o: ../solaris/ca_os_simple_bitmap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_simple_bitmap.o ../solaris/ca_os_simple_bitmap.cpp

${OBJECTDIR}/_ext/43900685/ca_mutex_lock.o: ../ca/ca_mutex_lock.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_mutex_lock.o ../ca/ca_mutex_lock.cpp

${OBJECTDIR}/_ext/43900685/ca_argcargv.o: ../ca/ca_argcargv.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_argcargv.o ../ca/ca_argcargv.cpp

${OBJECTDIR}/_ext/43900685/ca_template.o: ../ca/ca_template.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_template.o ../ca/ca_template.cpp

${OBJECTDIR}/_ext/583780700/ca_os_simple_graphics.o: ../solaris/ca_os_simple_graphics.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_simple_graphics.o ../solaris/ca_os_simple_graphics.cpp

${OBJECTDIR}/_ext/1328484458/ansios_file.o: ../ansios/ansios_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_file.o ../ansios/ansios_file.cpp

${OBJECTDIR}/_ext/43900685/ca_strdup.o: ../ca/ca_strdup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_strdup.o ../ca/ca_strdup.cpp

${OBJECTDIR}/_ext/2111841970/simple_label.o: ../simple_ui/simple_label.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111841970
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/2111841970/simple_label.o ../simple_ui/simple_label.cpp

${OBJECTDIR}/_ext/583780700/ca_os_cairo_keep.o: ../solaris/ca_os_cairo_keep.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_cairo_keep.o ../solaris/ca_os_cairo_keep.cpp

${OBJECTDIR}/_ext/583780700/ca_os_message_loop.o: ../solaris/ca_os_message_loop.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_message_loop.o ../solaris/ca_os_message_loop.cpp

${OBJECTDIR}/_ext/583780700/ca_os_cross_win_gdi.o: ../solaris/ca_os_cross_win_gdi.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_cross_win_gdi.o ../solaris/ca_os_cross_win_gdi.cpp

${OBJECTDIR}/_ext/583780700/ca_os_lock.o: ../solaris/ca_os_lock.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_lock.o ../solaris/ca_os_lock.cpp

${OBJECTDIR}/_ext/43900685/ca_url.o: ../ca/ca_url.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_url.o ../ca/ca_url.cpp

${OBJECTDIR}/_ext/43900685/ca_math.o: ../ca/ca_math.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_math.o ../ca/ca_math.cpp

${OBJECTDIR}/_ext/43900685/ca_md5.o: ../ca/ca_md5.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_md5.o ../ca/ca_md5.cpp

${OBJECTDIR}/_ext/1360937173/spa_small_bell.o: ../spa/spa_small_bell.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_small_bell.o ../spa/spa_small_bell.cpp

${OBJECTDIR}/_ext/43900685/ca_simple_array.o: ../ca/ca_simple_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_simple_array.o ../ca/ca_simple_array.cpp

${OBJECTDIR}/_ext/1360937173/spa_canvas.o: ../spa/spa_canvas.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_canvas.o ../spa/spa_canvas.cpp

${OBJECTDIR}/_ext/43900685/ca_sprintf.o: ../ca/ca_sprintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_sprintf.o ../ca/ca_sprintf.cpp

${OBJECTDIR}/_ext/583780700/ca_os_process_pid.o: ../solaris/ca_os_process_pid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/583780700/ca_os_process_pid.o ../solaris/ca_os_process_pid.cpp

${OBJECTDIR}/_ext/43900685/ca_base64.o: ../ca/ca_base64.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_base64.o ../ca/ca_base64.cpp

${OBJECTDIR}/_ext/2119092129/whirpool.o: ../crypt/whirpool.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2119092129
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/2119092129/whirpool.o ../crypt/whirpool.cpp

${OBJECTDIR}/_ext/43900685/ca_cpu_architecture.o: ../ca/ca_cpu_architecture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43900685
	$(COMPILE.cc) -g -I../../../.. -I../../.. -I../.. -I.. -KPIC  -o ${OBJECTDIR}/_ext/43900685/ca_cpu_architecture.o ../ca/ca_cpu_architecture.cpp

# Subprojects
.build-subprojects:
	cd ../../c/_c.sol && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/OracleSolarisStudio-Solaris-x86/libca.sol.so
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:
	cd ../../c/_c.sol && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

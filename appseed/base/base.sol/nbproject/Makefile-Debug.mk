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
CND_PLATFORM=OracleSolarisStudio_12.3-Solaris-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1422879424/exception_os.o \
	${OBJECTDIR}/_ext/761140800/base_departament.o \
	${OBJECTDIR}/_ext/1360937314/str_from_integer.o \
	${OBJECTDIR}/_ext/761014165/file_stream.o \
	${OBJECTDIR}/_ext/761014165/file_plain_text_stream_base.o \
	${OBJECTDIR}/_ext/761014165/file_input_stream.o \
	${OBJECTDIR}/_ext/1422879424/exception_not_licensed.o \
	${OBJECTDIR}/_ext/732521037/collection_map_misc.o \
	${OBJECTDIR}/_ext/732521037/collection_numeric_array.o \
	${OBJECTDIR}/_ext/761140800/base_allocate_var.o \
	${OBJECTDIR}/_ext/1893554344/primitive_id.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_socket_event.o \
	${OBJECTDIR}/_ext/761140800/base_assert.o \
	${OBJECTDIR}/_ext/761140800/base_element.o \
	${OBJECTDIR}/_ext/761014165/file_reader.o \
	${OBJECTDIR}/_ext/732521037/collection_pointer_list.o \
	${OBJECTDIR}/_ext/761014165/file_c.o \
	${OBJECTDIR}/_ext/1422879424/exception_engine.o \
	${OBJECTDIR}/_ext/1422879424/exception_invalid_index.o \
	${OBJECTDIR}/_ext/760557894/user_create_context.o \
	${OBJECTDIR}/_ext/2111058971/linux_thread.o \
	${OBJECTDIR}/_ext/761140800/base_application.o \
	${OBJECTDIR}/_ext/1360941896/xml_edit.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_mutex.o \
	${OBJECTDIR}/_ext/1360941896/xml_attr.o \
	${OBJECTDIR}/_ext/732521037/collection_sort.o \
	${OBJECTDIR}/_ext/1893554344/primitive_factory.o \
	${OBJECTDIR}/_ext/1360937314/str_dup.o \
	${OBJECTDIR}/_ext/761014165/file_output_stream.o \
	${OBJECTDIR}/_ext/1328484458/ansios_multithreading.o \
	${OBJECTDIR}/_ext/761140800/base_allocate_base_heap.o \
	${OBJECTDIR}/_ext/1360937173/spa_file.o \
	${OBJECTDIR}/_ext/761014165/file_byte_output_stream.o \
	${OBJECTDIR}/_ext/1392566472/windows_locale.o \
	${OBJECTDIR}/_ext/1360937314/str_strx.o \
	${OBJECTDIR}/_ext/1893554344/primitive_data_container.o \
	${OBJECTDIR}/_ext/1893554344/primitive_edit.o \
	${OBJECTDIR}/_ext/761014165/file_plain_text_stream_string_buffer.o \
	${OBJECTDIR}/_ext/1360941896/xml_property_exchange.o \
	${OBJECTDIR}/_ext/1328484458/ansios_http.o \
	${OBJECTDIR}/_ext/1360937314/str_base64.o \
	${OBJECTDIR}/_ext/1893554344/primitive_property.o \
	${OBJECTDIR}/_ext/1422879424/exception_resource.o \
	${OBJECTDIR}/_ext/1893554344/primitive_shared_memory.o \
	${OBJECTDIR}/_ext/1289935841/geometry_point.o \
	${OBJECTDIR}/_ext/1360941896/xml_data.o \
	${OBJECTDIR}/_ext/1893554344/primitive_request_interface.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_retry_single_lock.o \
	${OBJECTDIR}/_ext/1893554344/primitive_id_space.o \
	${OBJECTDIR}/_ext/761014165/file_string_buffer.o \
	${OBJECTDIR}/_ext/732521037/collection_rect_array.o \
	${OBJECTDIR}/_ext/1422879424/exception_not_supported.o \
	${OBJECTDIR}/_ext/1422879424/exception_last_error.o \
	${OBJECTDIR}/_ext/2111058971/linux_time.o \
	${OBJECTDIR}/_ext/1360932046/net_net.o \
	${OBJECTDIR}/_ext/1360937314/str_c.o \
	${OBJECTDIR}/_ext/1422879424/exception_base.o \
	${OBJECTDIR}/_ext/1893554344/primitive_property_set.o \
	${OBJECTDIR}/_ext/1893554344/primitive_create_context.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_wait_result.o \
	${OBJECTDIR}/_ext/1422879424/exception_call_stack.o \
	${OBJECTDIR}/_ext/1422879424/exception_error.o \
	${OBJECTDIR}/_ext/1422879424/exception_dump_output.o \
	${OBJECTDIR}/_ext/1893554344/primitive_data.o \
	${OBJECTDIR}/_ext/761140800/base_allocate_base.o \
	${OBJECTDIR}/_ext/1360937314/str_to_integer.o \
	${OBJECTDIR}/_ext/761140800/base_heap.o \
	${OBJECTDIR}/_ext/43901075/os_file.o \
	${OBJECTDIR}/_ext/732521037/collection_key_sort_array.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_retry_multi_lock.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_synch_lock.o \
	${OBJECTDIR}/_ext/1422879424/exception_interface_only.o \
	${OBJECTDIR}/_ext/1422879424/exception_hresult.o \
	${OBJECTDIR}/_ext/1893554344/primitive_application_bias.o \
	${OBJECTDIR}/_ext/1422879424/exception_void_implementation.o \
	${OBJECTDIR}/_ext/1360941896/xml_input_tree.o \
	${OBJECTDIR}/_ext/732521037/collection_comparable_array.o \
	${OBJECTDIR}/_ext/732521037/collection_2d_array.o \
	${OBJECTDIR}/_ext/760557894/user_base_interaction.o \
	${OBJECTDIR}/_ext/1893554344/primitive_signal.o \
	${OBJECTDIR}/_ext/732521037/collection_string_sort_array.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_manual_reset_event.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_event_collection.o \
	${OBJECTDIR}/_ext/761014165/file_writer_flush.o \
	${OBJECTDIR}/_ext/761140800/base_system.o \
	${OBJECTDIR}/_ext/1893554344/primitive_memory.o \
	${OBJECTDIR}/_ext/1360937314/str_ch_class.o \
	${OBJECTDIR}/_ext/732521037/collection_string_to_string_map.o \
	${OBJECTDIR}/_ext/1422879424/exception_user.o \
	${OBJECTDIR}/_ext/761014165/file_plain_text_input_stream.o \
	${OBJECTDIR}/_ext/732521037/collection_id_array.o \
	${OBJECTDIR}/_ext/761014165/file_stream_buffer_base.o \
	${OBJECTDIR}/_ext/732521037/collection_stringa.o \
	${OBJECTDIR}/_ext/1392566472/windows_error.o \
	${OBJECTDIR}/_ext/1360941896/xml_var_exchange.o \
	${OBJECTDIR}/_ext/1360937314/str_core.o \
	${OBJECTDIR}/_ext/1422879424/exception_invalid_argument.o \
	${OBJECTDIR}/_ext/1360941896/xml_importable.o \
	${OBJECTDIR}/_ext/1893554344/primitive_virtual_memory.o \
	${OBJECTDIR}/_ext/1422879424/exception_invalid_character.o \
	${OBJECTDIR}/_ext/43901075/os_process.o \
	${OBJECTDIR}/_ext/732521037/collection_stringl.o \
	${OBJECTDIR}/_ext/1422879424/exception_runtime_error.o \
	${OBJECTDIR}/_ext/732521037/collection_point_array.o \
	${OBJECTDIR}/_ext/1360937173/spa_trace.o \
	${OBJECTDIR}/_ext/1360937314/str_verisimple_wstring.o \
	${OBJECTDIR}/_ext/2111058971/linux_os.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_critical_section.o \
	${OBJECTDIR}/_ext/1360941896/xml_base_array.o \
	${OBJECTDIR}/_ext/1893554344/primitive_var.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_condition.o \
	${OBJECTDIR}/_ext/1360937314/str_ch.o \
	${OBJECTDIR}/_ext/1360941896/xml_exportable.o \
	${OBJECTDIR}/_ext/761014165/file_stream_base.o \
	${OBJECTDIR}/_ext/1328484458/ansios_thread.o \
	${OBJECTDIR}/_ext/761014165/file_binary_buffer.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_event.o \
	${OBJECTDIR}/_ext/1360937314/str_wtostring.o \
	${OBJECTDIR}/_ext/761140800/base_allocate_mid_big.o \
	${OBJECTDIR}/_ext/1422879424/exception.o \
	${OBJECTDIR}/_ext/761140800/base_conv.o \
	${OBJECTDIR}/_ext/1422879424/exception_memory.o \
	${OBJECTDIR}/_ext/1392566472/windows_crt.o \
	${OBJECTDIR}/_ext/761014165/file_byte_stream_memory_buffer.o \
	${OBJECTDIR}/_ext/1893554344/primitive_type.o \
	${OBJECTDIR}/_ext/761014165/file_exception.o \
	${OBJECTDIR}/_ext/732521037/collection_class_sort_array.o \
	${OBJECTDIR}/_ext/2111058971/linux_cross_win_file.o \
	${OBJECTDIR}/_ext/761014165/file_simple_binary_buffer.o \
	${OBJECTDIR}/_ext/1237618410/datetime_time.o \
	${OBJECTDIR}/_ext/1360937314/str_international.o \
	${OBJECTDIR}/_ext/1893554344/primitive_command_thread.o \
	${OBJECTDIR}/_ext/1328484458/ansios_file_std.o \
	${OBJECTDIR}/_ext/761140800/base.o \
	${OBJECTDIR}/_ext/1360941896/xml_parse_info.o \
	${OBJECTDIR}/_ext/1360941896/xml_output_tree.o \
	${OBJECTDIR}/_ext/761014165/file_plain_text_stream.o \
	${OBJECTDIR}/_ext/1422879424/exception_dump.o \
	${OBJECTDIR}/_ext/1360937314/str_hex.o \
	${OBJECTDIR}/_ext/1328484458/ansios_cross_win_file.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_single_lock.o \
	${OBJECTDIR}/_ext/1893554344/primitive_memory_base.o \
	${OBJECTDIR}/_ext/1422879424/exception_standard_translator.o \
	${OBJECTDIR}/_ext/1360941896/xml_tree_base.o \
	${OBJECTDIR}/_ext/732521037/collection_object_list.o \
	${OBJECTDIR}/_ext/1422879424/exception_debug.o \
	${OBJECTDIR}/_ext/761140800/base_checked.o \
	${OBJECTDIR}/_ext/1422879424/exception_simple.o \
	${OBJECTDIR}/_ext/1422879424/exception_not_implemented.o \
	${OBJECTDIR}/_ext/761140800/base_departament_container.o \
	${OBJECTDIR}/_ext/1289935841/geometry_types.o \
	${OBJECTDIR}/_ext/1328484458/ansios_cross_win.o \
	${OBJECTDIR}/_ext/1392566472/windows_time.o \
	${OBJECTDIR}/_ext/761014165/file_byte_input_stream_binary_buffer.o \
	${OBJECTDIR}/_ext/1893554344/primitive_interlocked_long.o \
	${OBJECTDIR}/_ext/761014165/file_stream_buffer.o \
	${OBJECTDIR}/_ext/732521037/collection_string_list.o \
	${OBJECTDIR}/_ext/1893554344/primitive_command.o \
	${OBJECTDIR}/_ext/1893554344/primitive_bit.o \
	${OBJECTDIR}/_ext/1392566472/windows_user.o \
	${OBJECTDIR}/_ext/761014165/file_writer.o \
	${OBJECTDIR}/_ext/1392566472/windows.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_sync_object.o \
	${OBJECTDIR}/_ext/43901075/os_thread.o \
	${OBJECTDIR}/_ext/1360937314/str_stringtow.o \
	${OBJECTDIR}/_ext/760813065/math_math.o \
	${OBJECTDIR}/_ext/1422879424/exception_todo.o \
	${OBJECTDIR}/_ext/1360941896/xml_entity.o \
	${OBJECTDIR}/_ext/1392566472/windows_thread.o \
	${OBJECTDIR}/_ext/1893554344/primitive_memory_c.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_event_base.o \
	${OBJECTDIR}/_ext/1360937314/str_tokenizer.o \
	${OBJECTDIR}/_ext/1893554344/primitive_interlocked_long_pulse.o \
	${OBJECTDIR}/_ext/1360932046/net_url_departament.o \
	${OBJECTDIR}/_ext/761014165/file_plain_text_output_stream_string_buffer.o \
	${OBJECTDIR}/_ext/761014165/file_byte_output_stream_binary_buffer.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_core.o \
	${OBJECTDIR}/_ext/1629396920/comparison_md5.o \
	${OBJECTDIR}/_ext/761140800/base_template.o \
	${OBJECTDIR}/_ext/761140800/base_plex_heap.o \
	${OBJECTDIR}/_ext/43901075/os_http.o \
	${OBJECTDIR}/_ext/2111058971/linux_window.o \
	${OBJECTDIR}/_ext/1893554344/primitive_memory_container.o \
	${OBJECTDIR}/_ext/1360937314/str_string.o \
	${OBJECTDIR}/_ext/1360937314/str_istring.o \
	${OBJECTDIR}/_ext/761140800/base_thread.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_multi_lock.o \
	${OBJECTDIR}/_ext/761014165/file_composite.o \
	${OBJECTDIR}/_ext/761014165/file_byte_input_stream.o \
	${OBJECTDIR}/_ext/761014165/file_seekable.o \
	${OBJECTDIR}/_ext/761140800/base_muldiv64.o \
	${OBJECTDIR}/_ext/1328484458/ansios_cross_windows_user.o \
	${OBJECTDIR}/_ext/1328484458/ansios_http_lib.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_file_change_event.o \
	${OBJECTDIR}/_ext/1360937314/str_strw.o \
	${OBJECTDIR}/_ext/1360941896/xml_document.o \
	${OBJECTDIR}/_ext/761140800/base_plex.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_service_base.o \
	${OBJECTDIR}/_ext/1360937314/str_manager.o \
	${OBJECTDIR}/_ext/732521037/collection_var_array.o \
	${OBJECTDIR}/_ext/1893554344/primitive_request_signal.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_waitable.o \
	${OBJECTDIR}/_ext/1289935841/geometry_rect.o \
	${OBJECTDIR}/_ext/1422879424/exception_installing.o \
	${OBJECTDIR}/_ext/761014165/file_dir.o \
	${OBJECTDIR}/_ext/583780700/c_os.o \
	${OBJECTDIR}/_ext/1422879424/exception_invalid_handle.o \
	${OBJECTDIR}/_ext/1422879424/exception_temporary.o \
	${OBJECTDIR}/_ext/1893554344/primitive_data_listener.o \
	${OBJECTDIR}/_ext/761140800/base_fixed_alloc.o \
	${OBJECTDIR}/_ext/1360941896/xml_xmlite.o \
	${OBJECTDIR}/_ext/1360937314/str_format.o \
	${OBJECTDIR}/_ext/761014165/file_byte_stream.o \
	${OBJECTDIR}/_ext/1328484458/ansios_file.o \
	${OBJECTDIR}/_ext/2111058971/linux_c.o \
	${OBJECTDIR}/_ext/1422879424/exception_archive_exception.o \
	${OBJECTDIR}/_ext/1422879424/exception_dump_floating_point.o \
	${OBJECTDIR}/_ext/761014165/file_memory_buffer.o \
	${OBJECTDIR}/_ext/1237618410/datetime_duration.o \
	${OBJECTDIR}/_ext/732521037/collection_bit_array.o \
	${OBJECTDIR}/_ext/761140800/base_allocate_system_heap.o \
	${OBJECTDIR}/_ext/1893554344/primitive_command_line.o \
	${OBJECTDIR}/_ext/732521037/collection_array.o \
	${OBJECTDIR}/_ext/1360941896/xml_tree_schema.o \
	${OBJECTDIR}/_ext/1629396920/comparison_var_strict.o \
	${OBJECTDIR}/_ext/1893554344/primitive_object.o \
	${OBJECTDIR}/_ext/761140800/base_root.o \
	${OBJECTDIR}/_ext/1422879424/exception_archive.o \
	${OBJECTDIR}/_ext/1422879424/exception_VMSException.o \
	${OBJECTDIR}/_ext/1360937314/str_str.o \
	${OBJECTDIR}/_ext/761014165/file_plain_text_stream_memory_buffer.o \
	${OBJECTDIR}/_ext/761014165/file_dir2.o \
	${OBJECTDIR}/_ext/1422879424/exception_operation_canceled.o \
	${OBJECTDIR}/_ext/732521037/collection_string_array.o \
	${OBJECTDIR}/_ext/2111058971/linux_debug.o \
	${OBJECTDIR}/_ext/1360941896/xml_node.o \
	${OBJECTDIR}/_ext/1360941896/xml_disp_option.o \
	${OBJECTDIR}/_ext/761140800/base_c.o \
	${OBJECTDIR}/_ext/1360937314/str_simple.o \
	${OBJECTDIR}/_ext/1422879424/exception_dump_context.o \
	${OBJECTDIR}/_ext/1422879424/exception_range_error.o \
	${OBJECTDIR}/_ext/1422879424/exception_io.o \
	${OBJECTDIR}/_ext/2111058971/linux_display.o \
	${OBJECTDIR}/_ext/1289935841/geometry_size.o \
	${OBJECTDIR}/_ext/1392566472/windows_shared_memory.o \
	${OBJECTDIR}/_ext/2111058971/linux_process.o \
	${OBJECTDIR}/_ext/1360941896/xml_xml.o \
	${OBJECTDIR}/_ext/761014165/file_plain_text_output_stream.o \
	${OBJECTDIR}/_ext/1422879424/exception_overflow_error.o \
	${OBJECTDIR}/_ext/1422879424/exception_not_installed.o \
	${OBJECTDIR}/_ext/1422879424/exception_exit.o \
	${OBJECTDIR}/_ext/1055495342/multithreading_semaphore.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-features=no%anachronisms,no%transitions,tmplife -features=extensions,tmplrefstatic,iddollar
CXXFLAGS=-features=no%anachronisms,no%transitions,tmplife -features=extensions,tmplrefstatic,iddollar

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbase.sol.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbase.sol.so: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -G -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbase.sol.so -KPIC -norunpath -h libbase.sol.so ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1422879424/exception_os.o: ../exception/exception_os.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_os.o ../exception/exception_os.cpp

${OBJECTDIR}/_ext/761140800/base_departament.o: ../base/base_departament.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_departament.o ../base/base_departament.cpp

${OBJECTDIR}/_ext/1360937314/str_from_integer.o: ../str/str_from_integer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_from_integer.o ../str/str_from_integer.cpp

${OBJECTDIR}/_ext/761014165/file_stream.o: ../file/file_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_stream.o ../file/file_stream.cpp

${OBJECTDIR}/_ext/761014165/file_plain_text_stream_base.o: ../file/file_plain_text_stream_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_plain_text_stream_base.o ../file/file_plain_text_stream_base.cpp

${OBJECTDIR}/_ext/761014165/file_input_stream.o: ../file/file_input_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_input_stream.o ../file/file_input_stream.cpp

${OBJECTDIR}/_ext/1422879424/exception_not_licensed.o: ../exception/exception_not_licensed.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_not_licensed.o ../exception/exception_not_licensed.cpp

${OBJECTDIR}/_ext/732521037/collection_map_misc.o: ../collection/collection_map_misc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_map_misc.o ../collection/collection_map_misc.cpp

${OBJECTDIR}/_ext/732521037/collection_numeric_array.o: ../collection/collection_numeric_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_numeric_array.o ../collection/collection_numeric_array.cpp

${OBJECTDIR}/_ext/761140800/base_allocate_var.o: ../base/base_allocate_var.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_allocate_var.o ../base/base_allocate_var.cpp

${OBJECTDIR}/_ext/1893554344/primitive_id.o: ../primitive/primitive_id.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_id.o ../primitive/primitive_id.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_socket_event.o: ../multithreading/multithreading_socket_event.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_socket_event.o ../multithreading/multithreading_socket_event.cpp

${OBJECTDIR}/_ext/761140800/base_assert.o: ../base/base_assert.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_assert.o ../base/base_assert.cpp

${OBJECTDIR}/_ext/761140800/base_element.o: ../base/base_element.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_element.o ../base/base_element.cpp

${OBJECTDIR}/_ext/761014165/file_reader.o: ../file/file_reader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_reader.o ../file/file_reader.cpp

${OBJECTDIR}/_ext/732521037/collection_pointer_list.o: ../collection/collection_pointer_list.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_pointer_list.o ../collection/collection_pointer_list.cpp

${OBJECTDIR}/_ext/761014165/file_c.o: ../file/file_c.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_c.o ../file/file_c.cpp

${OBJECTDIR}/_ext/1422879424/exception_engine.o: ../exception/exception_engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_engine.o ../exception/exception_engine.cpp

${OBJECTDIR}/_ext/1422879424/exception_invalid_index.o: ../exception/exception_invalid_index.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_invalid_index.o ../exception/exception_invalid_index.cpp

${OBJECTDIR}/_ext/760557894/user_create_context.o: ../user/user_create_context.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760557894
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/760557894/user_create_context.o ../user/user_create_context.cpp

${OBJECTDIR}/_ext/2111058971/linux_thread.o: ../linux/linux_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_thread.o ../linux/linux_thread.cpp

${OBJECTDIR}/_ext/761140800/base_application.o: ../base/base_application.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_application.o ../base/base_application.cpp

${OBJECTDIR}/_ext/1360941896/xml_edit.o: ../xml/xml_edit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_edit.o ../xml/xml_edit.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_mutex.o: ../multithreading/multithreading_mutex.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_mutex.o ../multithreading/multithreading_mutex.cpp

${OBJECTDIR}/_ext/1360941896/xml_attr.o: ../xml/xml_attr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_attr.o ../xml/xml_attr.cpp

${OBJECTDIR}/_ext/732521037/collection_sort.o: ../collection/collection_sort.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_sort.o ../collection/collection_sort.cpp

${OBJECTDIR}/_ext/1893554344/primitive_factory.o: ../primitive/primitive_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_factory.o ../primitive/primitive_factory.cpp

${OBJECTDIR}/_ext/1360937314/str_dup.o: ../str/str_dup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_dup.o ../str/str_dup.cpp

${OBJECTDIR}/_ext/761014165/file_output_stream.o: ../file/file_output_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_output_stream.o ../file/file_output_stream.cpp

${OBJECTDIR}/_ext/1328484458/ansios_multithreading.o: ../ansios/ansios_multithreading.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_multithreading.o ../ansios/ansios_multithreading.cpp

${OBJECTDIR}/_ext/761140800/base_allocate_base_heap.o: ../base/base_allocate_base_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_allocate_base_heap.o ../base/base_allocate_base_heap.cpp

${OBJECTDIR}/_ext/1360937173/spa_file.o: ../spa/spa_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_file.o ../spa/spa_file.cpp

${OBJECTDIR}/_ext/761014165/file_byte_output_stream.o: ../file/file_byte_output_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_byte_output_stream.o ../file/file_byte_output_stream.cpp

${OBJECTDIR}/_ext/1392566472/windows_locale.o: ../os/cross/windows/windows_locale.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1392566472
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1392566472/windows_locale.o ../os/cross/windows/windows_locale.cpp

${OBJECTDIR}/_ext/1360937314/str_strx.o: ../str/str_strx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_strx.o ../str/str_strx.cpp

${OBJECTDIR}/_ext/1893554344/primitive_data_container.o: ../primitive/primitive_data_container.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_data_container.o ../primitive/primitive_data_container.cpp

${OBJECTDIR}/_ext/1893554344/primitive_edit.o: ../primitive/primitive_edit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_edit.o ../primitive/primitive_edit.cpp

${OBJECTDIR}/_ext/761014165/file_plain_text_stream_string_buffer.o: ../file/file_plain_text_stream_string_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_plain_text_stream_string_buffer.o ../file/file_plain_text_stream_string_buffer.cpp

${OBJECTDIR}/_ext/1360941896/xml_property_exchange.o: ../xml/xml_property_exchange.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_property_exchange.o ../xml/xml_property_exchange.cpp

${OBJECTDIR}/_ext/1328484458/ansios_http.o: ../ansios/ansios_http.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_http.o ../ansios/ansios_http.cpp

${OBJECTDIR}/_ext/1360937314/str_base64.o: ../str/str_base64.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_base64.o ../str/str_base64.cpp

${OBJECTDIR}/_ext/1893554344/primitive_property.o: ../primitive/primitive_property.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_property.o ../primitive/primitive_property.cpp

${OBJECTDIR}/_ext/1422879424/exception_resource.o: ../exception/exception_resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_resource.o ../exception/exception_resource.cpp

${OBJECTDIR}/_ext/1893554344/primitive_shared_memory.o: ../primitive/primitive_shared_memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_shared_memory.o ../primitive/primitive_shared_memory.cpp

${OBJECTDIR}/_ext/1289935841/geometry_point.o: ../geometry/geometry_point.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1289935841
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1289935841/geometry_point.o ../geometry/geometry_point.cpp

${OBJECTDIR}/_ext/1360941896/xml_data.o: ../xml/xml_data.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_data.o ../xml/xml_data.cpp

${OBJECTDIR}/_ext/1893554344/primitive_request_interface.o: ../primitive/primitive_request_interface.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_request_interface.o ../primitive/primitive_request_interface.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_retry_single_lock.o: ../multithreading/multithreading_retry_single_lock.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_retry_single_lock.o ../multithreading/multithreading_retry_single_lock.cpp

${OBJECTDIR}/_ext/1893554344/primitive_id_space.o: ../primitive/primitive_id_space.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_id_space.o ../primitive/primitive_id_space.cpp

${OBJECTDIR}/_ext/761014165/file_string_buffer.o: ../file/file_string_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_string_buffer.o ../file/file_string_buffer.cpp

${OBJECTDIR}/_ext/732521037/collection_rect_array.o: ../collection/collection_rect_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_rect_array.o ../collection/collection_rect_array.cpp

${OBJECTDIR}/_ext/1422879424/exception_not_supported.o: ../exception/exception_not_supported.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_not_supported.o ../exception/exception_not_supported.cpp

${OBJECTDIR}/_ext/1422879424/exception_last_error.o: ../exception/exception_last_error.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_last_error.o ../exception/exception_last_error.cpp

${OBJECTDIR}/_ext/2111058971/linux_time.o: ../linux/linux_time.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_time.o ../linux/linux_time.cpp

${OBJECTDIR}/_ext/1360932046/net_net.o: ../net/net_net.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360932046
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360932046/net_net.o ../net/net_net.cpp

${OBJECTDIR}/_ext/1360937314/str_c.o: ../str/str_c.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_c.o ../str/str_c.cpp

${OBJECTDIR}/_ext/1422879424/exception_base.o: ../exception/exception_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_base.o ../exception/exception_base.cpp

${OBJECTDIR}/_ext/1893554344/primitive_property_set.o: ../primitive/primitive_property_set.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_property_set.o ../primitive/primitive_property_set.cpp

${OBJECTDIR}/_ext/1893554344/primitive_create_context.o: ../primitive/primitive_create_context.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_create_context.o ../primitive/primitive_create_context.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_wait_result.o: ../multithreading/multithreading_wait_result.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_wait_result.o ../multithreading/multithreading_wait_result.cpp

${OBJECTDIR}/_ext/1422879424/exception_call_stack.o: ../exception/exception_call_stack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_call_stack.o ../exception/exception_call_stack.cpp

${OBJECTDIR}/_ext/1422879424/exception_error.o: ../exception/exception_error.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_error.o ../exception/exception_error.cpp

${OBJECTDIR}/_ext/1422879424/exception_dump_output.o: ../exception/exception_dump_output.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_dump_output.o ../exception/exception_dump_output.cpp

${OBJECTDIR}/_ext/1893554344/primitive_data.o: ../primitive/primitive_data.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_data.o ../primitive/primitive_data.cpp

${OBJECTDIR}/_ext/761140800/base_allocate_base.o: ../base/base_allocate_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_allocate_base.o ../base/base_allocate_base.cpp

${OBJECTDIR}/_ext/1360937314/str_to_integer.o: ../str/str_to_integer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_to_integer.o ../str/str_to_integer.cpp

${OBJECTDIR}/_ext/761140800/base_heap.o: ../base/base_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_heap.o ../base/base_heap.cpp

${OBJECTDIR}/_ext/43901075/os_file.o: ../os/os_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43901075
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/43901075/os_file.o ../os/os_file.cpp

${OBJECTDIR}/_ext/732521037/collection_key_sort_array.o: ../collection/collection_key_sort_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_key_sort_array.o ../collection/collection_key_sort_array.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_retry_multi_lock.o: ../multithreading/multithreading_retry_multi_lock.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_retry_multi_lock.o ../multithreading/multithreading_retry_multi_lock.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_synch_lock.o: ../multithreading/multithreading_synch_lock.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_synch_lock.o ../multithreading/multithreading_synch_lock.cpp

${OBJECTDIR}/_ext/1422879424/exception_interface_only.o: ../exception/exception_interface_only.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_interface_only.o ../exception/exception_interface_only.cpp

${OBJECTDIR}/_ext/1422879424/exception_hresult.o: ../exception/exception_hresult.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_hresult.o ../exception/exception_hresult.cpp

${OBJECTDIR}/_ext/1893554344/primitive_application_bias.o: ../primitive/primitive_application_bias.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_application_bias.o ../primitive/primitive_application_bias.cpp

${OBJECTDIR}/_ext/1422879424/exception_void_implementation.o: ../exception/exception_void_implementation.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_void_implementation.o ../exception/exception_void_implementation.cpp

${OBJECTDIR}/_ext/1360941896/xml_input_tree.o: ../xml/xml_input_tree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_input_tree.o ../xml/xml_input_tree.cpp

${OBJECTDIR}/_ext/732521037/collection_comparable_array.o: ../collection/collection_comparable_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_comparable_array.o ../collection/collection_comparable_array.cpp

${OBJECTDIR}/_ext/732521037/collection_2d_array.o: ../collection/collection_2d_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_2d_array.o ../collection/collection_2d_array.cpp

${OBJECTDIR}/_ext/760557894/user_base_interaction.o: ../user/user_base_interaction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760557894
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/760557894/user_base_interaction.o ../user/user_base_interaction.cpp

${OBJECTDIR}/_ext/1893554344/primitive_signal.o: ../primitive/primitive_signal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_signal.o ../primitive/primitive_signal.cpp

${OBJECTDIR}/_ext/732521037/collection_string_sort_array.o: ../collection/collection_string_sort_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_string_sort_array.o ../collection/collection_string_sort_array.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_manual_reset_event.o: ../multithreading/multithreading_manual_reset_event.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_manual_reset_event.o ../multithreading/multithreading_manual_reset_event.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_event_collection.o: ../multithreading/multithreading_event_collection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_event_collection.o ../multithreading/multithreading_event_collection.cpp

${OBJECTDIR}/_ext/761014165/file_writer_flush.o: ../file/file_writer_flush.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_writer_flush.o ../file/file_writer_flush.cpp

${OBJECTDIR}/_ext/761140800/base_system.o: ../base/base_system.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_system.o ../base/base_system.cpp

${OBJECTDIR}/_ext/1893554344/primitive_memory.o: ../primitive/primitive_memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_memory.o ../primitive/primitive_memory.cpp

${OBJECTDIR}/_ext/1360937314/str_ch_class.o: ../str/str_ch_class.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_ch_class.o ../str/str_ch_class.cpp

${OBJECTDIR}/_ext/732521037/collection_string_to_string_map.o: ../collection/collection_string_to_string_map.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_string_to_string_map.o ../collection/collection_string_to_string_map.cpp

${OBJECTDIR}/_ext/1422879424/exception_user.o: ../exception/exception_user.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_user.o ../exception/exception_user.cpp

${OBJECTDIR}/_ext/761014165/file_plain_text_input_stream.o: ../file/file_plain_text_input_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_plain_text_input_stream.o ../file/file_plain_text_input_stream.cpp

${OBJECTDIR}/_ext/732521037/collection_id_array.o: ../collection/collection_id_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_id_array.o ../collection/collection_id_array.cpp

${OBJECTDIR}/_ext/761014165/file_stream_buffer_base.o: ../file/file_stream_buffer_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_stream_buffer_base.o ../file/file_stream_buffer_base.cpp

${OBJECTDIR}/_ext/732521037/collection_stringa.o: ../collection/collection_stringa.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_stringa.o ../collection/collection_stringa.cpp

${OBJECTDIR}/_ext/1392566472/windows_error.o: ../os/cross/windows/windows_error.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1392566472
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1392566472/windows_error.o ../os/cross/windows/windows_error.cpp

${OBJECTDIR}/_ext/1360941896/xml_var_exchange.o: ../xml/xml_var_exchange.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_var_exchange.o ../xml/xml_var_exchange.cpp

${OBJECTDIR}/_ext/1360937314/str_core.o: ../str/str_core.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_core.o ../str/str_core.cpp

${OBJECTDIR}/_ext/1422879424/exception_invalid_argument.o: ../exception/exception_invalid_argument.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_invalid_argument.o ../exception/exception_invalid_argument.cpp

${OBJECTDIR}/_ext/1360941896/xml_importable.o: ../xml/xml_importable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_importable.o ../xml/xml_importable.cpp

${OBJECTDIR}/_ext/1893554344/primitive_virtual_memory.o: ../primitive/primitive_virtual_memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_virtual_memory.o ../primitive/primitive_virtual_memory.cpp

${OBJECTDIR}/_ext/1422879424/exception_invalid_character.o: ../exception/exception_invalid_character.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_invalid_character.o ../exception/exception_invalid_character.cpp

${OBJECTDIR}/_ext/43901075/os_process.o: ../os/os_process.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43901075
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/43901075/os_process.o ../os/os_process.cpp

${OBJECTDIR}/_ext/732521037/collection_stringl.o: ../collection/collection_stringl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_stringl.o ../collection/collection_stringl.cpp

${OBJECTDIR}/_ext/1422879424/exception_runtime_error.o: ../exception/exception_runtime_error.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_runtime_error.o ../exception/exception_runtime_error.cpp

${OBJECTDIR}/_ext/732521037/collection_point_array.o: ../collection/collection_point_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_point_array.o ../collection/collection_point_array.cpp

${OBJECTDIR}/_ext/1360937173/spa_trace.o: ../spa/spa_trace.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937173
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937173/spa_trace.o ../spa/spa_trace.cpp

${OBJECTDIR}/_ext/1360937314/str_verisimple_wstring.o: ../str/str_verisimple_wstring.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_verisimple_wstring.o ../str/str_verisimple_wstring.cpp

${OBJECTDIR}/_ext/2111058971/linux_os.o: ../linux/linux_os.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_os.o ../linux/linux_os.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_critical_section.o: ../multithreading/multithreading_critical_section.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_critical_section.o ../multithreading/multithreading_critical_section.cpp

${OBJECTDIR}/_ext/1360941896/xml_base_array.o: ../xml/xml_base_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_base_array.o ../xml/xml_base_array.cpp

${OBJECTDIR}/_ext/1893554344/primitive_var.o: ../primitive/primitive_var.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_var.o ../primitive/primitive_var.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_condition.o: ../multithreading/multithreading_condition.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_condition.o ../multithreading/multithreading_condition.cpp

${OBJECTDIR}/_ext/1360937314/str_ch.o: ../str/str_ch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_ch.o ../str/str_ch.cpp

${OBJECTDIR}/_ext/1360941896/xml_exportable.o: ../xml/xml_exportable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_exportable.o ../xml/xml_exportable.cpp

${OBJECTDIR}/_ext/761014165/file_stream_base.o: ../file/file_stream_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_stream_base.o ../file/file_stream_base.cpp

${OBJECTDIR}/_ext/1328484458/ansios_thread.o: ../ansios/ansios_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_thread.o ../ansios/ansios_thread.cpp

${OBJECTDIR}/_ext/761014165/file_binary_buffer.o: ../file/file_binary_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_binary_buffer.o ../file/file_binary_buffer.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_event.o: ../multithreading/multithreading_event.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_event.o ../multithreading/multithreading_event.cpp

${OBJECTDIR}/_ext/1360937314/str_wtostring.o: ../str/str_wtostring.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_wtostring.o ../str/str_wtostring.cpp

${OBJECTDIR}/_ext/761140800/base_allocate_mid_big.o: ../base/base_allocate_mid_big.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_allocate_mid_big.o ../base/base_allocate_mid_big.cpp

${OBJECTDIR}/_ext/1422879424/exception.o: ../exception/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception.o ../exception/exception.cpp

${OBJECTDIR}/_ext/761140800/base_conv.o: ../base/base_conv.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_conv.o ../base/base_conv.cpp

${OBJECTDIR}/_ext/1422879424/exception_memory.o: ../exception/exception_memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_memory.o ../exception/exception_memory.cpp

${OBJECTDIR}/_ext/1392566472/windows_crt.o: ../os/cross/windows/windows_crt.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1392566472
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1392566472/windows_crt.o ../os/cross/windows/windows_crt.cpp

${OBJECTDIR}/_ext/761014165/file_byte_stream_memory_buffer.o: ../file/file_byte_stream_memory_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_byte_stream_memory_buffer.o ../file/file_byte_stream_memory_buffer.cpp

${OBJECTDIR}/_ext/1893554344/primitive_type.o: ../primitive/primitive_type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_type.o ../primitive/primitive_type.cpp

${OBJECTDIR}/_ext/761014165/file_exception.o: ../file/file_exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_exception.o ../file/file_exception.cpp

${OBJECTDIR}/_ext/732521037/collection_class_sort_array.o: ../collection/collection_class_sort_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_class_sort_array.o ../collection/collection_class_sort_array.cpp

${OBJECTDIR}/_ext/2111058971/linux_cross_win_file.o: ../linux/linux_cross_win_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_cross_win_file.o ../linux/linux_cross_win_file.cpp

${OBJECTDIR}/_ext/761014165/file_simple_binary_buffer.o: ../file/file_simple_binary_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_simple_binary_buffer.o ../file/file_simple_binary_buffer.cpp

${OBJECTDIR}/_ext/1237618410/datetime_time.o: ../datetime/datetime_time.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1237618410
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1237618410/datetime_time.o ../datetime/datetime_time.cpp

${OBJECTDIR}/_ext/1360937314/str_international.o: ../str/str_international.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_international.o ../str/str_international.cpp

${OBJECTDIR}/_ext/1893554344/primitive_command_thread.o: ../primitive/primitive_command_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_command_thread.o ../primitive/primitive_command_thread.cpp

${OBJECTDIR}/_ext/1328484458/ansios_file_std.o: ../ansios/ansios_file_std.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_file_std.o ../ansios/ansios_file_std.cpp

${OBJECTDIR}/_ext/761140800/base.o: ../base/base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base.o ../base/base.cpp

${OBJECTDIR}/_ext/1360941896/xml_parse_info.o: ../xml/xml_parse_info.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_parse_info.o ../xml/xml_parse_info.cpp

${OBJECTDIR}/_ext/1360941896/xml_output_tree.o: ../xml/xml_output_tree.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_output_tree.o ../xml/xml_output_tree.cpp

${OBJECTDIR}/_ext/761014165/file_plain_text_stream.o: ../file/file_plain_text_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_plain_text_stream.o ../file/file_plain_text_stream.cpp

${OBJECTDIR}/_ext/1422879424/exception_dump.o: ../exception/exception_dump.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_dump.o ../exception/exception_dump.cpp

${OBJECTDIR}/_ext/1360937314/str_hex.o: ../str/str_hex.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_hex.o ../str/str_hex.cpp

${OBJECTDIR}/_ext/1328484458/ansios_cross_win_file.o: ../ansios/ansios_cross_win_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_cross_win_file.o ../ansios/ansios_cross_win_file.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_single_lock.o: ../multithreading/multithreading_single_lock.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_single_lock.o ../multithreading/multithreading_single_lock.cpp

${OBJECTDIR}/_ext/1893554344/primitive_memory_base.o: ../primitive/primitive_memory_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_memory_base.o ../primitive/primitive_memory_base.cpp

${OBJECTDIR}/_ext/1422879424/exception_standard_translator.o: ../exception/exception_standard_translator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_standard_translator.o ../exception/exception_standard_translator.cpp

${OBJECTDIR}/_ext/1360941896/xml_tree_base.o: ../xml/xml_tree_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_tree_base.o ../xml/xml_tree_base.cpp

${OBJECTDIR}/_ext/732521037/collection_object_list.o: ../collection/collection_object_list.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_object_list.o ../collection/collection_object_list.cpp

${OBJECTDIR}/_ext/1422879424/exception_debug.o: ../exception/exception_debug.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_debug.o ../exception/exception_debug.cpp

${OBJECTDIR}/_ext/761140800/base_checked.o: ../base/base_checked.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_checked.o ../base/base_checked.cpp

${OBJECTDIR}/_ext/1422879424/exception_simple.o: ../exception/exception_simple.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_simple.o ../exception/exception_simple.cpp

${OBJECTDIR}/_ext/1422879424/exception_not_implemented.o: ../exception/exception_not_implemented.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_not_implemented.o ../exception/exception_not_implemented.cpp

${OBJECTDIR}/_ext/761140800/base_departament_container.o: ../base/base_departament_container.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_departament_container.o ../base/base_departament_container.cpp

${OBJECTDIR}/_ext/1289935841/geometry_types.o: ../geometry/geometry_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1289935841
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1289935841/geometry_types.o ../geometry/geometry_types.cpp

${OBJECTDIR}/_ext/1328484458/ansios_cross_win.o: ../ansios/ansios_cross_win.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_cross_win.o ../ansios/ansios_cross_win.cpp

${OBJECTDIR}/_ext/1392566472/windows_time.o: ../os/cross/windows/windows_time.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1392566472
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1392566472/windows_time.o ../os/cross/windows/windows_time.cpp

${OBJECTDIR}/_ext/761014165/file_byte_input_stream_binary_buffer.o: ../file/file_byte_input_stream_binary_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_byte_input_stream_binary_buffer.o ../file/file_byte_input_stream_binary_buffer.cpp

${OBJECTDIR}/_ext/1893554344/primitive_interlocked_long.o: ../primitive/primitive_interlocked_long.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_interlocked_long.o ../primitive/primitive_interlocked_long.cpp

${OBJECTDIR}/_ext/761014165/file_stream_buffer.o: ../file/file_stream_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_stream_buffer.o ../file/file_stream_buffer.cpp

${OBJECTDIR}/_ext/732521037/collection_string_list.o: ../collection/collection_string_list.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_string_list.o ../collection/collection_string_list.cpp

${OBJECTDIR}/_ext/1893554344/primitive_command.o: ../primitive/primitive_command.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_command.o ../primitive/primitive_command.cpp

${OBJECTDIR}/_ext/1893554344/primitive_bit.o: ../primitive/primitive_bit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_bit.o ../primitive/primitive_bit.cpp

${OBJECTDIR}/_ext/1392566472/windows_user.o: ../os/cross/windows/windows_user.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1392566472
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1392566472/windows_user.o ../os/cross/windows/windows_user.cpp

${OBJECTDIR}/_ext/761014165/file_writer.o: ../file/file_writer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_writer.o ../file/file_writer.cpp

${OBJECTDIR}/_ext/1392566472/windows.o: ../os/cross/windows/windows.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1392566472
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1392566472/windows.o ../os/cross/windows/windows.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_sync_object.o: ../multithreading/multithreading_sync_object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_sync_object.o ../multithreading/multithreading_sync_object.cpp

${OBJECTDIR}/_ext/43901075/os_thread.o: ../os/os_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43901075
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/43901075/os_thread.o ../os/os_thread.cpp

${OBJECTDIR}/_ext/1360937314/str_stringtow.o: ../str/str_stringtow.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_stringtow.o ../str/str_stringtow.cpp

${OBJECTDIR}/_ext/760813065/math_math.o: ../math/math_math.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760813065
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/760813065/math_math.o ../math/math_math.cpp

${OBJECTDIR}/_ext/1422879424/exception_todo.o: ../exception/exception_todo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_todo.o ../exception/exception_todo.cpp

${OBJECTDIR}/_ext/1360941896/xml_entity.o: ../xml/xml_entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_entity.o ../xml/xml_entity.cpp

${OBJECTDIR}/_ext/1392566472/windows_thread.o: ../os/cross/windows/windows_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1392566472
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1392566472/windows_thread.o ../os/cross/windows/windows_thread.cpp

${OBJECTDIR}/_ext/1893554344/primitive_memory_c.o: ../primitive/primitive_memory_c.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_memory_c.o ../primitive/primitive_memory_c.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_event_base.o: ../multithreading/multithreading_event_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_event_base.o ../multithreading/multithreading_event_base.cpp

${OBJECTDIR}/_ext/1360937314/str_tokenizer.o: ../str/str_tokenizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_tokenizer.o ../str/str_tokenizer.cpp

${OBJECTDIR}/_ext/1893554344/primitive_interlocked_long_pulse.o: ../primitive/primitive_interlocked_long_pulse.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_interlocked_long_pulse.o ../primitive/primitive_interlocked_long_pulse.cpp

${OBJECTDIR}/_ext/1360932046/net_url_departament.o: ../net/net_url_departament.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360932046
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360932046/net_url_departament.o ../net/net_url_departament.cpp

${OBJECTDIR}/_ext/761014165/file_plain_text_output_stream_string_buffer.o: ../file/file_plain_text_output_stream_string_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_plain_text_output_stream_string_buffer.o ../file/file_plain_text_output_stream_string_buffer.cpp

${OBJECTDIR}/_ext/761014165/file_byte_output_stream_binary_buffer.o: ../file/file_byte_output_stream_binary_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_byte_output_stream_binary_buffer.o ../file/file_byte_output_stream_binary_buffer.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_core.o: ../multithreading/multithreading_core.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_core.o ../multithreading/multithreading_core.cpp

${OBJECTDIR}/_ext/1629396920/comparison_md5.o: ../comparison/comparison_md5.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1629396920
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1629396920/comparison_md5.o ../comparison/comparison_md5.cpp

${OBJECTDIR}/_ext/761140800/base_template.o: ../base/base_template.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_template.o ../base/base_template.cpp

${OBJECTDIR}/_ext/761140800/base_plex_heap.o: ../base/base_plex_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_plex_heap.o ../base/base_plex_heap.cpp

${OBJECTDIR}/_ext/43901075/os_http.o: ../os/os_http.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/43901075
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/43901075/os_http.o ../os/os_http.cpp

${OBJECTDIR}/_ext/2111058971/linux_window.o: ../linux/linux_window.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_window.o ../linux/linux_window.cpp

${OBJECTDIR}/_ext/1893554344/primitive_memory_container.o: ../primitive/primitive_memory_container.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_memory_container.o ../primitive/primitive_memory_container.cpp

${OBJECTDIR}/_ext/1360937314/str_string.o: ../str/str_string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_string.o ../str/str_string.cpp

${OBJECTDIR}/_ext/1360937314/str_istring.o: ../str/str_istring.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_istring.o ../str/str_istring.cpp

${OBJECTDIR}/_ext/761140800/base_thread.o: ../base/base_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_thread.o ../base/base_thread.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_multi_lock.o: ../multithreading/multithreading_multi_lock.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_multi_lock.o ../multithreading/multithreading_multi_lock.cpp

${OBJECTDIR}/_ext/761014165/file_composite.o: ../file/file_composite.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_composite.o ../file/file_composite.cpp

${OBJECTDIR}/_ext/761014165/file_byte_input_stream.o: ../file/file_byte_input_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_byte_input_stream.o ../file/file_byte_input_stream.cpp

${OBJECTDIR}/_ext/761014165/file_seekable.o: ../file/file_seekable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_seekable.o ../file/file_seekable.cpp

${OBJECTDIR}/_ext/761140800/base_muldiv64.o: ../base/base_muldiv64.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_muldiv64.o ../base/base_muldiv64.cpp

${OBJECTDIR}/_ext/1328484458/ansios_cross_windows_user.o: ../ansios/ansios_cross_windows_user.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_cross_windows_user.o ../ansios/ansios_cross_windows_user.cpp

${OBJECTDIR}/_ext/1328484458/ansios_http_lib.o: ../ansios/ansios_http_lib.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_http_lib.o ../ansios/ansios_http_lib.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_file_change_event.o: ../multithreading/multithreading_file_change_event.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_file_change_event.o ../multithreading/multithreading_file_change_event.cpp

${OBJECTDIR}/_ext/1360937314/str_strw.o: ../str/str_strw.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_strw.o ../str/str_strw.cpp

${OBJECTDIR}/_ext/1360941896/xml_document.o: ../xml/xml_document.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_document.o ../xml/xml_document.cpp

${OBJECTDIR}/_ext/761140800/base_plex.o: ../base/base_plex.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_plex.o ../base/base_plex.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_service_base.o: ../multithreading/multithreading_service_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_service_base.o ../multithreading/multithreading_service_base.cpp

${OBJECTDIR}/_ext/1360937314/str_manager.o: ../str/str_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_manager.o ../str/str_manager.cpp

${OBJECTDIR}/_ext/732521037/collection_var_array.o: ../collection/collection_var_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_var_array.o ../collection/collection_var_array.cpp

${OBJECTDIR}/_ext/1893554344/primitive_request_signal.o: ../primitive/primitive_request_signal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_request_signal.o ../primitive/primitive_request_signal.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_waitable.o: ../multithreading/multithreading_waitable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_waitable.o ../multithreading/multithreading_waitable.cpp

${OBJECTDIR}/_ext/1289935841/geometry_rect.o: ../geometry/geometry_rect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1289935841
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1289935841/geometry_rect.o ../geometry/geometry_rect.cpp

${OBJECTDIR}/_ext/1422879424/exception_installing.o: ../exception/exception_installing.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_installing.o ../exception/exception_installing.cpp

${OBJECTDIR}/_ext/761014165/file_dir.o: ../file/file_dir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_dir.o ../file/file_dir.cpp

${OBJECTDIR}/_ext/583780700/c_os.o: ../solaris/c_os.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/583780700
	$(COMPILE.c) -g -KPIC  -o ${OBJECTDIR}/_ext/583780700/c_os.o ../solaris/c_os.c

${OBJECTDIR}/_ext/1422879424/exception_invalid_handle.o: ../exception/exception_invalid_handle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_invalid_handle.o ../exception/exception_invalid_handle.cpp

${OBJECTDIR}/_ext/1422879424/exception_temporary.o: ../exception/exception_temporary.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_temporary.o ../exception/exception_temporary.cpp

${OBJECTDIR}/_ext/1893554344/primitive_data_listener.o: ../primitive/primitive_data_listener.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_data_listener.o ../primitive/primitive_data_listener.cpp

${OBJECTDIR}/_ext/761140800/base_fixed_alloc.o: ../base/base_fixed_alloc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_fixed_alloc.o ../base/base_fixed_alloc.cpp

${OBJECTDIR}/_ext/1360941896/xml_xmlite.o: ../xml/xml_xmlite.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_xmlite.o ../xml/xml_xmlite.cpp

${OBJECTDIR}/_ext/1360937314/str_format.o: ../str/str_format.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_format.o ../str/str_format.cpp

${OBJECTDIR}/_ext/761014165/file_byte_stream.o: ../file/file_byte_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_byte_stream.o ../file/file_byte_stream.cpp

${OBJECTDIR}/_ext/1328484458/ansios_file.o: ../ansios/ansios_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1328484458
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1328484458/ansios_file.o ../ansios/ansios_file.cpp

${OBJECTDIR}/_ext/2111058971/linux_c.o: ../linux/linux_c.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.c) -g -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_c.o ../linux/linux_c.c

${OBJECTDIR}/_ext/1422879424/exception_archive_exception.o: ../exception/exception_archive_exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_archive_exception.o ../exception/exception_archive_exception.cpp

${OBJECTDIR}/_ext/1422879424/exception_dump_floating_point.o: ../exception/exception_dump_floating_point.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_dump_floating_point.o ../exception/exception_dump_floating_point.cpp

${OBJECTDIR}/_ext/761014165/file_memory_buffer.o: ../file/file_memory_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_memory_buffer.o ../file/file_memory_buffer.cpp

${OBJECTDIR}/_ext/1237618410/datetime_duration.o: ../datetime/datetime_duration.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1237618410
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1237618410/datetime_duration.o ../datetime/datetime_duration.cpp

${OBJECTDIR}/_ext/732521037/collection_bit_array.o: ../collection/collection_bit_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_bit_array.o ../collection/collection_bit_array.cpp

${OBJECTDIR}/_ext/761140800/base_allocate_system_heap.o: ../base/base_allocate_system_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_allocate_system_heap.o ../base/base_allocate_system_heap.cpp

${OBJECTDIR}/_ext/1893554344/primitive_command_line.o: ../primitive/primitive_command_line.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_command_line.o ../primitive/primitive_command_line.cpp

${OBJECTDIR}/_ext/732521037/collection_array.o: ../collection/collection_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_array.o ../collection/collection_array.cpp

${OBJECTDIR}/_ext/1360941896/xml_tree_schema.o: ../xml/xml_tree_schema.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_tree_schema.o ../xml/xml_tree_schema.cpp

${OBJECTDIR}/_ext/1629396920/comparison_var_strict.o: ../comparison/comparison_var_strict.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1629396920
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1629396920/comparison_var_strict.o ../comparison/comparison_var_strict.cpp

${OBJECTDIR}/_ext/1893554344/primitive_object.o: ../primitive/primitive_object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1893554344
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1893554344/primitive_object.o ../primitive/primitive_object.cpp

${OBJECTDIR}/_ext/761140800/base_root.o: ../base/base_root.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_root.o ../base/base_root.cpp

${OBJECTDIR}/_ext/1422879424/exception_archive.o: ../exception/exception_archive.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_archive.o ../exception/exception_archive.cpp

${OBJECTDIR}/_ext/1422879424/exception_VMSException.o: ../exception/exception_VMSException.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_VMSException.o ../exception/exception_VMSException.cpp

${OBJECTDIR}/_ext/1360937314/str_str.o: ../str/str_str.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_str.o ../str/str_str.cpp

${OBJECTDIR}/_ext/761014165/file_plain_text_stream_memory_buffer.o: ../file/file_plain_text_stream_memory_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_plain_text_stream_memory_buffer.o ../file/file_plain_text_stream_memory_buffer.cpp

${OBJECTDIR}/_ext/761014165/file_dir2.o: ../file/file_dir2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_dir2.o ../file/file_dir2.cpp

${OBJECTDIR}/_ext/1422879424/exception_operation_canceled.o: ../exception/exception_operation_canceled.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_operation_canceled.o ../exception/exception_operation_canceled.cpp

${OBJECTDIR}/_ext/732521037/collection_string_array.o: ../collection/collection_string_array.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/732521037
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/732521037/collection_string_array.o ../collection/collection_string_array.cpp

${OBJECTDIR}/_ext/2111058971/linux_debug.o: ../linux/linux_debug.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_debug.o ../linux/linux_debug.cpp

${OBJECTDIR}/_ext/1360941896/xml_node.o: ../xml/xml_node.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_node.o ../xml/xml_node.cpp

${OBJECTDIR}/_ext/1360941896/xml_disp_option.o: ../xml/xml_disp_option.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_disp_option.o ../xml/xml_disp_option.cpp

${OBJECTDIR}/_ext/761140800/base_c.o: ../base/base_c.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/761140800
	$(COMPILE.c) -g -KPIC  -o ${OBJECTDIR}/_ext/761140800/base_c.o ../base/base_c.c

${OBJECTDIR}/_ext/1360937314/str_simple.o: ../str/str_simple.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937314
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360937314/str_simple.o ../str/str_simple.cpp

${OBJECTDIR}/_ext/1422879424/exception_dump_context.o: ../exception/exception_dump_context.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_dump_context.o ../exception/exception_dump_context.cpp

${OBJECTDIR}/_ext/1422879424/exception_range_error.o: ../exception/exception_range_error.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_range_error.o ../exception/exception_range_error.cpp

${OBJECTDIR}/_ext/1422879424/exception_io.o: ../exception/exception_io.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_io.o ../exception/exception_io.cpp

${OBJECTDIR}/_ext/2111058971/linux_display.o: ../linux/linux_display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_display.o ../linux/linux_display.cpp

${OBJECTDIR}/_ext/1289935841/geometry_size.o: ../geometry/geometry_size.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1289935841
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1289935841/geometry_size.o ../geometry/geometry_size.cpp

${OBJECTDIR}/_ext/1392566472/windows_shared_memory.o: ../os/cross/windows/windows_shared_memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1392566472
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1392566472/windows_shared_memory.o ../os/cross/windows/windows_shared_memory.cpp

${OBJECTDIR}/_ext/2111058971/linux_process.o: ../linux/linux_process.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2111058971
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/2111058971/linux_process.o ../linux/linux_process.cpp

${OBJECTDIR}/_ext/1360941896/xml_xml.o: ../xml/xml_xml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360941896
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1360941896/xml_xml.o ../xml/xml_xml.cpp

${OBJECTDIR}/_ext/761014165/file_plain_text_output_stream.o: ../file/file_plain_text_output_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/761014165/file_plain_text_output_stream.o ../file/file_plain_text_output_stream.cpp

${OBJECTDIR}/_ext/1422879424/exception_overflow_error.o: ../exception/exception_overflow_error.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_overflow_error.o ../exception/exception_overflow_error.cpp

${OBJECTDIR}/_ext/1422879424/exception_not_installed.o: ../exception/exception_not_installed.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_not_installed.o ../exception/exception_not_installed.cpp

${OBJECTDIR}/_ext/1422879424/exception_exit.o: ../exception/exception_exit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422879424
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1422879424/exception_exit.o ../exception/exception_exit.cpp

${OBJECTDIR}/_ext/1055495342/multithreading_semaphore.o: ../multithreading/multithreading_semaphore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1055495342
	$(COMPILE.cc) -g -I.. -I../../../.. -I../.. -KPIC  -o ${OBJECTDIR}/_ext/1055495342/multithreading_semaphore.o ../multithreading/multithreading_semaphore.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbase.sol.so
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

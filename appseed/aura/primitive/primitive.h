#pragma once


#include "aura/primitive/primitive_var.h"
#include "aura/primitive/primitive_property_set.h"
#include "aura/primitive/primitive_application_bias.h"
#include "aura/primitive/primitive_color.h"
#include "aura/primitive/primitive_command.h"
#include "aura/primitive/primitive_command_line.h"
#include "aura/primitive/primitive_create.h"
#include "aura/primitive/primitive_command_thread.h"
#include "aura/primitive/primitive_edit.h"
#include "aura/primitive/primitive_factory.h"
#include "aura/primitive/primitive_id.h"
#include "aura/primitive/primitive_id_space.h"
#include "aura/primitive/primitive_interlocked_long.h"
#include "aura/primitive/primitive_interlocked_long_pulse.h"
#include "aura/primitive/primitive_job.h"
#include "aura/primitive/primitive_memory_container.h"
#include "aura/primitive/primitive_relation_set.h"
#include "aura/primitive/primitive_request_signal.h"
#include "aura/primitive/primitive_shared_memory.h"
#include "aura/primitive/primitive_virtual_memory.h"












namespace file
{

   class writer;
   class reader;

}







//CLASS_DECL_AURA ::file::ostream & operator << (::file::ostream & ostream, const property & prop);
//CLASS_DECL_AURA ::file::istream & operator >> (::file::istream & istream, property & prop);
//
//
//CLASS_DECL_AURA ::file::ostream & operator << (::file::ostream & ostream, const var & var);
//CLASS_DECL_AURA ::file::istream & operator >> (::file::istream & istream, var & var);

CLASS_DECL_AURA ::file::ostream & operator << (::file::ostream & ostream, const property_set & set);
CLASS_DECL_AURA ::file::istream & operator >> (::file::istream & istream, property_set & set);






namespace lemon
{

   CLASS_DECL_AURA void transfer_to(::file::writer & writer, const ::primitive::memory_base & mem, memory_size_t uiBufferSize = 1024 * 1024);

   CLASS_DECL_AURA void transfer_from_begin(::file::reader & reader, ::primitive::memory_base & mem, memory_size_t uiBufferSize = 1024 * 1024);

   CLASS_DECL_AURA void transfer_from(::file::reader & reader, ::primitive::memory_base & mem, memory_size_t uiBufferSize = 1024 * 1024);


} // namespace lemon

CLASS_DECL_AURA::file::istream & operator >> (::file::istream & istream, ::primitive::memory_container & memcontainer);

CLASS_DECL_AURA::file::ostream & operator << (::file::ostream & ostream, const ::primitive::memory_base & mem);

CLASS_DECL_AURA::file::istream & operator >> (::file::istream & istream, ::primitive::memory_base & mem);


#include "primitive.inl"
#include "primitive_factory_impl.inl"
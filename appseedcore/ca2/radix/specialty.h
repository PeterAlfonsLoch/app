#pragma once

// special exception handling just for ca2 API library implementation

// ca2 API does not rely on auto-delete semantics of the TRY..CATCH macros,
//  therefore those macros are mapped to something closer to the native
//  C++ exception handling mechanism when building ca2 API itself.

#undef TRY
#define TRY { try {

#undef CATCH
#define CATCH(class, e) } catch (class* e) \
   { ASSERT(e->is_kind_of(&typeid(class))); UNUSED(e);

#undef AND_CATCH
#define AND_CATCH(class, e) } catch (class* e) \
   { ASSERT(e->is_kind_of(&typeid(class))); UNUSED(e);

#undef CATCH_ALL
#define CATCH_ALL(e) } catch (base_exception* e) \
   { { ASSERT(e->is_kind_of(&typeid(base_exception))); UNUSED(e);

#undef AND_CATCH_ALL
#define AND_CATCH_ALL(e) } catch (base_exception* e) \
   { { ASSERT(e->is_kind_of(&typeid(base_exception))); UNUSED(e);

#undef END_TRY
#define END_TRY } catch (base_exception* e) \
   { ASSERT(e->is_kind_of(&typeid(base_exception))); e->Delete(); } }

#undef THROW_LAST
#define THROW_LAST() throw

// Because of the above definitions of TRY...CATCH it is necessary to
//  explicitly delete exception objects at the catch site.

#define DELETE_EXCEPTION(e) do { e->Delete(); } while (0)
#define NO_CPP_EXCEPTION(expr)


/////////////////////////////////////////////////////////////////////////////

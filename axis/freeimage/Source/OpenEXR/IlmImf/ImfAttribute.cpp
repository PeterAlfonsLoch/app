#include "Imf.h"



//-----------------------------------------------------------------------------
//
//	class Attribute
//
//-----------------------------------------------------------------------------

//#include <ImfAttribute.h>
//#include "Iex.h"
//#include "Iex.h"
//#include <string.h>
////#include <map>


namespace Imf {

using IlmThread::Mutex;
using IlmThread::Lock;


Attribute::Attribute () {}


Attribute::~Attribute () {}


namespace {

struct NameCompare: std::binary_function <const char *, const char *, bool>
{
    bool
    operator () (const char *x, const char *y) const
    {
	return strcmp (x, y) < 0;
    }
};


typedef Attribute* (*Constructor)();
typedef std::map <const char *, Constructor, NameCompare> TypeMap;
//typedef std::map <const char *,Constructor> TypeMap;


class LockedTypeMap: public TypeMap
{
  public:

    Mutex mutex;
};


LockedTypeMap &
typeMap ()
{
    static Mutex criticalSection;
    Lock lock (criticalSection);

    static LockedTypeMap* typeMap = 0;

    if (typeMap == 0)
	typeMap = new LockedTypeMap ();

    return *typeMap;
}


} // namespace


bool		
Attribute::knownType (const char typeName[])
{
    LockedTypeMap& tMap = typeMap();
    Lock lock (tMap.mutex);

    return tMap.find (typeName) != tMap.end();
}


void	
Attribute::registerAttributeType (const char typeName[],
			          Attribute *(*newAttribute)())
{
    LockedTypeMap& tMap = typeMap();
    Lock lock (tMap.mutex);

    if (tMap.find (typeName) != tMap.end())
	THROW (Iex::ArgExc, "Cannot register image file attribute "
			    "type \"" << typeName << "\". "
			    "The type has already been registered.");

    tMap.set_at(typeName, newAttribute);
}


void
Attribute::unRegisterAttributeType (const char typeName[])
{
    LockedTypeMap& tMap = typeMap();
    Lock lock (tMap.mutex);

    tMap.erase (typeName);
}


Attribute *
Attribute::newAttribute (const char typeName[])
{
    LockedTypeMap& tMap = typeMap();
    Lock lock (tMap.mutex);

    TypeMap::const_iterator i = tMap.find (typeName);

    if (i == tMap.end())
	THROW (Iex::ArgExc, "Cannot create image file attribute of "
			    "unknown type \"" << typeName << "\".");

    return (i->m_element2)();
}


} // namespace Imf

#include "StdAfx.h"

#include "WinAppImpl.h"

#include "WinFile.h"

#include "WinFileSet.h"

#include "WinFileSystem.h"

#include "ex1/Ex1Resource.h"
#include "WinResource.h"

#include "WinStdioFile.h"


WinFactoryImpl::WinFactoryImpl()
{

}

WinFactoryImpl::~WinFactoryImpl()
{

}


Ex1Impl * WinFactoryImpl::New(::ca::type_info ti)
{
   if(ti == typeid(Ex2Application))
   {
      return new WinAppImpl();
   }
   else if(ti == typeid(Ex2FileSet))
   {
      return new WinFileSet();
   }
   else if(ti == typeid(Ex1FileSystem))
   {
      return new WinFileSystem();
   }
   else if(ti == typeid(Ex1TextFile))
   {
      return new WinStdioFile();
   }
   else if(ti == typeid(Ex1File))
   {
      return new WinFile();
   }
   else if(ti == typeid(Ex1FileException))
   {
      return new WinFileException();
   }
   else if(ti == typeid(Ex1Resource))
   {
      return new WinResource();
   }
   return NULL;
}




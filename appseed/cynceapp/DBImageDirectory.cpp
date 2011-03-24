
#include "stdafx.h"
#include "resource.h"
#include "DBImageDirectory.h"

DBImageDirectorySet::DBImageDirectorySet() :
DBStringArraySet(NULL, VMSDATAKEY(ImageDirectorySet))
{
   int iInitialized = 0;
	if(!VmsDataGet(
      VMSDATAKEY(ImageDirectorySetInitialUpdate),
      0, 0, iInitialized))
	{
      VmsDataSet(VMSDATAKEY(ImageDirectorySetInitialUpdate), 0, 0, 1);

      WStrArray wstra;

      DB()->GetDefaultImageDirectorySet(&wstra);
      SetData(wstra);
   }
}

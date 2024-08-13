#include "FrameworkCommonLibrary.h"

bool FFrameworkCommonLibrary::WithInEditor()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}
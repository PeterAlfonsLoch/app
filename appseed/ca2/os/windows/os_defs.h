// Windows/Defs.h

#pragma once

inline bool LRESULTToBool(LRESULT v) { return (v != FALSE); }
inline bool WINBOOLToBool(WINBOOL v) { return (v != FALSE); }
inline WINBOOL BoolToWINBOOL(bool v) { return (v ? TRUE: FALSE); }


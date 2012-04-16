// Windows/Defs.h

#pragma once

inline bool LRESULTToBool(LRESULT v) { return (v != FALSE); }
inline bool BOOLToBool(BOOL v) { return (v != FALSE); }
inline BOOL BoolToBOOL(bool v) { return (v ? TRUE: FALSE); }


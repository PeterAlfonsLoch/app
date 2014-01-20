// ==========================================================
// Multi-Page functions
//
// Design and implementation by
// - Floris van den Berg (flvdberg@wxs.nl)
//
// This file is part of FreeImage 3
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at your own risk!
// ==========================================================

#ifndef CACHEFILE_H
#define CACHEFILE_H

// ----------------------------------------------------------

#include "Utilities.h"

// ----------------------------------------------------------

static const int CACHE_SIZE = 32;
static const int BLOCK_SIZE = (64 * 1024) - 8;

// ----------------------------------------------------------

#ifdef _WIN32
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif // _WIN32

struct Block {
     unsigned nr;
     unsigned next;
     BYTE *data;
};

#ifdef _WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif // _WIN32

// ----------------------------------------------------------

class CacheFile {
	typedef list<Block *> PageCache;
   typedef list<Block *>::iterator PageCacheIt;
	typedef map<int, int, PageCacheIt, PageCacheIt> PageMap;
	typedef map<int, int, PageCacheIt, PageCacheIt>::iterator PageMapIt;

public :
	CacheFile(const string filename, int_bool keep_in_memory);
	~CacheFile();

	int_bool open();
	void close();
	int_bool readFile(BYTE *data, int nr, int size);
	int writeFile(BYTE *data, int size);
	void deleteFile(int nr);

private :
	void cleanupMemCache();
	int allocateBlock();
	Block *lockBlock(int nr);
	int_bool unlockBlock(int nr);
	int_bool deleteBlock(int nr);

private :
	FILE *m_file;
	string m_filename;
	list<int> m_free_pages;
	PageCache m_page_cache_mem;
	PageCache m_page_cache_disk;
	PageMap m_page_map;
	int m_page_count;
	Block *m_current_block;
	int_bool m_keep_in_memory;
};

#endif // CACHEFILE_H

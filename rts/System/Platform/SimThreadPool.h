/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef SIMTHREADPOOL_H
#define SIMTHREADPOOL_H
#include "System/Platform/Threading.h"
#include <boost/thread/barrier.hpp>
#include "lib/gml/gmlcnt.h"

class CSimThreadPool {
public:
	CSimThreadPool();
	virtual ~CSimThreadPool();
	void Execute(void (* tf)(bool) = NULL, void (* itf)(bool) = NULL, int i = 0);
	long NextIter() { return ++atomicCount; }

private:
	gmlCount atomicCount;
	int simNumExtraThreads;
	boost::barrier* simBarrier;
	boost::thread* simThreads[GML_MAX_NUM_THREADS];
	volatile bool stopThread;
	void (* volatile InitThreadFunc)(bool);
	void (* volatile ThreadFunc)(bool);
};

#endif // SIMTHREADPOOL_H

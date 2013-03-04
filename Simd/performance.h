// Copyright (C) 2012 Reply S.p.A. and/or its subsidiary(-ies). All rights reserved.
// Released under the the GNU Lesser General Public License version 2.1. In addition, as a special exception, Reply S.p.A. gives you certain additional rights.
// Alternatively, this file may be used in accordance with the terms and conditions contained in a signed written agreement between you and Reply S.p.A., and/or its subsidiary(-ies).
// See Licence.txt

#ifndef PERFORMANCE_H__
#define PERFORMANCE_H__
#endif

#ifdef _WIN32
	//#include <time.h>
	//typedef clock_t  Clock;
	//#include <stdint.h>
	#include <windows.h>
	#include <stdio.h>
	typedef __int64 Clock;

//Apple systems
#elif defined (__APPLE__)
	#include <stdint.h>
	typedef uint64_t Clock;
#endif

namespace performance {
	Clock   Start          ();
	Clock   Stop           ();
	double   ExecutionTime  (Clock start, Clock stop);
}


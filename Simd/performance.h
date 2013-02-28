#ifndef PERFORMANCE_H__
#define PERFORMANCE_H__

namespace performance {
	uint64_t   Start          ();
	uint64_t   Stop           ();
	double     ExecutionTime  (uint64_t start, uint64_t stop);
}

#endif
#ifndef INTERVAL_H
#define INTERVAL_H

typedef struct{
	f64 min;
	f64 max;
}interval;

inline interval
create_interval(f64 min, f64 max){
	return (interval){min,max};
}

inline f64
interval_size(interval itvl){
	return itvl.max - itvl.min;
}

inline b32
interval_contains(interval itvl, f64 x){
	b32 result;
	result = itvl.min <= x && x <= itvl.max;
	return result;
}

inline b32
interval_surrounds(interval itvl, f64 x){
	b32 result;
	result = itvl.min < x && x < itvl.max;
	return result;
}


const interval interval_empty = {+INFINITY, -INFINITY};
const interval interval_universe = {-INFINITY, +INFINITY};
#endif

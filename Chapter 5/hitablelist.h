#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"
class hitable_list :public hitable {
public:
	hitable_list() {}
	hitanle_list(hitable **l, int n) { list = l; list_size = n; }
};

#endif

#include "time_mgr.h"

namespace nario {
	TimeMgr* TimeMgr::_instance = NULL;
	TimeMgr::GC TimeMgr::gc;
}
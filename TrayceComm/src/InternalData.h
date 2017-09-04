#ifndef TRAYCE_INTERNALDATA_H
#define TRAYCE_INTERNALDATA_H

#include "Trayce/LogService.h"

namespace Trayce { namespace Comm {

Trayce::Log::LogCategoryId GTrayceCommCategoryId = Trayce::Log::LogService::get().registerCategory("Trayce::Comm");

}} // Trayce::Comm

#endif //TRAYCE_INTERNALDATA_H

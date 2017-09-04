#ifndef TRAYCE_INTERNALDATA_H
#define TRAYCE_INTERNALDATA_H

#include "Trayce/LogService.h"

namespace Trayce { namespace Log {

LogCategoryId GTrayceCoreCategoryId = LogService::get().registerCategory("Trayce::Core");

}} // Trayce::Log

#endif //TRAYCE_INTERNALDATA_H

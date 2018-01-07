#ifndef DEEPSTATS_GLOBAL_H
#define DEEPSTATS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEEPSTATS_LIBRARY)
#  define DEEPSTATS_EXPORT Q_DECL_EXPORT
#else
#  define DEEPSTATS_EXPORT Q_DECL_IMPORT
#endif

#endif // DEEPSTATS_GLOBAL_H

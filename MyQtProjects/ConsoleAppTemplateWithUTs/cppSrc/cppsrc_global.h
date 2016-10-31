#ifndef CPPSRC_GLOBAL_H
#define CPPSRC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CPPSRC_LIBRARY)
#  define CPPSRCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CPPSRCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CPPSRC_GLOBAL_H

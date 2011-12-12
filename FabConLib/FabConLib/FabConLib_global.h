#ifndef FABCONLIB_GLOBAL_H
#define FABCONLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FABCONLIB_LIBRARY)
#  define FABCONLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FABCONLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FABCONLIB_GLOBAL_H

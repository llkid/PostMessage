#ifndef MY_TESTLIB_GLOBAL_H
#define MY_TESTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MY_TESTLIB_LIBRARY)
#  define MY_TESTLIB_EXPORT Q_DECL_EXPORT
#else
#  define MY_TESTLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // MY_TESTLIB_GLOBAL_H

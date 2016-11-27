#ifndef LIBSYMBOLSEXPORT_H
#define LIBSYMBOLSEXPORT_H

#include <QtCore/QtGlobal>


/*!
 * \note    This define construct is used to select the
 *          right compiler option:
 *          - if compiling library itself, you need to
 *            use 'declare export' (Qt => Q_DECL_EXPORT)
 *          - if compiling client's code using the library,
 *            you need to use 'declare import' (Qt => Q_DECL_IMPORT)
 */
#if defined(COMPILE_LIBRARY)
#  define LIB_EXPORT Q_DECL_EXPORT
#else
#  define LIB_EXPORT Q_DECL_IMPORT
#endif


#endif // LIBSYMBOLSEXPORT_H

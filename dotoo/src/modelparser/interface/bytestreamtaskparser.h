#ifndef BYTESTREAMTASKPARSER_H
#define BYTESTREAMTASKPARSER_H

#include <QList>

#include "project/libsymbolsexport.h"
#include "models/interface/decl/taskdecl.h"



class QByteArray;


namespace Dotoo {
namespace ModelParser {


class LIB_EXPORT BytestreamTaskParser
{
public:
    virtual ~BytestreamTaskParser() {}

    virtual Task BytestreamIntoTask( const QByteArray& bs ) const = 0;
    virtual QList<Task> BytestreamIntoTaskList( const QByteArray& bs ) const = 0;

    virtual QByteArray TaskIntoBytestream( const Task& task ) const = 0;
    virtual QByteArray TaskListIntoBytestream( const QList<Task>& taskList ) const = 0;
};


} // namespace ModelParser
} // namespace Dotoo

#endif // BYTESTREAMTASKPARSER_H

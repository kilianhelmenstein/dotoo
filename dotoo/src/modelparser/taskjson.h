#ifndef TASKJSON_H
#define TASKJSON_H

#include <QtGlobal>

#include "modelparser/interface/bytestreamtaskparser.h"


namespace Dotoo {
namespace ModelParser {


class LIB_EXPORT JsonTaskParser : public BytestreamTaskParser
{
public:
    Task BytestreamIntoTask( const QByteArray& bs ) const;
    QList<Task> BytestreamIntoTaskList( const QByteArray& bs ) const;

    QByteArray TaskIntoBytestream( const Task& task ) const;
    QByteArray TaskListIntoBytestream( const QList<Task>& taskList ) const;
};


} // namespace ModelParser
} // namespace Dotoo

#endif // TASKJSON_H

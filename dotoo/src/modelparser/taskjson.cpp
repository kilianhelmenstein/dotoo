#include <QByteArray>
#include <QString>
#include <QDate>

#include "parsing/json.h"

#include "taskjson.h"
#include "task.h"
#include "types/tasktypes.h"


using namespace Dotoo;
using namespace ModelParser;

using json = nlohmann::json;    /* For convinience. */


Task JsonToTask( const json& jsonData )
{
    return Dotoo::Task(
                jsonData.count("id") ? static_cast<UniqueId>(jsonData["id"]) : 0,
            QString::fromStdString( jsonData["title"] ),
            jsonData["isDone"],
            jsonData["responsible"],
            jsonData["creator"],
            QDate::fromString( QString::fromStdString( jsonData["creationDate"] ) ),
            QDate::fromString( QString::fromStdString( jsonData["dueDate"] )  ),
            jsonData["priority"],
            jsonData["relatedProject"],
            QString::fromStdString(jsonData["comment"]) );
}


json TaskToJson( const Task& task )
{
    json jsonData = {
        { "id", task.getId() },
        { "title", task.getTitle().toStdString() },
        { "isDone", task.isDone() },
        { "responsible", task.getResponsible() },
        { "creator", task.getCreator() },
        { "creationDate", task.getCreationDate().toString().toStdString() },
        { "dueDate", task.getDueDate().toString().toStdString() },
        { "priority", task.getPriority() },
        { "relatedProject", task.getRelatedProject() },
        { "comment", task.getComment().toStdString() }
    };

    return jsonData;
}


Task JsonTaskParser::BytestreamIntoTask( const QByteArray& bs ) const
{
    json jsonData = json::parse( bs.data() );
    return JsonToTask( jsonData );
}


QList<Task> JsonTaskParser::BytestreamIntoTaskList( const QByteArray& bs ) const
{
    QList<Task> taskList;
    json jsonDataAll = json::parse( bs.data() );

    /* Step through json array and create all persons: */
    for ( std::size_t i = 0 ; i < jsonDataAll.size() ; i++ )
    {
        json jsonData = jsonDataAll.at(i);
        taskList.append( JsonToTask(jsonData) );
    }

    return taskList;
}


QByteArray JsonTaskParser::TaskIntoBytestream( const Task& task ) const
{
    json jsonData = TaskToJson( task );
    return QByteArray( jsonData.dump().data() );
}


QByteArray JsonTaskParser::TaskListIntoBytestream( const QList<Task>& taskList ) const
{
    json jsonDataAll;

    for ( QList<Task>::const_iterator itTask = taskList.begin()
          ; itTask != taskList.end()
          ; itTask++ )
    {
        jsonDataAll.push_back( TaskToJson(*itTask) );
    }

    return QByteArray( jsonDataAll.dump().data() );
}

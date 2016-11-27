#include <QByteArray>
#include <QString>
#include <QDate>

#include "parsing/json.h"

#include "taskjson.h"
#include "task.h"
#include "types/tasktypes.h"


using namespace ModelParser;

using json = nlohmann::json;    /* For convinience. */



//Dotoo::Task TaskJSON::TaskFromJSON( const QByteArray& rawTask )
//{
//    json jsonData = json::parse( rawTask.data() );

//    return Dotoo::Task( jsonData["id"],
//                        jsonData["done"],
//                        jsonData["responsible"],
//                        jsonData["creator"],
//                        Dotoo::fromString(QString::fromStdString(jsonData["creation_date"])),
//                        Dotoo::fromString(QString::fromStdString(jsonData["due_date"])),
//                        jsonData["priority"],
//                        jsonData["related_project"],
//                        QString::fromStdString(jsonData["comment"] ));
//}



//QByteArray TaskJSON::JSONFromTask( const Dotoo::Task& task )
//{
//    json jsonData = {
//        { "id", task.getId() },
//        { "done", task.isDone() },
//        { "responsible", task.getResponsible() },
//        { "creator", task.getCreator() },
//        { "creation_date", Dotoo::toString(task.getCreationDate()).toStdString() },
//        { "due_date", Dotoo::toString(task.getDueDate()).toStdString() },
//        { "priority", task.getPriority() },
//        { "related_project", task.getRelatedProject() },
//        { "comment", task.getComment().toStdString() }
//    };

//    return QByteArray( jsonData.dump().data(), jsonData.size() );
//}


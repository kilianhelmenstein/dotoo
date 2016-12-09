#ifndef ASYNCDATALYR_TASK_H
#define ASYNCDATALYR_TASK_H

#include <QObject>

#include "project/libsymbolsexport.h"
#include "data/interface/datalyr_types.h"
#include "models/interface/types/commontypes.h"



namespace Dotoo {

class Task;


namespace Data {



/*!
 * \brief   The AsyncDataLyr_Task class provides an interface for requesting
 *          Task data asynchronously. Objects are designed to work with only ONE client.
 */
class AsyncDataLyr_Task : public QObject
{
    Q_OBJECT
public:
    AsyncDataLyr_Task( QObject* parent=nullptr ) : QObject( parent ) {}
    virtual ~AsyncDataLyr_Task() {}

    virtual void getAllTasks() = 0;
    virtual void getTask( UniqueId taskId ) = 0;
    virtual void createTask( const Task& newTask ) = 0;
    virtual void changeTask( const Task& changedTask ) = 0;
    virtual void deleteTask( const UniqueId taskId ) = 0;

signals:
    /*!
     * \brief   Emitted when response of getAllTasks request is received.
     *          Client is responsible for deleting allTasks list.
     */
    void responseGetAllTasks( QList<Task>* allTasks );

    /*!
     * \brief   Emitted when response of getTask request is received.
     *          Client is responsible for deleting task.
     */
    void responseGetTask( Task* task );

    /*!
     * \brief   Emitted when response of createTask request is received.
     */
    void responseCreateTask( Error_t errorCode );

    /*!
     * \brief   Emitted when response of changeTask request is received.
     */
    void responseChangeTask( Error_t errorCode );

    /*!
     * \brief   Emitted when response of deleteTask request is received.
     */
    void responseDeleteTask( Error_t errorCode );
};


} // namespace Data;
} // namespace Dotoo;

#endif // ASYNCDATALYR_TASK_H

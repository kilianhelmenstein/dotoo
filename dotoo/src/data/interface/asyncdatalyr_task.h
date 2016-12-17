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
 * \brief   The AsyncDataLyr_Task class is given to clients of AsyncDataLyr_Task
 *          to receive the responses of only their requests.
 */
class LIB_EXPORT AsyncDataLyr_TaskResponse : public QObject
{
    Q_OBJECT
signals:
    /*!
     * \brief   Emitted when response of getAllTasks request is received.
     *          Client is responsible for deleting allTasks list.
     */
    void responseGetAllTasks( QList<Task>* allTasks, Error_t errorCode );

    /*!
     * \brief   Emitted when response of getTask request is received.
     *          Client is responsible for deleting task.
     */
    void responseGetTask( Task* task, Error_t errorCode );

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



/*!
 * \brief   The AsyncDataLyr_Task class provides an interface for requesting
 *          Task data asynchronously. Objects are designed to work with only ONE client.
 */
class LIB_EXPORT AsyncDataLyr_Task : public QObject
{
    Q_OBJECT
public:
    AsyncDataLyr_Task( QObject* parent=nullptr ) : QObject( parent ) {}
    virtual ~AsyncDataLyr_Task() {}

    /*!
     * \brief   Tries to get all available tasks.
     *
     * \return  AsyncDataLyr_TaskResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_TaskResponse* getAllTasks() = 0;

    /*!
     * \brief   Tries to get the specified task.
     *
     * \return  AsyncDataLyr_TaskResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_TaskResponse* getTask( const UniqueId taskId ) = 0;

    /*!
     * \brief   Tries to create a new tasks that equals to newTask.
     *
     * \return  AsyncDataLyr_TaskResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_TaskResponse* createTask( const Task& newTask ) = 0;

    /*!
     * \brief   Tries to change the a tasks by using the attributes of
     *          changedTask. The task to change is referenced by changedTask's id.
     *
     * \return  AsyncDataLyr_TaskResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_TaskResponse* changeTask( const Task& changedTask ) = 0;

    /*!
     * \brief   Tries to delete the specified task.
     *
     * \return  AsyncDataLyr_TaskResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_TaskResponse* deleteTask( const UniqueId taskId ) = 0;
};


} // namespace Data;
} // namespace Dotoo;

#endif // ASYNCDATALYR_TASK_H

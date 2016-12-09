#ifndef DATALYR_TASK_H
#define DATALYR_TASK_H

#include <QList>

#include "project/libsymbolsexport.h"
#include "data/interface/datalyr_types.h"
#include "models/interface/types/commontypes.h"



namespace Dotoo {

class Task;


namespace Data {


/*!
 * \brief   The TaskDataLyr class defines the layer for accessing
 *          the data of model type 'Task'.
 */
class LIB_EXPORT DataLyr_Task
{
public:
    virtual ~DataLyr_Task() {}

    virtual QList<Task> getAllTasks() throw(Error_t) = 0;
    virtual Task getTask( UniqueId taskId ) throw(Error_t) = 0;
    virtual void createTask( const Task& newTask ) throw(Error_t) = 0;
    virtual void changeTask( const Task& changedTask ) throw(Error_t) = 0;
    virtual void deleteTask( const UniqueId taskId ) throw(Error_t) = 0;
};


} // namespace Data
} // namespace Dotoo

#endif // DATALYR_TASK_H

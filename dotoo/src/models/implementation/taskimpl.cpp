#include "taskimpl.h"


using namespace Dotoo;


TaskImpl::TaskImpl( const UniqueId id,
                    const bool isDone,
                    const UniqueId responsible,
                    const UniqueId creator,
                    const QDate& creationDate,
                    const QDate& dueDate,
                    const TaskPriority priority,
                    const UniqueId relatedProject,
                    const QString& comment )
    : m_id( id ),
      m_isDone( isDone ),
      m_responsible( responsible ),
      m_creator( creator ),
      m_creationDate( new QDate(creationDate) ),
      m_dueDate( new QDate(dueDate) ),
      m_priority( priority ),
      m_relatedProject( relatedProject ),
      m_comment( new QString(comment) )
{}


TaskImpl::~TaskImpl()
{}

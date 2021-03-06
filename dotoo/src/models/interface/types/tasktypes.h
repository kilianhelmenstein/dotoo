#ifndef TASKTYPES_H
#define TASKTYPES_H

#include "commontypes.h"



/******************** Namespaces ********************/

namespace Dotoo {



/********************* Typedefs *********************/

/*!
 * \brief   Represents the type for task priorities.
 */
typedef enum
{
    VeryImportant,
    Important,
    LessImportant
} TaskPriority;

} // namespace Dotoo



#endif // TASKTYPES_H

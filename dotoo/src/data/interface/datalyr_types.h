#ifndef DATALYR_TYPES_H
#define DATALYR_TYPES_H


namespace Dotoo {
namespace Data {

/*!
 * \brief   Contains all possible errors that could occur while using
 *          this layer.
 */
typedef enum {
    None = 0,
    NotFound,
    NotAvailable,
    InvalidArguments
} Error_t;


} // namespace Data
} // namespace Dotoo

#endif // DATALYR_TYPES_H

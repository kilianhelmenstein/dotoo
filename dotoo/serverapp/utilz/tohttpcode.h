/*!
 * \brief   Collection of utilities to dealing with HTTP status codes.
 *
 * \author  K.Helmenstein
 *
 * \date    2016-11-28
 */

#ifndef TOHTTPCODE_H
#define TOHTTPCODE_H

#include <qhttpresponse.h>
#include <data/interface/datalyr_types.h>



namespace HttpUtilz {

/*!
 * \brief       Translates a error code form Data::Error_t into a appropriate
 *              HTTP status code.
 *
 * \param[in]   Dotoo::Data::Error_t dataError      Error code to translate.
 *
 * \return      QHttpResponse::StatusCode           Resulting HTTP status code.
 */
inline QHttpResponse::StatusCode DataErrorIntoHttpCode( Dotoo::Data::Error_t dataError )
{
    using namespace Dotoo;

    switch ( dataError )
    {
    case Data::NotFound:
        return QHttpResponse::STATUS_NOT_FOUND;
    case Data::NotAvailable:
        return QHttpResponse::STATUS_SERVICE_UNAVAILABLE;
    case Data::InvalidArguments:
        return QHttpResponse::STATUS_BAD_REQUEST;
    default:
        return QHttpResponse::STATUS_INTERNAL_SERVER_ERROR;
    }
}

} // namespace HttpUtilz


#endif // TOHTTPCODE_H

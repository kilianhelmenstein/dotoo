#ifndef HTTP_H
#define HTTP_H

#include <project/libsymbolsexport.h>
#include <data/interface/datalyr_types.h>



namespace HttpUtilz {

/*!
 * \brief   Type for http status codes.
 */
typedef enum {
    STATUS_CONTINUE = 100,
    STATUS_SWITCH_PROTOCOLS = 101,
    STATUS_OK = 200,
    STATUS_CREATED = 201,
    STATUS_ACCEPTED = 202,
    STATUS_NON_AUTHORITATIVE_INFORMATION = 203,
    STATUS_NO_CONTENT = 204,
    STATUS_RESET_CONTENT = 205,
    STATUS_PARTIAL_CONTENT = 206,
    STATUS_MULTIPLE_CHOICES = 300,
    STATUS_MOVED_PERMANENTLY = 301,
    STATUS_FOUND = 302,
    STATUS_SEE_OTHER = 303,
    STATUS_NOT_MODIFIED = 304,
    STATUS_USE_PROXY = 305,
    STATUS_TEMPORARY_REDIRECT = 307,
    STATUS_BAD_REQUEST = 400,
    STATUS_UNAUTHORIZED = 401,
    STATUS_PAYMENT_REQUIRED = 402,
    STATUS_FORBIDDEN = 403,
    STATUS_NOT_FOUND = 404,
    STATUS_METHOD_NOT_ALLOWED = 405,
    STATUS_NOT_ACCEPTABLE = 406,
    STATUS_PROXY_AUTHENTICATION_REQUIRED = 407,
    STATUS_REQUEST_TIMEOUT = 408,
    STATUS_CONFLICT = 409,
    STATUS_GONE = 410,
    STATUS_LENGTH_REQUIRED = 411,
    STATUS_PRECONDITION_FAILED = 412,
    STATUS_REQUEST_ENTITY_TOO_LARGE = 413,
    STATUS_REQUEST_URI_TOO_LONG = 414,
    STATUS_REQUEST_UNSUPPORTED_MEDIA_TYPE = 415,
    STATUS_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
    STATUS_EXPECTATION_FAILED = 417,
    STATUS_INTERNAL_SERVER_ERROR = 500,
    STATUS_NOT_IMPLEMENTED = 501,
    STATUS_BAD_GATEWAY = 502,
    STATUS_SERVICE_UNAVAILABLE = 503,
    STATUS_GATEWAY_TIMEOUT = 504,
    STATUS_HTTP_VERSION_NOT_SUPPORTED = 505
} HttpStatusCode;



/*!
 * \brief       Translates a http status code into error code (see Data::Error_t).
 *
 * \param[in]   HttpStatusCode status           Http status code
 *
 * \return      Dotoo::Data::Error_t            Error code in a format used by data layers.
 */
inline Dotoo::Data::Error_t LIB_EXPORT DataErrorIntoHttpCode( const HttpStatusCode status )
{
    using namespace Dotoo;

    switch ( status )
    {
    case HttpUtilz::STATUS_OK:
    case HttpUtilz::STATUS_CREATED:
    case HttpUtilz::STATUS_ACCEPTED:
        return Dotoo::Data::None;
    case HttpUtilz::STATUS_BAD_REQUEST:
    case HttpUtilz::STATUS_UNAUTHORIZED:
    case HttpUtilz::STATUS_PAYMENT_REQUIRED:
    case HttpUtilz::STATUS_FORBIDDEN:
    case HttpUtilz::STATUS_METHOD_NOT_ALLOWED:
    case HttpUtilz::STATUS_NOT_ACCEPTABLE:
        return Dotoo::Data::InvalidArguments;
    case HttpUtilz::STATUS_NOT_FOUND:
        return Dotoo::Data::NotFound;
    default:
        return Dotoo::Data::NotSpecified;
    }
}

} // namespace HttpUtilz



#endif // HTTP_H

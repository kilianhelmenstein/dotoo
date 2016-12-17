/*!
 * \brief   Collection of simple tools  for working with URIs.
 *
 * \author  K.Helmenstein
 *
 * \date    2016-12-01
 */
#ifndef URIUTILZ_H
#define URIUTILZ_H

#include <QRegExp>


namespace UriUtilz {


/*!
 * \brief   Determines the selected resource id of the given resource collection.
 *
 *          Assumed input format: [...](/)<resourceCollection>/<resourceId>(/)[...]
 *
 * \param   const QString& uri                      The input uri that holds the resource id.
 *
 * \param   const QString& resourceCollection       The name of the id's resource collection.
 *
 * \return  QString         Holds the extracted resource id, if found.
 *                          If id could not be found, returns an empty string.
 */
inline QString FindResourceId( const QString& uri,
                               const QString& resourceCollection )
{
    QRegExp rexpFindId( QString("(%1\\/)(\\d*)$").arg( resourceCollection ) );

    if ( rexpFindId.indexIn( uri ) != -1 )
    {
        return rexpFindId.cap(2);
    } else
    {
        /* Id could not be found within URI: */
        return QString("");
    }
}

} // namespace HttpUtilz


#endif // URIUTILZ_H

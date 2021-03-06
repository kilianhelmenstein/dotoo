#ifndef QPROPERTYFILTERING_H
#define QPROPERTYFILTERING_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QMap>


namespace QPropertyFiltering {


typedef enum {
    AllMatching,
    OneMatching
} FilterConjunction;

/*!
 * \brief   Contains all appliable modes for QProperty filtering.
 */
typedef enum {
    PartialMatch,   /*!< Filter value will be matched partially. */
    FullMatch       /*!< Filter value will be matched completely. */
} FilterMode;


/*!
 * \brief   Possible logic bahavior for matching strategies.
 */
typedef enum {
    Included,       /*!< Equality of values will lead to a filter 'match' */
    Excluded        /*!< Equality of values will lead to NO filter 'match' */
} FilterLogic;


/*!
 * \brief       Contains all settings for filtering a QProperty of a QObject.
 */
struct FilterSetting {
    bool enabled;                   /*!< Filter setting will only be applied, if 'enabled' is true. */
    QString property;               /*!< The property's name, that will be used for matching values. */
    FilterMode mode;                /*!< Mode for this setting. */
    FilterLogic logic;              /*!< Logic for computing match. */
    QList<QVariant> matchValues;    /*!< Values that will be compared to property's current value. */
    bool matchIsMandatory;          /*!< Match is voluntary, but minimum one voluntary match must be occur! */
};



/*!
 * \brief   The QPropertyFilter class represents a collection of filter settings
 *          that can be applied on a QObject instance (by using the QProperty system).
 */
class QPropertyFilter
{
public:
    /*!
     * \brief   Installs new filter setting. Overwrites an existing one if
     *          a setting with same 'property' field already exists.
     *
     * \param   const FilterSetting& filterSetting      New filter setting.
     */
    void installFilterSettingGroup( const QList<FilterSetting>& filterSettingGroup,
                                    FilterConjunction conj );

    /*!
     * \brief   Removes all installed filter settings.
     */
    void removeAllFilterSettings()
    {
        m_appliedFilterSettings.clear();
    }


    /*!
     * \brief   Applies all filter settings to properties of 'propertyContainer'.

     * \param   const QObject& propertyContainer        Contains the properties to be filtered.
     *
     * \return  bool    true  -> Match is given for all properties of 'propertyContainer'.
     *                  false -> No match.
     */
    bool applyFilter( const QObject& propertyContainer );

private:
    /*!
     * \brief   Matches the value 'prop' agains the filter value 'val'.
     *
     * \return  bool    true  -> 'prop' and 'filterVal' match (resp. partailly. See parameter 'logic')
     *                  false -> no match.
     */
    bool matchValues( const QVariant& prop,
                      const QList<QVariant>& filterValues,
                      FilterMode mode,
                      FilterLogic logic );

private:
    QMap<FilterConjunction,QList<FilterSetting> > m_appliedFilterSettings;      /*!< This settings will be applied while filtering process. */
};


} // namespace QPropertyFiltering

#endif // QPROPERTYFILTERING_H

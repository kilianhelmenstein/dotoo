#include "qpropertyfiltering.h"



namespace QPropertyFiltering {



void QPropertyFilter::installFilterSettingGroup( const QList<FilterSetting>& filterSettingGroup,
                                                 FilterConjunction conj )
{
    m_appliedFilterSettings.insertMulti( conj, filterSettingGroup );
}


bool QPropertyFilter::applyFilter( const QObject& propertyContainer )
{
    if ( m_appliedFilterSettings.isEmpty() )
    {
        return true;        // No filtering if filter setting list is empty.
    }


    bool result = false;

    for ( QMap<FilterConjunction,QList<FilterSetting> >::iterator currentFilterGroup = m_appliedFilterSettings.begin() ;
          currentFilterGroup != m_appliedFilterSettings.end() ;
          ++currentFilterGroup )
    {

        foreach ( FilterSetting filterSetting, currentFilterGroup.value() )
        {
            if ( filterSetting.enabled )    // Only apply setting if 'enabled' is true!
            {
                if ( matchValues( propertyContainer.property(filterSetting.property.toLatin1()),
                                  filterSetting.matchValues,
                                  filterSetting.mode, filterSetting.logic ) )
                {
                    // Match:
                    result = true;
                    if ( currentFilterGroup.key() == OneMatching )
                    {
                        break;  // Match is given for this filter group.
                    }
                } else
                {
                    // NO Match:
                    if ( currentFilterGroup.key() == AllMatching )
                    {
                        result = false;
                        break;  // Match is NOT given for this filter group.
                    }
                }
            }
        }

        // Check matching result for this filter group:
        if ( result == false )
        {
            return false;
        } else
        {
            result = false;     // reset for next filter setting group
        }
    }

    return true;
}


bool QPropertyFilter::matchValues( const QVariant& prop,
                                   const QList<QVariant>& filterValues,
                                   FilterMode mode,
                                   FilterLogic logic )
{
    foreach ( QVariant filterVal, filterValues )
    {
        switch ( mode )
        {
        case PartialMatch:
            if ( prop.type() == QVariant::String )
            {
                if ( prop.toString().contains( filterVal.toString(),
                                               Qt::CaseInsensitive ) ) return (logic == Included);
            } else
            {
                if ( prop == filterVal ) return (logic == Included);
            }
            break;
        case FullMatch:
            if ( prop == filterVal ) return ( logic == Included);
            break;
        }
    }

    return (logic == Excluded);
}


} // namespace QPropertyFiltering

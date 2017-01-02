#include "qpropertyfiltering.h"



namespace QPropertyFiltering {



bool QPropertyFilter::applyFilter( const QObject& propertyContainer )
{
    if ( m_appliedFilterSettings.isEmpty() )
    {
        return true;        // No filtering if filter setting list is empty.
    }

    bool result = false;

    foreach ( FilterSetting filterSetting, m_appliedFilterSettings )
    {
        if ( filterSetting.enabled )    // Only apply setting if 'enabled' is true!
        {
            if ( matchValues( propertyContainer.property(filterSetting.property.toLatin1()),
                              filterSetting.matchValues,
                              filterSetting.mode, filterSetting.logic ) )
            {
                // Match:
                result = true;
            } else
            {
                // NO Match:
                result = false;
                if ( filterSetting.matchIsMandatory ) break;
            }
        }
    }

    return result;
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
            if ( prop == filterVal ) return (logic == Included);
        case FullMatch:
            if ( prop.type() == QVariant::String )
            {
                if ( prop.toString().contains( filterVal.toString(),
                                               Qt::CaseInsensitive ) ) return (logic == Included);
            } else
            {
                if ( prop == filterVal ) return (logic == Included);
            }
        }
    }

    return (logic == Excluded);
}


} // namespace QPropertyFiltering

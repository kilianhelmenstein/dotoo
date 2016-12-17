#ifndef TEXTVIEWUTILZ_H
#define TEXTVIEWUTILZ_H

class QLabel;
class QString;



namespace TextViewUtilz {

/*!
 * \brief           Using the label's font to set a elided text if string is too long.
 *
 * \param[in/out]   QLable* label       Using label's font for create QFontMetrics.
 *                                      Using label's setText for writing 'text'.
 *
 * \param[in]       QString text        String, that shall be presented by 'label'.
 */
void SetTextToLabel( QLabel* label, const QString& text );


} // namespace Textviewutilz

#endif // TEXTVIEWUTILZ_H

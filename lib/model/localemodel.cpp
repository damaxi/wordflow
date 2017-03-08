#include "localemodel.h"

#include <QLocale>

LocaleModel::LocaleModel(QObject *parent) :
    QAbstractListModel(parent),
    m_languages()
{
    QList<QLocale> allLocales = QLocale::matchingLocales(
                QLocale::AnyLanguage,
                QLocale::AnyScript,
                QLocale::AnyCountry);

    QSet<QString> languages;
    for(const QLocale &locale : allLocales) {
        languages.insert(QLocale::languageToString(locale.language()));
    }
    m_languages = languages.toList();
    qStableSort(m_languages);
}

int LocaleModel::rowCount(const QModelIndex &parent) const
{
    return m_languages.count();
}

QVariant LocaleModel::data(const QModelIndex &index, int role) const
{
    return m_languages[index.row()];
}

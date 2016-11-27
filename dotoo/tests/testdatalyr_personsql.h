#ifndef TESTDATALYR_PERSONSQL_H
#define TESTDATALYR_PERSONSQL_H

#include <QObject>
#include <QtTest/QTest>

namespace Dotoo {
namespace Data {
    class DataLyr_Person;
}
}


class TestDataLyr_PersonSql : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void createPerson();
    void deletePerson();

    void cleanupTestCase();

private:
    Dotoo::Data::DataLyr_Person* m_dut;
};

#endif // TESTDATALYR_PERSONSQL_H

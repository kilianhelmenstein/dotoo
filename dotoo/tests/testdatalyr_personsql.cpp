#include <QFile>
#include <QDebug>

#include "testdatalyr_personsql.h"

#include "models/interface/person.h"
#include "data/implementation/datalyr_personsql.h"



void TestDataLyr_PersonSql::initTestCase()
{
    m_dut = new Dotoo::Data::DataLyr_PersonSql( "unit_test.db3",
                                                "persons" );
}


void TestDataLyr_PersonSql::createPerson()
{
    bool newPersonFound = false;
    Dotoo::Person newPerson( 0,
                             Dotoo::PersonName_t( "test_forename", "test_name" ),
                             "this is a test" );

    /* Create person: */
    m_dut->createPerson( newPerson );

    /* Read all persons and look for new one: */
    QList<Dotoo::Person> allPersons = m_dut->getAllPersons();

    foreach ( Dotoo::Person p, allPersons )
    {
        if ( p.getName() == newPerson.getName()
             && p.getComment() == newPerson.getComment() )
        {
            newPersonFound = true;
        }
    }

    QVERIFY(newPersonFound);
}


void TestDataLyr_PersonSql::deletePerson()
{
    bool newPersonFound = false;
    Dotoo::Person newPerson( 0,
                             Dotoo::PersonName_t( "test_forename", "test_name" ),
                             "this is a test" );

    /* Create person: */
    m_dut->createPerson( newPerson );

    /* Read all persons and look for new one: */
    QList<Dotoo::Person> allPersons = m_dut->getAllPersons();

    foreach ( Dotoo::Person p, allPersons )
    {
        if ( p.getName() == newPerson.getName()
             && p.getComment() == newPerson.getComment() )
        {
            newPersonFound = true;
            break;
        }
    }

    QVERIFY(newPersonFound);

    /* Delete person: */
    m_dut->deletePerson( 1 );

    /* Read all persons and look for new one: */
    allPersons = m_dut->getAllPersons();

    newPersonFound = false;
    foreach ( Dotoo::Person p, allPersons )
    {
        if ( p.getName() == newPerson.getName()
             && p.getComment() == newPerson.getComment()
             && p.getId() == 1 )
        {
            newPersonFound = true;
        }
    }

    QVERIFY( newPersonFound == false );
}


void TestDataLyr_PersonSql::cleanupTestCase()
{
    delete m_dut;
    m_dut = nullptr;

    /* Remove database: */
    QFile dbFile( "unit_test.db3" );
    dbFile.remove();
}

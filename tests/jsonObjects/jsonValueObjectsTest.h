/**
 *  @file    jsonValueObjectsTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONVSLUROBJECTTEST_H
#define JSONVSLUROBJECTTEST_H

#include <testing/commonTest.h>

namespace Kitsune
{
namespace Json
{
class JsonValue;

class JsonValueObjectsTest: public Kitsune::CommonTest
{
public:
    JsonValueObjectsTest();
private:
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void cleanupTestCase();

    JsonValue* m_valueString = nullptr;
    JsonValue* m_valueInt = nullptr;
    JsonValue* m_valueFloat = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONVSLUROBJECTTEST_H

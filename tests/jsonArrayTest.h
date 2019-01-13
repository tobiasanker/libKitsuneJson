/**
 *  @file    jsonArrayTest.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef JSONARRAYTEST_H
#define JSONARRAYTEST_H

#include <../../../LibKitsuneCommon/include/libKitsuneCommon/commonTest.h>

namespace Kitsune
{
namespace Json
{
class JsonArray;

class JsonArrayTest: public Kitsune::CommonTest
{
public:
    JsonArrayTest();
private:
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void removeTestCase();
    void cleanupTestCase();

    JsonArray* m_array = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONARRAYTEST_H

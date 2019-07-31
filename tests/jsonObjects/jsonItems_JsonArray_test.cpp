/**
 *  @file    jsonItems_JsonArray_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItems_JsonArray_test.hpp"
#include <jsonItems.hpp>

namespace Kitsune
{
namespace Json
{

JsonItems_JsonArray_Test::JsonItems_JsonArray_Test()
    : Kitsune::CommonTest("JsonItems_JsonArray_Test")
{
    parseString_test();
    append_test();

    operator_test();
    get_test();
    getSize_test();
    remove_test();
    copy_test();
    print_test();
    getType_test();
    isValue_isObject_isArray_test();
    toValue_toObject_toArray_test();
    toString_toInt_toFloat_test();
}

void
JsonItems_JsonArray_Test::parseString_test()
{

}

void
JsonItems_JsonArray_Test::append_test()
{
    JsonArray array;
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    UNITTEST(array.append(defaultValue.copy()), true);
    UNITTEST(array.append(stringValue.copy()), true);
    UNITTEST(array.append(intValue.copy()), true);
    UNITTEST(array.append(floatValue.copy()), true);

    UNITTEST(array.append(nullptr), false);
}

void
JsonItems_JsonArray_Test::operator_test()
{
    JsonArray array = initTestArray();

    UNITTEST(array[1]->toString(), "test");
    UNITTEST(array["2"]->toInt(), 42);

    bool isNullptr = array[10] == nullptr;
    UNITTEST(isNullptr, true);
}

void
JsonItems_JsonArray_Test::get_test()
{
    JsonArray array = initTestArray();

    UNITTEST(array.get(1)->toString(), "test");
    UNITTEST(array.get("2")->toInt(), 42);

    bool isNullptr = array.get(10) == nullptr;
    UNITTEST(isNullptr, true);
}

void
JsonItems_JsonArray_Test::getSize_test()
{
    JsonArray array = initTestArray();
    UNITTEST(array.getSize(), 4);
}

void
JsonItems_JsonArray_Test::remove_test()
{
    JsonArray array = initTestArray();
    UNITTEST(array.remove(1), true);
    UNITTEST(array.remove("2"), true);

    UNITTEST(array.get(1)->toInt(), 42);
    UNITTEST(array.getSize(), 2);

    UNITTEST(array.remove(10), false);
}

void
JsonItems_JsonArray_Test::copy_test()
{
    JsonArray array = initTestArray();

    JsonArray* arrayCopy = dynamic_cast<JsonArray*>(array.copy());

    bool isNullptr = arrayCopy == nullptr;
    UNITTEST(isNullptr, false);

    UNITTEST(array.print(), arrayCopy->print());
}

void
JsonItems_JsonArray_Test::print_test()
{
    JsonArray array = initTestArray();

    std::string compare = "[\"\",\"test\",42,42.500000]";
    UNITTEST(array.print(), compare);

    compare = "[\n"
              "    \"\",\n"
              "    \"test\",\n"
              "    42,\n"
              "    42.500000\n"
              "]";
    UNITTEST(array.print(nullptr, true), compare);
}

void
JsonItems_JsonArray_Test::getType_test()
{
    JsonArray array = initTestArray();
    UNITTEST(array.getType(), JsonItem::ARRAY_TYPE);
}

void
JsonItems_JsonArray_Test::isValue_isObject_isArray_test()
{
    JsonArray array = initTestArray();
    UNITTEST(array.isValue(), false);
    UNITTEST(array.isObject(), false);
    UNITTEST(array.isArray(), true);
}

void
JsonItems_JsonArray_Test::toValue_toObject_toArray_test()
{
    JsonArray array = initTestArray();

    bool isNullptr = array.toObject() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = array.toArray() == nullptr;
    UNITTEST(isNullptr, false);

    isNullptr = array.toValue() == nullptr;
    UNITTEST(isNullptr, true);
}

void
JsonItems_JsonArray_Test::toString_toInt_toFloat_test()
{
    JsonArray array = initTestArray();
    UNITTEST(array.toString(), "");
    UNITTEST(array.toInt(), 0);
    UNITTEST(array.toFloat(), 0.0f);
}

JsonArray
JsonItems_JsonArray_Test::initTestArray()
{
    JsonArray array;
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    array.append(defaultValue.copy());
    array.append(stringValue.copy());
    array.append(intValue.copy());
    array.append(floatValue.copy());

    return array;
}

}  // namespace Json
}  // namespace Kitsune

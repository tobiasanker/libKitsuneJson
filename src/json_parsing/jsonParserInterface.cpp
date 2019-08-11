/**
 *  @file    jsonParserInterface.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <json_parsing/jsonParserInterface.hpp>
#include <jsonParser.hpp>

#include <data_structure/dataItems.hpp>

using Kitsune::Common::DataItem;
using Kitsune::Common::DataArray;
using Kitsune::Common::DataValue;
using Kitsune::Common::DataObject;

# define YY_DECL \
    Kitsune::Json::JsonParser::symbol_type jsonlex (Kitsune::Json::JsonParserInterface& driver)
YY_DECL;

namespace Kitsune
{
namespace Json
{

/**
 * @brief The class is the interface for the bison-generated parser.
 *        It starts the parsing-process and store the returned values.
 *
 * @param traceParsing If set to true, the scanner prints all triggered rules.
 *                     It is only for better debugging.
 */
JsonParserInterface::JsonParserInterface(const bool traceParsing)
{
    m_traceParsing = traceParsing;
}

/**
 * @brief Start the scanner and parser
 *
 * @param inputFile string which should be parsed
 *
 * @return true, if parsing was successful, else false
 */
bool
JsonParserInterface::parse(const std::string &inputString)
{
    // init global values
    m_inputString = inputString;
    m_errorMessage = "";
    m_output = nullptr;

    // run parser-code
    this->scan_begin(inputString);
    Kitsune::Json::JsonParser parser(*this);
    int res = parser.parse();
    this->scan_end();

    if(res != 0) {
        return false;
    }
    return true;
}

/**
 * @brief remove quotes at the beginning and end of a string
 *
 * @param input input-string
 *
 * @return cleared string
 */
std::string
JsonParserInterface::removeQuotes(std::string input)
{
    if(input.length() == 0) {
        return input;
    }

    if(input[0] == '\"' && input[input.length()-1] == '\"')
    {
        std::string result = "";
        for(uint32_t i = 1; i < input.length()-1; i++)
        {
            result += input[i];
        }
        return result;
    }
    return input;
}

/**
 * @brief Is called for the parser after successfully parsing the input-string
 *
 * @param output parser-output as QDataArray
 */
void
JsonParserInterface::setOutput(DataObject* output)
{
     m_output = output;
}

/**
 * getter for the json-output of the parser
 *
 * @return parser-output as QDataArray
 */
DataObject*
JsonParserInterface::getOutput() const
{
    return m_output;
}

/**
 * @brief Is called from the parser in case of an error
 *
 * @param location location-object of the bison-parser,
 *                 which contains the informations of the location
 *                 of the syntax-error in the parsed string
 * @param message error-specific message from the parser
 */
void
JsonParserInterface::error(const Kitsune::Json::location& location,
                           const std::string& message)
{
    // get the broken part of the parsed string
    const uint32_t errorStart = location.begin.column;
    const uint32_t errorLength = location.end.column - location.begin.column;
    const std::string errorStringPart = m_inputString.substr(errorStart, errorLength);

    // build error-message
    m_errorMessage =  "error while parsing json-template \n";
    m_errorMessage += "parser-message: " + message + " \n";
    m_errorMessage += "line-number: " + std::to_string(location.begin.line) + " \n";
    m_errorMessage += "position in line: " + std::to_string(location.begin.column) + " \n";
    m_errorMessage += "broken part in template: \"" + errorStringPart + "\" \n";

    //std::cout<<"m_errorMessage: "<<m_errorMessage<<std::endl;
}

/**
 * @brief getter fot the error-message in case of an error while parsing
 *
 * @return error-message
 */
std::string
JsonParserInterface::getErrorMessage() const
{
    return m_errorMessage;
}

}  // namespace Json
}  // namespace Kitsune

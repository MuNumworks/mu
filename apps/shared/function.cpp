#include "function.h"
#include "poincare_helpers.h"
#include "poincare/src/parsing/parser.h"
#include <ion/unicode/utf8_decoder.h>
#include <string.h>
#include <cmath>
#include <assert.h>

using namespace Poincare;

namespace Shared {

bool Function::BaseNameCompliant(const char * baseName, NameNotCompliantError * error) {
  assert(baseName[0] != 0);

  UTF8Decoder decoder(baseName);
  CodePoint c = decoder.nextCodePoint();
  if (c.isDecimalDigit()) {
    // The name cannot start with a number
    if (error != nullptr) {
      *error = NameNotCompliantError::NameCannotStartWithNumber;
    }
    return false;
  }

  // The name should only have allowed characters
  while (c != UCodePointNull) {
    // FIXME '_' should be accepted but not as first character
    // TODO Factor this piece of code with similar one in the Parser
    if (!(c.isDecimalDigit()) || c.isLatinLetter() || c == '_') {
      if (error != nullptr) {
        *error = NameNotCompliantError::CharacterNotAllowed;
      }
      return false;
    }
    c = decoder.nextCodePoint();
  }

  // The name should not be a reserved name
  if (Parser::IsReservedName(baseName, strlen(baseName))) {
    if (error != nullptr) {
      *error = NameNotCompliantError::ReservedName;
    }
    return false;
  }
  return true;
}

bool Function::isActive() const {
  return recordData()->isActive();
}

KDColor Function::color() const {
  return recordData()->color();
}

void Function::setActive(bool active) {
  recordData()->setActive(active);
}

int Function::printValue(double cursorT, double cursorX, double cursorY, char * buffer, int bufferSize, int precision, Poincare::Context * context) {
  return PoincareHelpers::ConvertFloatToText<double>(cursorY, buffer, bufferSize, precision);
}

int Function::name(char * buffer, size_t bufferSize) {
  return SymbolAbstract::TruncateExtension(buffer, fullName(), bufferSize);
}

int Function::nameWithArgument(char * buffer, size_t bufferSize) {
  int funcNameSize = name(buffer, bufferSize);
  assert(funcNameSize > 0);
  size_t result = funcNameSize;
  assert(result <= bufferSize);
  buffer[result++] = '(';
  assert(result <= bufferSize);
  assert(UTF8Decoder::CharSizeOfCodePoint(symbol()) <= 2);
  result += UTF8Decoder::CodePointToChars(symbol(), buffer+result, bufferSize-result);
  assert(result <= bufferSize);
  result += strlcpy(buffer+result, ")", bufferSize-result);
  return result;
}

Function::RecordDataBuffer * Function::recordData() const {
  assert(!isNull());
  Ion::Storage::Record::Data d = value();
  return reinterpret_cast<RecordDataBuffer *>(const_cast<void *>(d.buffer));
}

}

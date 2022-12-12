#ifndef VALUED_TOKEN_H
#define VALUED_TOKEN_H

#include "token.h"

namespace s21 {

template <class T>
class ValuedToken : public Token {
 public:
  ValuedToken() : Token(), value_() {}
  ValuedToken(const T& value, const std::string& strVal)
      : Token(kNumber, kNoPriority, strVal), value_(value) {}

  virtual ~ValuedToken() {}

  // Access value
  T getValue() { return value_; }

 private:
  T value_;
};
}  // namespace s21

#endif  // VALUED_TOKEN_H

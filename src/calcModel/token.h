#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace s21 {
enum TokenType {
  kNumber,
  kLeftBracket,
  kRightBracket,
  kFunction,
  kUnaryOperator,
  kBinaryOperator,
  kVariable
};

enum Priority { kNoPriority, kLow, kMedium, kHigh, kHighest };

class Token {
 public:
  Token() : type_(kNumber), priority_(kNoPriority), strVal_(""){};
  virtual ~Token(){};
  Token(TokenType t, Priority pr, const std::string& strVal)
      : type_(t), priority_(pr), strVal_(strVal) {}
  Token(const Token& other) {
    type_ = other.type_;
    priority_ = other.priority_;
  }

  Token(Token&& other) {
    type_ = other.type_;
    priority_ = other.priority_;
  }

  TokenType getType() { return type_; }
  void setType(TokenType type) { type_ = type; }
  void setStrValue(const std::string& strVal) { strVal_ = strVal; }
  std::string getStrValue() { return strVal_; }
  Priority getPriority() { return priority_; }
  void setPriority(Priority priority) { priority_ = priority; }

 private:
  TokenType type_;
  Priority priority_;
  std::string strVal_;
};
}  // namespace s21

#endif  // TOKEN_H

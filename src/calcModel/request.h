#ifndef REQUEST_H
#define REQUEST_H

#include <deque>
#include <string>

#include "token.h"

namespace s21 {

class Request {
 public:
  // Constructors and destructors
  Request();
  ~Request();

  // Methods
  void makeNotation();
  void setLine(const std::string& line);
  std::string getLine();
  void resetRequest();
  void processLine();
  std::string getStringLexeme(const std::string& str, bool fromBeginning);
  bool isRequestValid();
  Token* getTokenFromLexeme(const std::string& lexeme);
  bool isInputValid();
  std::deque<Token*>* getNotation();
  int getLastElementLength();

 private:
  std::deque<Token*>* tokens_;
  std::deque<Token*>* notation_;
  std::string line_;

  bool isValidRequest_;
  bool isUnaryOperation(const std::string& lexeme);
  void processIfOperator(std::deque<Token*>* tmp, Token* token, TokenType type);
  void processIfRightBracket(std::deque<Token*>* tmp, TokenType type);
  void processRemaining(std::deque<Token*>* tmp);
  void clearDeque(std::deque<Token*>* deque);

  // Копирование этих элементов не предусмотрено, функции сделаны приватными, в
  // случае попытки копирования компилятор покажет ошибку
  Request(const Request& other);
  Request& operator=(const Request& other);
};
}  // namespace s21

#endif

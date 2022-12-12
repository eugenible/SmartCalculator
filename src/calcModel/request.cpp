#include "request.h"

#include <ctype.h>

#include <iostream>
#include <regex>
#include <set>

#include "functions.h"
#include "operations.h"
#include "token.h"
#include "valued_token.h"

using namespace s21;

Request::Request() : tokens_(nullptr), line_(""), isValidRequest_(true) {
  tokens_ = new std::deque<Token*>();
  notation_ = new std::deque<Token*>();
}

Request::~Request() {
  resetRequest();
  delete tokens_;
  delete notation_;
}

std::string Request::getLine() { return line_; }

std::string Request::getStringLexeme(const std::string& str,
                                     bool fromBeginning) {
  std::set<std::string> patterns = {
      "mod",  "cos",  "sin",
      "tan",  "acos", "asin",
      "atan", "sqrt", "ln",
      "log",  "\\+",  "-",
      "\\*",  "\\/",  "\\^",
      "\\(",  "\\)",  "((?:0|[1-9]\\d*)(?:\\.\\d+)?(?:[eE][+\\-]?\\d+)?)",
      "x"};
  std::string lexeme = "";

  for (auto& in : patterns) {
    std::string pattern = fromBeginning ? "^" + in : in + "$";
    std::regex rgx(pattern);
    std::smatch match;
    if (std::regex_search(str, match, rgx)) {
      lexeme = match[0];
      break;
    }
  }

  return lexeme;
}

bool Request::isRequestValid() { return isValidRequest_; }

void Request::setLine(const std::string& line) { line_ = line; }

bool Request::isUnaryOperation(const std::string& lexeme) {
  if (lexeme != "+" && lexeme != "-") return false;
  if (tokens_->size() == 0) return true;
  Token* lastElem = tokens_->at(tokens_->size() - 1);
  if (tokens_->empty() || lastElem->getType() == kBinaryOperator ||
      (lastElem->getType() == kLeftBracket))
    return true;
  return false;
}

Token* Request::getTokenFromLexeme(const std::string& lexeme) {
  if (lexeme == "mod") return new Modulo();
  if (lexeme == "cos") return new Cosine();
  if (lexeme == "sin") return new Sine();
  if (lexeme == "tan") return new Tangent();
  if (lexeme == "acos") return new ArcCosine();
  if (lexeme == "asin") return new ArcSine();
  if (lexeme == "atan") return new ArcTangent();
  if (lexeme == "sqrt") return new SquareRoot();
  if (lexeme == "ln") return new LogN();
  if (lexeme == "log") return new Log();
  if (lexeme == "+") {
    if (isUnaryOperation(lexeme)) return new UnaryPlus();
    return new Sum();
  }
  if (lexeme == "-") {
    if (isUnaryOperation(lexeme)) return new UnaryMinus();
    return new Subtraction();
  }
  if (lexeme == "*") return new Mul();
  if (lexeme == "/") return new Division();
  if (lexeme == "^") return new Power();
  if (lexeme == "(" || lexeme == ")") {
    Token* token = new ValuedToken<std::string>(lexeme, lexeme);
    TokenType type = (lexeme == "(") ? kLeftBracket : kRightBracket;
    token->setType(type);
    return token;
  }

  if (lexeme == "x") {
    double default_value = 0;
    Token* token = new ValuedToken<double>(default_value, "x");
    token->setType(kVariable);
    return token;
  }

  if (std::regex_match(
          lexeme,
          std::regex("((?:0|[1-9]\\d*)(?:\\.\\d+)?(?:[eE][+\\-]?\\d+)?)")))
    return new ValuedToken<double>(std::stod(lexeme), lexeme);

  return nullptr;
}

void Request::clearDeque(std::deque<Token*>* deque) {
  if (deque) {
    for (size_t i = 0; i < deque->size(); ++i) {
      if (deque->at(i)) delete deque->at(i);
      deque->at(i) = nullptr;
    }
    deque->clear();
  }
}

bool Request::isInputValid() {
  int leftBrackets = 0;
  int rightBrackets = 0;
  TokenType current;
  TokenType prev;

  if (tokens_->empty()) return false;  // Пустой запрос
  for (size_t i = 0; i < tokens_->size(); ++i) {
    current = tokens_->at(i)->getType();
    if (i != 0) prev = tokens_->at(i - 1)->getType();
    if (current == kLeftBracket) leftBrackets++;
    if (current == kRightBracket) rightBrackets++;
    if (i != 0 && ((current == kLeftBracket && prev == kRightBracket) ||
                   (current == kRightBracket && prev == kLeftBracket)))
      return false;  // пустые скобки
    if (i != 0 && current == kBinaryOperator && prev == kBinaryOperator)
      return false;  // два бинарных оператора подряд ** /+
    if (i != 0 && ((current == kVariable && prev == kNumber) ||
                   (current == kNumber && prev == kVariable)))
      return false;  // случай 10х или х10
  }

  if (leftBrackets != rightBrackets)
    return false;  // кол-во скобок не совпадает
  return true;
}

void Request::processLine() {
  std::string line = line_;
  while (line.length() > 0) {
    std::string lexeme = getStringLexeme(line, true);
    if (lexeme == "") {
      isValidRequest_ = false;
      return;
    }
    line = (line).substr(lexeme.length(), (line).length());
    Token* token = getTokenFromLexeme(lexeme);
    tokens_->push_back(token);
  }
  if (!isInputValid()) {
    isValidRequest_ = false;
    return;
  }
  makeNotation();
}

void Request::processIfOperator(std::deque<Token*>* tmp, Token* token,
                                TokenType type) {
  Token* tmpToken = nullptr;
  if (type == kUnaryOperator || type == kBinaryOperator) {
    while (!tmp->empty() &&
           token->getPriority() <= (tmpToken = tmp->back())->getPriority()) {
      tmp->pop_back();
      notation_->push_back(tmpToken);
    }
    tmp->push_back(token);
  }
}

void Request::processIfRightBracket(std::deque<Token*>* tmp, TokenType type) {
  Token* tmpToken = nullptr;
  if (type == kRightBracket) {
    bool foundBracket = false;
    while (!tmp->empty()) {
      tmpToken = tmp->back();
      tmp->pop_back();
      if (tmpToken->getType() == kLeftBracket) {
        foundBracket = true;
        break;
      }
      notation_->push_back(tmpToken);
    }
    // Если лексема на вершине стека — функция, перекладываем её в выходную
    // очередь.
    if (!foundBracket) {
      isValidRequest_ = false;
    } else if (!tmp->empty() &&
               (tmpToken = tmp->back())->getType() == kFunction) {
      tmp->pop_back();
      notation_->push_back(tmpToken);
    }
  }
}

void Request::processRemaining(std::deque<Token*>* tmp) {
  Token* tmpToken = nullptr;
  while (isValidRequest_ && !tmp->empty()) {
    tmpToken = tmp->back();
    if (tmpToken->getType() == kLeftBracket ||
        tmpToken->getType() == kRightBracket) {
      isValidRequest_ = false;
      continue;
    }
    tmp->pop_back();
    notation_->push_back(tmpToken);
  }
}

void Request::makeNotation() {
  std::deque<Token*> tmp;
  Token* token = nullptr;
  TokenType type;
  for (size_t i = 0; isValidRequest_ && i < tokens_->size(); ++i) {
    token = tokens_->at(i);
    type = token->getType();
    if (type == kNumber || type == kVariable) notation_->push_back(token);
    if (type == kFunction || type == kLeftBracket) tmp.push_back(token);
    processIfOperator(&tmp, token, type);
    processIfRightBracket(&tmp, type);
  }

  // Докидываем операции из стака в результат
  if (isValidRequest_) processRemaining(&tmp);
}

void Request::resetRequest() {
  isValidRequest_ = true;
  line_ = "";
  clearDeque(tokens_);
  notation_->clear();
}

std::deque<Token*>* Request::getNotation() { return notation_; }

int Request::getLastElementLength() {
  const char& lastChar = line_.at(line_.length() - 1);
  if ((lastChar >= '0' && lastChar <= '9') || lastChar == '.' ||
      lastChar == 'e' || lastChar == 'E')
    return 1;
  std::string lexeme = getStringLexeme(line_, false);
  return (lexeme == "") ? 1 : lexeme.length();
}

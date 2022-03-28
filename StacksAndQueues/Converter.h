#include <string>
#include <iostream>

#include "Queue.h"
#include "Stack.h"
#include "Element.h"

#ifndef CONVERTER_H
#define CONVERTER_H
namespace bavykin
{
  class Converter
  {
  public:
    Converter(std::string&);

    Converter& toPostfix();
    long long calculate();

  private:
    queue<element> m_InfixQueue;
    stack<element> m_Stack;
    queue<element> m_PostfixQueue;

    void setInfixQueue(std::string);
    queue<element> splitAndTransform(std::string) const;
  };
}
#endif

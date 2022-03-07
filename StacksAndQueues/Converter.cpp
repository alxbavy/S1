#include "Converter.h"

void Converter::setInfixQueue(std::string line)
{
	m_InfixQueue = splitAndTransform(line);
}

// "( 5 + 15 ) / ( 4 + 7 � 1 )" -> Queue{}
queue<element> Converter::splitAndTransform(std::string line, char sep = ' ')
{
	queue<element> tempQueue;
	int i = 0;
	int tokenCount = 0;
	std::string token = "";
	while (i < sizeof(line)) {

		token[tokenCount] = line[i];
		tokenCount++;
		if (line[i] == sep) {
			tempQueue.push(token);
			token = "";
		}
		else {

			continue;

		}

		i++;

	}
	return tempQueue;
}

Converter::Converter(std::string& inputLine)
{
	setInfixQueue(inputLine); // fills in m_Infix field
}

Converter& Converter::toPostfix()
{
	using type = element::Type;

	while (!m_InfixQueue.isEmpty())
	{
		element now = m_InfixQueue.pop();

		switch (now.getType())
		{
		case type::openParenthesis:
			m_Stack.push(now);
			break;
		case type::digit:
			m_PostfixQueue.push(now);
			break;
		case type::closeParenthesis:
			now = m_Stack.pop();
			while (now.getType() != type::openParenthesis)
			{
				m_PostfixQueue.push(now);
				if (m_Stack.getCount() == 0) 
				{
					throw "Error: Check the quantity of brackets!";
				}
				now = m_Stack.pop();
			}
			break;
		case type::operators:
			while ()
			{

			}
			break;
		}
	}
	return;
}

long long Converter::calculate()
{
	if (!m_PostfixQueue.isEmpty())
	{
		/*
		* Calc PostfixQueue to long long
		*/

		using type = element::Type;

		stack<long long> out;

		m_PostfixQueue.reverse();

		while (!m_PostfixQueue.isEmpty()) 
		{
			auto now = m_PostfixQueue.pop();

			if (now.getType() == type::digit) 
			{
				long long nowDigit = static_cast<long long>(now);

				out.push(nowDigit);
			}
			else if (now.getType() == type::operators) 
			{
				long long b = out.pop();
				long long a = out.pop();

				if (now.getElement()[0] == '%') 
				{
					out.push(((a % b) + b) % b);
				}
				else 
				{
					out.push(now.calculate(a, b));
				}
			}
		}

		return out[0]; // ��� � ��, ���� ��������� ��� ������
	}
}
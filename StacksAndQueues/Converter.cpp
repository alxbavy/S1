#include "Converter.h"


void Converter::setInfixQueue(std::string line)
{
	m_InfixQueue = splitAndTransform(line);
}

// "( 5 + 15 ) / ( 4 + 7 � 1 )" -> Queue{}
queue<element> Converter::splitAndTransform(std::string line, const char sep)
{
	queue<element> tempQueue;

	std::string temp = "";
	int i = 0;

	while (i < line.size())
	{
		temp = "";

		if (line[i] == ' ')
		{
			i++;
			continue;
		}
		else if (!std::isdigit(line[i]))
		{
			temp = line[i];
			i++;
		}
		else
		{
			while (std::isdigit(line[i]))
			{
				temp += line[i];
				i++;
			}
		}

		element now = element(temp);
		tempQueue.push(now);
	}

	return tempQueue;
}

Converter::Converter(std::string& Line)
{
	setInfixQueue(Line); // fills in m_Infix field
}

Converter& Converter::toPostfix()
{
	using type = element::Type;

	while (!m_InfixQueue.isEmpty())
	{
		element now = m_InfixQueue.pop();
		std::cout << m_InfixQueue << std::endl;
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
			now = m_InfixQueue.pop();

			if (m_Stack.isEmpty())
			{
				m_Stack.push(now);
			}
			else if (now.getOperatorId() <= m_Stack.peek().getOperatorId()) // ������� ����� while - ����� ���� ��������� ���������� �����
			{
				m_PostfixQueue.push(m_Stack.pop());
				m_Stack.push(now);
			}
			else
			{
				m_Stack.push(now);
			}
			break;
		}
	}
	return *this;
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
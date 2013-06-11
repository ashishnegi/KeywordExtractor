#pragma once

#include <iostream>
#include <string>

class MyException {
	std::string msg;
	public:
	MyException (const std::string &);	
	friend std::ostream &operator<<(std::ostream & stream, MyException & exp);
};

class IllegalStringException : public MyException {
	public:
	IllegalStringException(std::string _msg) : MyException(_msg) {
	}
};
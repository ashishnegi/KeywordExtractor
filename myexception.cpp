#include "myexception.h"

MyException :: MyException (const std::string & _msg) : msg(_msg) {
}

std::ostream & operator<<(std::ostream &stream, MyException & exp) {
	stream << exp.msg;
	return stream;
}


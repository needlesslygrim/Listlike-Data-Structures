//
// Created by erickth on 14/05/23.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class empty_list_exception : public std::exception {
  public:
	explicit empty_list_exception(const char *msg) : m_msg(msg) {}
	const char *what() { return m_msg; }

  protected:
	const char *m_msg;
};

#endif // EXCEPTIONS_H

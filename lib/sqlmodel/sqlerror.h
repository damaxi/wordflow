#ifndef SQLERROR_H
#define SQLERROR_H

#include <exception>
#include <string>

class SqlError : public std::exception
{
public:
    SqlError(const std::string& sqlmsg);
    virtual const char* what() const noexcept override
    {
        return m_sqlmsg.c_str();
    }
private:
    std::string m_sqlmsg;
};

#endif // SQLERROR_H

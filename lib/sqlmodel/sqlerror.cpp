#include "sqlerror.h"


SqlError::SqlError(const std::string &sqlmsg) :
    m_sqlmsg(sqlmsg)
{}


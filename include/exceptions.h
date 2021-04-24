#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include "attributes.h"

typedef ExceptionTable Exception;

void       throwException(const char* exception_name);
Exception* findException(const char* exception_name);

#endif  // __EXCEPTIONS_H

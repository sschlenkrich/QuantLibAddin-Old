
/*
 Copyright (C) 2004, 2005 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <qla/qladdin.hpp>
#include <cstdarg>

extern "C" {
#include <Addins/C/utilities.h>
#include <Addins/C/varies.h>
#include <Addins/C/defines.h>
}
#include <Addins/C/varies.hpp>

const char *QL_VERSION() {
    static std::string ret = QuantLibAddin::qlVersion();
    return ret.c_str();
}

const char *OH_VERSION() {
    static std::string ret = ObjHandler::ohVersion();
    return ret.c_str();
}

const char *OH_SET_LOGFILE(const char *logFileName) {
    ObjHandler::setLogFile(logFileName);
    static std::string ret(logFileName);
    return ret.c_str();
}

void OH_CONSOLE(const long console) {
    ObjHandler::setConsole(console);
}

void OH_LOG_MESSAGE(
        const char *fmt,
        ...) {
    char buf[1000]; // FIXME
    va_list list;
    va_start(list, fmt);
    vsprintf(buf, fmt, list);
    va_end(list);
    ObjHandler::logMessage(buf);
}

void OH_LOG_OBJECT(
        const char *handle) {
    ObjHandler::logObject(handle);
}

int QL_LIST_REGISTERED_ENUMS(
        char **result) {
    try {
        std::vector < std::string > returnValue = QuantLibAddin::getRegisteredEnums();
        Conversion< std::string >::convertArray(returnValue, result);
        return SUCCESS;
    } catch (const std::exception &e) {
        ObjHandler::logMessage("QL_LIST_REGISTERED_ENUMS Error: " + std::string(e.what()));
        result = 0;
        return FAIL;
    }
}

int QL_LIST_ENUM(
        char *enumId,
        char **result) {
    try {
        std::vector < std::string > returnValue = QuantLibAddin::getEnumMembers(
            std::string(enumId));
        Conversion< std::string >::convertArray(returnValue, result);
        return SUCCESS;
    } catch (const std::exception &e) {
        ObjHandler::logMessage("QL_LIST_ENUM Error: " + std::string(e.what()));
        result = 0;
        return FAIL;
    }
}

int QL_LIST_REGISTERED_TYPES(
        char **result) {
    try {
        std::vector < std::string > returnValue = QuantLibAddin::getRegisteredComplexTypes();
        Conversion< std::string >::convertArray(returnValue, result);
        return SUCCESS;
    } catch (const std::exception &e) {
        ObjHandler::logMessage("QL_LIST_REGISTERED_TYPES Error: " + std::string(e.what()));
        result = 0;
        return FAIL;
    }
}

int QL_LIST_TYPE(
        char *enumId,
        char **result) {
    try {
        std::vector < std::string > returnValue = QuantLibAddin::getComplexTypeMembers(
            std::string(enumId));
        Conversion< std::string >::convertArray(returnValue, result);
        return SUCCESS;
    } catch (const std::exception &e) {
        ObjHandler::logMessage("QL_LIST_TYPE Error: " + std::string(e.what()));
        result = 0;
        return FAIL;
    }
}


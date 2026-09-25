/***************************************************************************
 *            macros.hpp
 *
 *  Copyright  2023  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Helper.
 *
 *  Helper is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Helper is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Helper.  If not, see <https://www.gnu.org/licenses/>.
 */


/*! \file macros.hpp
 *  \brief
 */



#ifndef HELPER_MACROS_HPP
#define HELPER_MACROS_HPP

#include <sstream>
#include <stdexcept>

#define HELPER_USING_CONSTRUCTORS(Class,Base) \
    template<class T,typename std::enable_if<std::is_convertible<T,Base>::value,int>::type=0> \
    Class(const T& t) : Base(t) { } \
    template<class T,typename std::enable_if<std::is_constructible<T,Base>::value and not std::is_convertible<T,Base>::value,int>::type=0> \
    explicit Class(const T& t) : Base(t) { } \
    template<class ...Args> Class(Args&&... args) : Base(std::forward<Args>(args)...) { } \

#define HELPER_THROW(except,func,msg)          \
    { \
        std::ostringstream ss; \
        ss << #except " in " << func << ": " << msg;    \
        throw except(ss.str()); \
    } \

#define HELPER_ASSERT(expression) \
    { \
        bool assertion_result = static_cast<bool>(expression); \
        if(!assertion_result) { \
            HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<__FUNCTION__,"Assertion `" << #expression << "' failed."); \
        } \
    } \


#ifndef NDEBUG
#define HELPER_DEBUG_ASSERT_MSG(expression,error) \
    { \
        bool assertion_result = static_cast<bool>(expression); \
        if(!assertion_result) { \
            HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<HELPER_PRETTY_FUNCTION,"Assertion `" << #expression << "' failed.\n"<<"  "<<error); \
        } \
    } \

#else
#define HELPER_DEBUG_ASSERT_MSG(expression,error) \
    { }
#endif


#ifndef NDEBUG
#define HELPER_DEBUG_ASSERT(expression) \
    { \
        bool assertion_result = static_cast<bool>(expression); \
        if(!assertion_result) { \
            HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<__FUNCTION__,"Assertion `" << #expression << "' failed."); \
        } \
    } \

#else
#define HELPER_DEBUG_ASSERT(expression) \
    { }
#endif


#define HELPER_PRECONDITION_MSG(expression,error)             \
    { \
        bool assertion_result = static_cast<bool>(expression); \
        if(!assertion_result) { \
            HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<HELPER_PRETTY_FUNCTION,"Precondition `" << #expression << "' failed.\n"<<"  "<<error); \
        } \
    } \

#define HELPER_PRECONDITION(expression)             \
    { \
        bool assertion_result = static_cast<bool>(expression); \
        if(!assertion_result) { \
            HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<HELPER_PRETTY_FUNCTION,"Precondition `" << #expression << "' failed."); \
        } \
    } \

#ifndef NDEBUG
#define HELPER_DEBUG_PRECONDITION(expression) \
    { \
        bool result = static_cast<bool>(expression); \
        if(!result) { \
            HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<__FUNCTION__,"Precondition `" << #expression << "' failed."); \
        } \
    } \

#else
#define HELPER_DEBUG_PRECONDITION(expression) \
    { }
#endif

#define HELPER_FAIL_MSG(error)             \
    { \
        HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<HELPER_PRETTY_FUNCTION,"ErrorTag "<<error); \
    } \

#define HELPER_ASSERT_MSG(expression,error)             \
    { \
        bool assertion_result = static_cast<bool>(expression); \
        if(!assertion_result) { \
            HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<HELPER_PRETTY_FUNCTION,"Assertion `" << #expression << "' failed.\n"<<"  "<<error); \
        } \
    } \

#define HELPER_ASSERT_EQUAL(expression1,expression2)    \
    { \
        bool assertion_result = static_cast<bool>((expression1) == (expression2));       \
        if(!assertion_result) { \
            HELPER_THROW(std::runtime_error,__FILE__<<":"<<__LINE__<<": "<<HELPER_PRETTY_FUNCTION,"Assertion `" << #expression1 << "==" << #expression2 << "' failed.\n"<<"  "<<expression1<<" != "<<expression2); \
        } \
    } \

#define HELPER_NOT_IMPLEMENTED                 \
    throw std::runtime_error(StringType("Not implemented: ")+HELPER_PRETTY_FUNCTION);

#define HELPER_DEPRECATED(fn,msg)          \
    static bool first_time=true; \
    if(first_time) { \
        first_time=false; \
        std::cerr << "DEPRECATED: Function " << #fn << " is deprecated. " << #msg << std::endl; \
    } \

#define HELPER_NOTIFY(msg)          \
    {                                                                \
        std::cerr << "NOTIFICATION: " << msg << "" << std::endl;                \
    }

#define HELPER_WARN(msg)          \
    {                                                                \
        std::cerr << "WARNING: " << msg << "" << std::endl;                \
    }

#define HELPER_WARN_ONCE(msg)          \
    static bool first_time=true; \
    if(first_time) { \
        first_time=false; \
        std::cerr << "WARNING: " << msg << "" << std::endl; \
    } \

#define HELPER_ERROR(msg)          \
    {                                                                \
        std::cerr << "ERROR: " << msg << "" << std::endl;                \
    }
                                                                  \
#if defined(linux) || defined(__linux) || defined(__linux__)
#define HELPER_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define HELPER_PRETTY_FUNCTION __FUNCTION__
#elif defined(darwin) || defined(__darwin) || defined(__darwin__) || defined(__APPLE__)
#define HELPER_PRETTY_FUNCTION __PRETTY_FUNCTION__
#else
#define HELPER_PRETTY_FUNCTION ""
#endif


#endif // HELPER_MACROS_HPP

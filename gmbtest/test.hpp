/*
  The MIT License (MIT)

  Copyright (c) 2016 G. Beard

  Permission is hereby granted, free of charge, to any person obtaining a 
  copy of this software and associated documentation files (the "Software"), 
  to deal in the Software without restriction, including without limitation 
  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
  and/or sell copies of the Software, and to permit persons to whom the 
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included 
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
  DEALINGS IN THE SOFTWARE.
*/
#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <tuple>

namespace gmb { namespace test
{
  inline size_t& error_count()
  {
    static size_t error_count_{0};
    return error_count_;
  }

  using test_case_t = void(*)(char const*);
  inline std::vector<std::pair<test_case_t, char const*>>& list()
  {
    static std::vector<std::pair<test_case_t, char const*>> list_;
    return list_;
  }

} }

#define TEST_STRINGIFY_IMPL(str) #str
#define TEST_STRINGIFY(str) TEST_STRINGIFY_IMPL(str)
#define TEST_CONCAT_IMPL(x, y) x##y
#define TEST_CONCAT(x, y) TEST_CONCAT_IMPL(x, y)

#define TEST_CASE(name) \
  void name(char const*); \
  struct name##_helper_t \
  { \
    name##_helper_t() \
    { \
      ::gmb::test::list().push_back(std::make_pair( \
        name, TEST_STRINGIFY(name))); \
    } \
  } name##_instance; \
  void name(char const* _test_name_)

#define DEFINE_TEST_MAIN \
  int main() \
  { \
    for(auto&& t : ::gmb::test::list()) { \
      std::get<0>(t)(std::get<1>(t)); \
    } \
    TEST_EXIT(); \
  }

#define TEST_LOG_DEBUG(str) \
  do { \
    std::cout << "LOG: " TEST_CONCAT(<<, str) \
    << " [" << __FILE__ << ", " << _test_name_ << ", line " \
          << __LINE__ << "] " << std::endl; \
  } \
  while(0)

#define TEST_PRINT_POSITION \
  " [" << __FILE__ << ", " << _test_name_ << \
  ", line " << __LINE__ << "]" \

#define TEST_ASSERT(x) \
  do { \
    if( !(x) ) { \
      ::gmb::test::error_count()++; \
      std::cerr << "ASSERTION FAILED: \"" TEST_STRINGIFY(x) \
        << "\"" << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define TEST_EXPECT_THROW(x) \
  do { \
    try { \
      x; \
      ::gmb::test::error_count()++; \
      std::cerr << "EXPECT EXCEPTION FAILED: \"" TEST_STRINGIFY(x) \
        << "\"" << TEST_PRINT_POSITION \
        << std::endl; \
    } \
    catch(...) { } \
  } \
  while(0)

#define THIS_(expr) \
  do { \
    char const* _expr_str_  = \
      TEST_STRINGIFY(expr); \
    auto _expr_lambda_ = \
      [&]{ return (expr); }; \

#define _SHOULD_NOT_THROW \
    try { _expr_lambda_(); } \
    catch(...) { \
      ::gmb::test::error_count()++; \
      std::cerr << "ASSERTION FAILED: DIDN'T EXPECT \"" << \
        _expr_str_ << "\" TO THROW!" \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define _SHOULD_THROW \
    try { _expr_lambda_(); \
      ::gmb::test::error_count()++; \
      std::cerr << "ASSERTION FAILED: EXPECTED \"" << \
        _expr_str_ << "\" TO THROW!" \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
    catch(...) { } \
  } \
  while(0)
#define _SHOULD_BE_(expected) \
  if(_expr_lambda_() != (expected) ) \
    { \
      ::gmb::test::error_count()++; \
      std::cerr << "ASSERTION FAILED: \"" << \
        _expr_str_ << " != " << TEST_STRINGIFY(expected) \
        << "\"" \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define _SHOULD_BE_TRUE \
  if(_expr_lambda_() == false ) \
    { \
      ::gmb::test::error_count()++; \
      std::cerr << "ASSERTION FAILED: \"" << \
        _expr_str_ << "\"" \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define _SHOULD_BE_FALSE \
  if(_expr_lambda_() == true ) \
    { \
      ::gmb::test::error_count()++; \
      std::cerr << "ASSERTION FAILED: \"" << \
        _expr_str_ << "\"" \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define TEST_EXPECT_NO_THROW(x) \
  do { \
    try { \
      x; \
    } \
    catch(...) { \
      ::gmb::test::error_count()++; \
      std::cerr << "EXPECT NO EXCEPTION FAILED: " TEST_STRINGIFY(x) \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define TEST_EXIT() \
  do { \
    if(::gmb::test::error_count() > 0) { \
      std::cerr << ::gmb::test::error_count() << " TESTS FAILED!" \
        << std::endl; \
      return 1; \
    } \
    else { \
      std::cout << "NO FAILURES" << std::endl; \
      return 0; \
    } \
  } \
  while(0)

#endif //TEST_HPP_INCLUDED

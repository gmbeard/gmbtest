#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <tuple>

namespace gmb { namespace test
{
  size_t error_count;
  using test_case_t = void(*)(char const*);
  std::vector<std::pair<test_case_t, char const*>> list;
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
      ::gmb::test::list.push_back(std::make_pair( \
        name, TEST_STRINGIFY(name))); \
    } \
  } name##_instance; \
  void name(char const* _test_name_)

#define DEFINE_TEST_MAIN \
  int main() \
  { \
    for(auto&& t : ::gmb::test::list) { \
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
      ::gmb::test::error_count++; \
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
      ::gmb::test::error_count++; \
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
    if ([&]() -> bool { return (expr); }

#define _SHOULD_BE_(expected) \
  () != (expected) ) \
    { \
      ::gmb::test::error_count++; \
      std::cerr << "ASSERTION FAILED: \"" << \
        _expr_str_ << " != " << TEST_STRINGIFY(expected) \
        << "\"" \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define _SHOULD_BE_TRUE \
  () == false ) \
    { \
      ::gmb::test::error_count++; \
      std::cerr << "ASSERTION FAILED: \"" << \
        _expr_str_ << "\"" \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define _SHOULD_BE_FALSE \
  () == true ) \
    { \
      ::gmb::test::error_count++; \
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
      ::gmb::test::error_count++; \
      std::cerr << "EXPECT NO EXCEPTION FAILED: " TEST_STRINGIFY(x) \
        << TEST_PRINT_POSITION \
        << std::endl; \
    } \
  } \
  while(0)

#define TEST_EXIT() \
  do { \
    if(::gmb::test::error_count > 0) { \
      std::cerr << ::gmb::test::error_count << " TESTS FAILED!" \
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

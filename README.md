GMBTEST - Macro-based C++ testing framework
====
This is a simple little testing framework that I created just for fun.

Usage
----
Testing is done using a small set of macros, namely `DEFINE_TEST_MAIN`, `TEST_CASE(...)`, `THIS_(x)_SHOULD_...`

    #include <gmbtest/test.hpp>

    DEFINE_TEST_MAIN // This needs to appear once
                     // in your test application.

    TEST_CASE(should_create_a_test)
    {
      auto a = 0;
      a++;

      THIS_(a)_SHOULD_BE_(1);

      a++;
      THIS_(a == 2)_SHOULD_BE_FALSE; // Failure.

      LOG_DEBUG("a is " << a); // Log to STDOUT.
    }

    TEST_CASE(another_test)
    {
      ...
    }

We can also test for exceptions...

    TEST_EXPECT_THROW(obj.func_that_should_throw()); // Fails if no exception thrown.

    TEST_EXPECT_NO_THROW(obj.func_that_shouldnt_throw()); // Fails if exception thrown.

Requirements
----
- C++11/14/17 compiler

(That's it!)

License
----
Licensed under the [MIT License](https://github.com/gmbeard/gmbtest/blob/master/LICENSE)

Contributors
----
- G. Beard


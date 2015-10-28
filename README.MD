Before start use asio, you just need to define preprocessors:

BOOST_ERROR_CODE_HEADER_ONLY
BOOST_SYSTEM_NO_DEPRECATED
BOOST_SYSTEM_NO_LIB
BOOST_DATE_TIME_NO_LIB
BOOST_REGEX_NO_LIB 

If use single thread, you should define: BOOST_ASIO_DISABLE_THREADS, but can't use timer

firstly, and add aditionnal includes path "Root Of boost Directory" to your compile system, such as MSVC,XCode,GCC,Android.mk.

Please open c++11 flags for android compile.
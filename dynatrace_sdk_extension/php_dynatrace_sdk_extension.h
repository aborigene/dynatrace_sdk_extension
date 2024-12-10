
#ifndef PHP_DYNATRACE_SDK_EXTENSION_H
#define PHP_DYNATRACE_SDK_EXTENSION_H

extern zend_module_entry dynatrace_sdk_extension_module_entry;
#define phpext_dynatrace_sdk_extension_ptr &dynatrace_sdk_extension_module_entry

#define PHP_DYNATRACE_SDK_EXTENSION_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_DYNATRACE_SDK_EXTENSION_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_DYNATRACE_SDK_EXTENSION_API __attribute__ ((visibility("default")))
#else
#	define PHP_DYNATRACE_SDK_EXTENSION_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(dynatrace_sdk_extension)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(dynatrace_sdk_extension)
*/

/* Always refer to the globals in your function as DYNATRACE_SDK_EXTENSION_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define DYNATRACE_SDK_EXTENSION_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(dynatrace_sdk_extension, v)

#if defined(ZTS) && defined(COMPILE_DL_DYNATRACE_SDK_EXTENSION)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_DYNATRACE_SDK_EXTENSION_H */


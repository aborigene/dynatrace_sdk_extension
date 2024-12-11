
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_dynatrace_sdk_extension.h"
#include "onesdk/onesdk.h"
#include <unistd.h>

/* If you declare any globals in php_dynatrace_sdk_extension.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(dynatrace_sdk_extension)
*/

/* True global resources - no need for thread safety here */
static int le_dynatrace_sdk_extension;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("dynatrace_sdk_extension.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_dynatrace_sdk_extension_globals, dynatrace_sdk_extension_globals)
    STD_PHP_INI_ENTRY("dynatrace_sdk_extension.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_dynatrace_sdk_extension_globals, dynatrace_sdk_extension_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_dynatrace_sdk_extension_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_dynatrace_sdk_extension_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "dynatrace_sdk_extension", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(start_trace) {
	onesdk_tracer_start(tracer);
}

// Function implementation
PHP_FUNCTION(simple_trace) {
	setenv("ONESDK_AGENT_LIB_PATH", "/opt/dynatrace/oneagent/agent/bin/1.303.62.20241129-131342/linux-x86-64/", 1);
	onesdk_result_t const onesdk_init_result = onesdk_initialize();
    //long a, b;

	// printf("%d", onesdk_init_result);
	// if (onesdk_init_result != ONESDK_SUCCESS) {
    //     // Handle initialization error
    //     printf("OneAgent SDK initialization failed with error code: %d\n", onesdk_init_result);
    // }
	//checkresult(onesdk_init_result, "  initialize");
	onesdk_tracer_handle_t const tracer = onesdk_outgoingremotecalltracer_create(
        onesdk_asciistr("remote service method"),
        onesdk_asciistr("logical service name"),
        onesdk_asciistr("deployed service endpoint"),
        ONESDK_CHANNEL_TYPE_TCP_IP,           /* channel type     */
        onesdk_asciistr("localhost:12345")    /* channel endpoint, host/ip:port in case of TCP_IP */ );
	
	//	long a = deu_merda("123");
	
	onesdk_tracer_start(tracer);
	sleep(3);
	onesdk_tracer_end(tracer);

	if (onesdk_init_result == ONESDK_SUCCESS)
        onesdk_shutdown();

    RETURN_LONG(0);
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_dynatrace_sdk_extension_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_dynatrace_sdk_extension_init_globals(zend_dynatrace_sdk_extension_globals *dynatrace_sdk_extension_globals)
{
	dynatrace_sdk_extension_globals->global_value = 0;
	dynatrace_sdk_extension_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(dynatrace_sdk_extension)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(dynatrace_sdk_extension)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(dynatrace_sdk_extension)
{
#if defined(COMPILE_DL_DYNATRACE_SDK_EXTENSION) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	printf("STARTED REQUEST...\n\n");
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(dynatrace_sdk_extension)
{
	printf("FINISHED REQUEST...\n\n");
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(dynatrace_sdk_extension)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "dynatrace_sdk_extension support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ dynatrace_sdk_extension_functions[]
 *
 * Every user visible function must have an entry in dynatrace_sdk_extension_functions[].
 */
const zend_function_entry dynatrace_sdk_extension_functions[] = {
	PHP_FE(confirm_dynatrace_sdk_extension_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(simple_trace,	NULL)		
	PHP_FE_END	/* Must be the last line in dynatrace_sdk_extension_functions[] */
};
/* }}} */

/* {{{ dynatrace_sdk_extension_module_entry
 */
zend_module_entry dynatrace_sdk_extension_module_entry = {
	STANDARD_MODULE_HEADER,
	"dynatrace_sdk_extension",
	dynatrace_sdk_extension_functions,
	PHP_MINIT(dynatrace_sdk_extension),
	PHP_MSHUTDOWN(dynatrace_sdk_extension),
	PHP_RINIT(dynatrace_sdk_extension),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(dynatrace_sdk_extension),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(dynatrace_sdk_extension),
	PHP_DYNATRACE_SDK_EXTENSION_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DYNATRACE_SDK_EXTENSION
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(dynatrace_sdk_extension)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

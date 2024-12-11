dnl $Id$
dnl config.m4 for extension dynatrace_sdk_extension

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(dynatrace_sdk_extension, for dynatrace_sdk_extension support,
dnl Make sure that the comment is aligned:
dnl [  --with-dynatrace_sdk_extension             Include dynatrace_sdk_extension support])

dnl Otherwise use enable:

PHP_ARG_WITH([onesdk], [for onesdk support], [AS_HELP_STRING([--with-onesdk], [Include onesdk support])])

if test "$PHP_ONESDK" != "no"; then

    LIBPATH=/home/ec2-user/OneAgent-SDK-for-C-1.7.1
    LIBNAME=onesdk_static
    LIBSYMBOL=onesdk_initialize

     PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  [
    PHP_ADD_INCLUDE($LIBPATH/include)
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LIBPATH/lib/linux-x86_64, DYNATRACE_SDK_EXTENSION_SHARED_LIBADD)
    PHP_SUBST(DYNATRACE_SDK_EXTENSION_SHARED_LIBADD)
    AC_DEFINE(HAVE_ONESDK,1,[ ])
  ],[
    AC_MSG_ERROR([wrong $LIBNAME lib version or lib not found in $LIBPATH])
  ],[
    -L$LIBPATH/lib/linux-x86_64 -l$LIBNAME -ldl
  ])
fi

PHP_ARG_ENABLE(dynatrace_sdk_extension, whether to enable dynatrace_sdk_extension support,
dnl Make sure that the comment is aligned:
[  --enable-dynatrace_sdk_extension           Enable dynatrace_sdk_extension support])

if test "$PHP_DYNATRACE_SDK_EXTENSION" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-dynatrace_sdk_extension -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/dynatrace_sdk_extension.h"  # you most likely want to change this
  dnl if test -r $PHP_DYNATRACE_SDK_EXTENSION/$SEARCH_FOR; then # path given as parameter
  dnl   DYNATRACE_SDK_EXTENSION_DIR=$PHP_DYNATRACE_SDK_EXTENSION
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for dynatrace_sdk_extension files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DYNATRACE_SDK_EXTENSION_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DYNATRACE_SDK_EXTENSION_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the dynatrace_sdk_extension distribution])
  dnl fi

  dnl # --with-dynatrace_sdk_extension -> add include path
  dnl PHP_ADD_INCLUDE($DYNATRACE_SDK_EXTENSION_DIR/include)

  dnl # --with-dynatrace_sdk_extension -> check for lib and symbol presence
  dnl LIBNAME=dynatrace_sdk_extension # you may want to change this
  dnl LIBSYMBOL=dynatrace_sdk_extension # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DYNATRACE_SDK_EXTENSION_DIR/$PHP_LIBDIR, DYNATRACE_SDK_EXTENSION_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DYNATRACE_SDK_EXTENSIONLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong dynatrace_sdk_extension lib version or lib not found])
  dnl ],[
  dnl   -L$DYNATRACE_SDK_EXTENSION_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DYNATRACE_SDK_EXTENSION_SHARED_LIBADD)

  PHP_NEW_EXTENSION(dynatrace_sdk_extension, dynatrace_sdk_extension.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi

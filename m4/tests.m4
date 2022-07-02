dnl
dnl TEST_BUILD_PROGRAM
dnl
dnl Adapted from PHP_BUILD_PROGRAM in php.m4.
dnl
AC_DEFUN([TEST_BUILD_PROGRAM],[
  test_c_pre='$(CC)'
  test_c_meta='$(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS)'
  test_c_post=
  test_cxx_pre='$(CXX)'
  test_cxx_meta='$(COMMON_FLAGS) $(CXXFLAGS_CLEAN) $(EXTRA_CXXFLAGS)'
  test_cxx_post=
])

dnl
dnl TEST_ADD_SOURCES(source-path, sources[, special-flags[, target-var]])
dnl
dnl Adapted from PHP_ADD_SOURCES_X in php.m4.
dnl
AC_DEFUN([TEST_ADD_SOURCES],[
  TEST_BUILD_PROGRAM

dnl Relative to source- or build-directory?
dnl ac_srcdir/ac_bdir include trailing slash
  case $1 in
  ""[)] ac_srcdir="$abs_srcdir/"; unset ac_bdir; ac_inc="-I. -I$abs_srcdir" ;;
  /*[)] ac_srcdir=`echo "$1"|cut -c 2-`"/"; ac_bdir=$ac_srcdir; ac_inc="-I$ac_bdir -I$abs_srcdir/$ac_bdir" ;;
  *[)] ac_srcdir="$abs_srcdir/$1/"; ac_bdir="$1/"; ac_inc="-I$ac_bdir -I$ac_srcdir" ;;
  esac

dnl Iterate over the sources.
  old_IFS=[$]IFS
  for ac_src in $2; do

dnl Remove the suffix.
      IFS=.
      set $ac_src
      ac_obj=[$]1
      IFS=$old_IFS

dnl Append to the array which has been dynamically chosen at m4 time.
      $4="[$]$4 [$]ac_bdir[$]ac_obj.o"

dnl Choose the right compiler/flags/etc. for the source-file.
      case $ac_src in
        *.c[)] ac_comp="$test_c_pre $ac_inc $test_c_meta $3 -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.o $test_c_post" ;;
        *.s[)] ac_comp="$test_c_pre $ac_inc $test_c_meta $3 -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.o $test_c_post" ;;
        *.S[)] ac_comp="$test_c_pre $ac_inc $test_c_meta $3 -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.o $test_c_post" ;;
        *.cpp|*.cc|*.cxx[)] ac_comp="$test_cxx_pre $ac_inc $test_cxx_meta $3 -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.o $test_cxx_post" ;;
      esac

dnl Generate Makefiles with dependencies
      ac_comp="$ac_comp -MMD -MF $ac_bdir$ac_obj.d -MT $ac_bdir[$]ac_obj.o"

dnl Create a rule for the object/source combo.
    cat >>Makefile.objects<<EOF
-include $ac_bdir[$]ac_obj.d
$ac_bdir[$]ac_obj.o: $ac_srcdir[$]ac_src
	$ac_comp
EOF
  done
])

EXTRA_INCLUDES := -I. -I$(srcdir) -I/usr/local/include

-include src/ecma402/bcp47.d
src/ecma402/bcp47.o: src/ecma402/bcp47.c
	$(CC) $(EXTRA_INCLUDES) $(COMMON_FLAGS) -MMD -MP -c src/ecma402/bcp47.c -o src/ecma402/bcp47.o

-include src/ecma402/units.d
src/ecma402/units.o: src/ecma402/units.cpp
	$(CXX) $(EXTRA_INCLUDES) $(COMMON_FLAGS) $(CXXFLAGS) -std=c++11 -MMD -MP -c src/ecma402/units.cpp -o src/ecma402/units.o

libecma402.so: src/ecma402/bcp47.o src/ecma402/units.o
	$(CXX) src/ecma402/bcp47.o src/ecma402/units.o -shared -o libecma402.so $(ECMA_INTL_SHARED_LIBADD)

-include tests/cpputest/ecma402/bcp47_test.d
tests/cpputest/ecma402/bcp47_test.o: tests/cpputest/ecma402/bcp47_test.cpp
	$(CXX) $(EXTRA_INCLUDES) $(COMMON_FLAGS) $(CXXFLAGS) -std=c++11 -MMD -MP -c tests/cpputest/ecma402/bcp47_test.cpp -o tests/cpputest/ecma402/bcp47_test.o

-include tests/cpputest/run_tests.d
tests/cpputest/run_tests.o: tests/cpputest/run_tests.cpp
	$(CXX) $(EXTRA_INCLUDES) $(COMMON_FLAGS) $(CXXFLAGS) -std=c++11 -MMD -MP -c tests/cpputest/run_tests.cpp -o tests/cpputest/run_tests.o

tests/cpputest/cpputest: src/ecma402/bcp47.o src/ecma402/units.o tests/cpputest/run_tests.o tests/cpputest/ecma402/bcp47_test.o
	$(CXX) tests/cpputest/run_tests.o src/ecma402/bcp47.o src/ecma402/units.o tests/cpputest/ecma402/bcp47_test.o -o tests/cpputest/cpputest $(ECMA_INTL_SHARED_LIBADD) -lCppUTest -lCppUTestExt

cpputest: tests/cpputest/cpputest
	@./tests/cpputest/cpputest -c

deepclean: distclean
	git clean -fXd \
		--exclude '!.idea' \
		--exclude '!.idea/**' \
		--exclude '!vendor' \
		--exclude '!vendor/**' \
		--exclude '!composer.lock'

.PHONY: cpputest deepclean

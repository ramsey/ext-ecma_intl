tests/cpputest/run_tests: $(cpputest_objects)
	@if test "$(cpputest_objects)"; then \
		$(CXX) $(cpputest_objects) -o tests/cpputest/run_tests $(ECMA_INTL_SHARED_LIBADD) $(CPPUTEST_LIBS); \
	else \
		echo "[ERROR] Configure ecma_intl with --enable-cpputest to run Cpputest tests"; \
		exit 1; \
	fi

cpputest: tests/cpputest/run_tests
	@./tests/cpputest/run_tests -c

deepclean: distclean
	git clean -fXd \
		--exclude '!.idea' \
		--exclude '!.idea/**' \
		--exclude '!vendor' \
		--exclude '!vendor/**' \
		--exclude '!composer.lock'

.PHONY: cpputest deepclean

check-criterion:
	@if ! test "$(criterion_objects)"; then \
		echo "[ERROR] Configure ecma_intl with --enable-criterion to run Criterion tests"; \
		echo "        To install Criterion, see https://github.com/Snaipe/Criterion"; \
		echo ""; \
		exit 1; \
	fi

tests/criterion/runner: check-criterion $(criterion_objects)
	$(CXX) $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) $(LDFLAGS) $(EXTRA_LDFLAGS) $(criterion_objects) -o tests/criterion/runner $(ECMA_INTL_SHARED_LIBADD) $(CRITERION_LIBS); \

#
# In CLion, set the "Build target" to "clion" in the Makefile project settings,
# and CLion will provide proper source code insight for code in both the src/
# and tests/ directories, since we're including "all" and
# "tests/criterion/runner" in this target.
#
# See: https://www.jetbrains.com/help/clion/makefiles-support.html#makefile-settings
#
clion: all tests/criterion/runner

criterion: tests/criterion/runner
	./tests/criterion/runner --color=always

test-clean:
	find . -name \*.d | xargs rm -f

clean: test-clean

deepclean: distclean
	git clean -fXd \
		--exclude '!.idea' \
		--exclude '!.idea/**' \
		--exclude '!vendor' \
		--exclude '!vendor/**' \
		--exclude '!composer.lock'

.PHONY: check-criterion criterion deepclean test-clean

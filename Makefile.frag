tests/criterion/runner: $(criterion_objects)
	@if test "$(criterion_objects)"; then \
		$(CXX) $(criterion_objects) -o tests/criterion/runner $(ECMA_INTL_SHARED_LIBADD) $(CRITERION_LIBS); \
	else \
		echo "[ERROR] Configure ecma_intl with --enable-criterion to run Criterion tests"; \
		echo "        To install Criterion, see https://github.com/Snaipe/Criterion"; \
		echo ""; \
		exit 1; \
	fi

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
	@./tests/criterion/runner --color=always

deepclean: distclean
	git clean -fXd \
		--exclude '!.idea' \
		--exclude '!.idea/**' \
		--exclude '!vendor' \
		--exclude '!vendor/**' \
		--exclude '!composer.lock'

.PHONY: criterion deepclean

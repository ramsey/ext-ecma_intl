tests/criterion/runner: $(criterion_objects)
	@if test "$(criterion_objects)"; then \
		$(CXX) $(criterion_objects) -o tests/criterion/runner $(ECMA_INTL_SHARED_LIBADD) $(CRITERION_LIBS); \
	else \
		echo "[ERROR] Configure ecma_intl with --enable-criterion to run Criterion tests"; \
		echo "        To install Criterion, see https://github.com/Snaipe/Criterion"; \
		echo ""; \
		exit 1; \
	fi

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

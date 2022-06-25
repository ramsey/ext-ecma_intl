.PHONY: deepclean

deepclean: distclean
	git clean -fXd \
		--exclude '!.idea' \
		--exclude '!.idea/**' \
		--exclude '!vendor' \
		--exclude '!vendor/**' \
		--exclude '!composer.lock'

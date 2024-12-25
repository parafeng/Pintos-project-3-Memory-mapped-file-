# ...existing code...

tests/vm/file-access.result: tests/vm/file-access
	pintos -v -k -T 60 --qemu --filesys-size=2 \
	-p tests/vm/file-access -a file-access \
	-- -q run file-access

.PHONY: tests/vm/file-access
tests/vm/file-access:
	$(MAKE) -C vm $@

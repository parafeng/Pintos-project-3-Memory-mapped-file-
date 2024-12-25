include ../Makefile.kernel

test: tests/vm/file-access.result

tests/vm/file-access.result: FORCE
	pintos -v -k -T 60 --qemu --filesys-size=2 -p tests/vm/file-access -a file-access -- -q run 'file-access'

FORCE:

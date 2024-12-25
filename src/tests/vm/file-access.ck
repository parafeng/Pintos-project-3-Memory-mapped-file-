use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(file-access) begin
(file-access) begin
(file-access) create first file: ok
(file-access) create second file: ok
(file-access) open files: ok
(file-access) read from first file: ok
(file-access) read access to file1 recorded
(file-access) write to second file: ok
(file-access) write access to file2 recorded
(file-access) verify read access: ok
(file-access) verify written data: ok
(file-access) access verification complete
(file-access) end
(file-access) end
EOF
pass;

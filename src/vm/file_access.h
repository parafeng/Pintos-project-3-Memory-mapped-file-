#ifndef VM_FILE_ACCESS_H
#define VM_FILE_ACCESS_H

void track_file_access(void *vaddr, bool is_write);
void print_file_access_stats(void);

#endif /* vm/file_access.h */
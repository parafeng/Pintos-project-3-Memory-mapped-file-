#include <debug.h>
#include <stdio.h>
#include "vm/page.h"
#include "vm/frame.h"
#include "threads/thread.h"
#include "threads/malloc.h"
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#include "vm/file_access.h"

struct file_access_entry {
    void *vaddr;              /* Virtual address */
    size_t page_read_count;   /* Number of page reads */
    size_t page_write_count;  /* Number of page writes */
    bool is_dirty;            /* Whether page is dirty */
};

/* Tracks file access statistics for pages */
void 
track_file_access(void *vaddr, bool is_write) 
{
    struct thread *t = thread_current();
    uint32_t *pd = t->pagedir;
    
    /* Verify the virtual address is valid */
    if (!is_user_vaddr(vaddr) || !pagedir_get_page(pd, vaddr))
        return;

    /* Update access counts */
    if (is_write) {
        /* Mark page as dirty */
        pagedir_set_dirty(pd, vaddr, true);
    }

    /* Mark page as accessed */
    pagedir_set_accessed(pd, vaddr, true);
}

/* Print file access statistics */
void
print_file_access_stats(void) 
{
    struct thread *t = thread_current();
    uint32_t *pd = t->pagedir;

    printf("File Access Statistics:\n");
    printf("----------------------\n");

    /* Iterate through all pages in current process */
    for (void *vaddr = 0; vaddr < PHYS_BASE; vaddr += PGSIZE) {
        if (pagedir_get_page(pd, vaddr) != NULL) {
            bool is_dirty = pagedir_is_dirty(pd, vaddr);
            bool is_accessed = pagedir_is_accessed(pd, vaddr);
            
            printf("Virtual Address: %p\n", vaddr);
            printf("  Dirty: %s\n", is_dirty ? "Yes" : "No");
            printf("  Accessed: %s\n", is_accessed ? "Yes" : "No");
            
            /* Reset accessed bit after checking */
            pagedir_set_accessed(pd, vaddr, false);
        }
    }
}
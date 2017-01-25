#define smalloc_int(size) smart_malloc_int(size, __FILE__, __LINE__)
#define sfree_int(ptr) smart_free_int(ptr, __FILE__, __LINE__)
#define sset_int(ptr, offset, value) smart_set_int(ptr, offset, value, __FILE__, __LINE__)
#define sget_int(ptr, offset) smart_get_int(ptr, offset, __FILE__, __LINE__)
#define sleak() smart_leakcheck ()

void *smart_malloc_int (size_t size, char *file, int line);
void smart_free_int (void *ptr, char *file, int line);
int smart_set_int (void *ptr, int offset, int value, char *file, int line);
int smart_get_int (void *ptr, int offset, char *file, int line);
int smart_leakcheck ();

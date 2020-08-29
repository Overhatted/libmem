# libmem
Memory library written in C (Windows/Linux)  

# Usage
Copy the 'libmem' folder to your project directory.  
Make sure to compile 'libmem.c' along with your project.  

# Dependencies
Windows: Windows SDK  
Linux:   libdl ( -ldl )  

# License
Read 'LICENSE'  

# Overview
```
//libmem

mem_string_t  mem_parse_mask(mem_string_t mask);

//ex
mem_pid_t     mem_ex_get_pid(mem_string_t process_name);
mem_string_t  mem_ex_get_process_name(mem_pid_t pid);
mem_process_t mem_ex_get_process(mem_pid_t pid);
mem_module_t  mem_ex_get_module(mem_process_t process, mem_string_t module_name);
mem_bool_t    mem_ex_is_process_running(mem_process_t process);
mem_int_t     mem_ex_read(mem_process_t process, mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size);
mem_int_t     mem_ex_write(mem_process_t process, mem_voidptr_t src, mem_voidptr_t data, mem_size_t size);
mem_int_t     mem_ex_set(mem_process_t process, mem_voidptr_t src, mem_byte_t byte, mem_size_t size);
mem_int_t     mem_ex_protect(mem_process_t process, mem_voidptr_t src, mem_size_t size, mem_prot_t protection);
mem_voidptr_t mem_ex_allocate(mem_process_t process, mem_size_t size, mem_prot_t protection);
mem_int_t     mem_ex_deallocate(mem_process_t process, mem_voidptr_t src, mem_size_t size);
mem_voidptr_t mem_ex_scan(mem_process_t process, mem_bytearray_t data, mem_voidptr_t base, mem_voidptr_t end, mem_size_t size);
mem_voidptr_t mem_ex_pattern_scan(mem_process_t process, mem_bytearray_t pattern, mem_string_t mask, mem_voidptr_t base, mem_voidptr_t end);
mem_int_t     mem_ex_detour(mem_process_t process, mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size, mem_detour_int_t method, mem_bytearray_t* stolen_bytes);
mem_voidptr_t mem_ex_detour_trampoline(mem_process_t process, mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size, mem_detour_int_t method, mem_bytearray_t* stolen_bytes);
mem_void_t    mem_ex_detour_restore(mem_process_t process, mem_voidptr_t src, mem_bytearray_t stolen_bytes, mem_size_t size);
mem_int_t     mem_ex_load_library(mem_process_t process, mem_lib_t lib);
mem_voidptr_t mem_ex_get_symbol(mem_module_t mod, const char* symbol);

//in

mem_pid_t     mem_in_get_pid();
mem_process_t mem_in_get_process();
mem_string_t  mem_in_get_process_name();
mem_module_t  mem_in_get_module(mem_string_t module_name);
mem_voidptr_t mem_in_pattern_scan(mem_bytearray_t pattern, mem_string_t mask, mem_voidptr_t base, mem_size_t size);
mem_void_t    mem_in_read(mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size);
mem_void_t    mem_in_write(mem_voidptr_t src, mem_voidptr_t data, mem_size_t size);
mem_void_t    mem_in_set(mem_voidptr_t src, mem_byte_t byte, mem_size_t size);
mem_int_t     mem_in_protect(mem_voidptr_t src, mem_size_t size, mem_prot_t protection);
mem_voidptr_t mem_in_allocate(mem_size_t size, mem_prot_t protection);
mem_void_t    mem_in_deallocate(mem_voidptr_t src, mem_size_t size);
mem_bool_t    mem_in_compare(mem_voidptr_t pdata1, mem_voidptr_t pdata2, mem_size_t size);
mem_voidptr_t mem_in_scan(mem_voidptr_t data, mem_voidptr_t base, mem_voidptr_t end, mem_size_t size);
mem_size_t    mem_in_detour_length(mem_detour_int_t method);
mem_int_t     mem_in_detour(mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size, mem_detour_int_t method, mem_bytearray_t* stolen_bytes);
mem_voidptr_t mem_in_detour_trampoline(mem_voidptr_t src, mem_voidptr_t dst, mem_size_t size, mem_detour_int_t method, mem_bytearray_t* stolen_bytes);
mem_void_t    mem_in_detour_restore(mem_voidptr_t src, mem_bytearray_t stolen_bytes, mem_size_t size);
mem_int_t     mem_in_load_library(mem_lib_t lib, mem_module_t* mod);
mem_voidptr_t mem_in_get_symbol(mem_module_t mod, const char* symbol);
```

# Projects
Made with libmem:
```
WIP
```

# TODO
. Add support for ARM  
. Add documentation  
. Add examples/projects  
. Clean up code  

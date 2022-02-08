#include "matrix.h"

static MemoryManager<float> manager;

void init_memory(size_t max_size){
    manager = MemoryManager<float>(max_size);
}
MemoryManager<float>& get_custom_memory(){
    return manager;
}
void free_manager() {
    manager.~MemoryManager();
}
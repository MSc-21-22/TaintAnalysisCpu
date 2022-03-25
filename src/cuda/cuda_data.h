#pragma once
#include <array>
#include <limits>
#include <memory>

using BitVector = int32_t;

struct Transfer{ // x = y + z     { x, [y, z]}
    int x;
    int rhs[5] = {-1,-1,-1,-1,-1}; // -1 terminated
    int next_transfer_index = -1;
};

template<typename Item>
class DynamicArray {
private:
    std::allocator<char> alloc{};
    char* items;
    size_t current_size;
    size_t max_size;
    unsigned int item_size;
public:
    DynamicArray(size_t item_count, unsigned int item_size) : max_size(item_count), item_size(item_size), current_size(0){
        items = alloc.allocate(max_size * item_size);
    }

    ~DynamicArray() {
        if(items != nullptr){
            alloc.deallocate(items, max_size * item_size);
        }
    }

    DynamicArray(const DynamicArray& other) {
        max_size = other.max_size;
        item_size = other.item_size;
        current_size = other.current_size;
        items = alloc.allocate(max_size * item_size);
        std::copy(other.items, other.items + current_size*item_size, items);
    }

    DynamicArray& operator=(const DynamicArray& other){
        max_size = other.max_size;
        item_size = other.item_size;
        current_size = other.current_size;
        items = alloc.allocate(max_size * item_size);
        std::copy(other.items, other.items + current_size*item_size, items);
        return *this;
    }

    
    DynamicArray(DynamicArray&& other) noexcept : DynamicArray(other.max_size, other.item_size) {
        std::swap(alloc, other.alloc);
        current_size = other.current_size;
        items = other.items;
        other.items = nullptr;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept{
        std::swap(current_size, other.current_size);
        std::swap(max_size, other.max_size);
        std::swap(item_size, other.item_size);
        std::swap(items, other.items);
        std::swap(alloc, other.alloc);
    }

    Item& operator[](int index) {
        return *(Item*)(items + index * item_size);
    }

    size_t size() {
        return current_size;
    }

    size_t capacity(){
        return max_size;
    }

    template<typename ... Args>
    Item& emplace_back(Args ... args){
        if(current_size >= max_size){
            throw "Exceeded capacity of dynamic array";
        }

        Item* next = (Item*)(items + current_size * item_size);
        current_size++;
        new (next) Item(std::forward<Args>(args)...); //Placement new, i.e. not an allocation

        std::memset(next+1, 0, item_size - sizeof(Item));

        return *next; 
    }

    Item& back() {
        return *(Item*) (items + (current_size - 1) * item_size);
    }

};
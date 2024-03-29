#include "kernel.hh"

using namespace console;
using namespace allocator;
using namespace idt;
using namespace pic;

BuddyAllocator k_allocator;
Console k_console;

extern "C" void main() {
    Idt k_idt;
    Pic k_pic;

    auto a1 = k_allocator.kmalloc(1 << 27).unwrap();
    auto a5 = k_allocator.kmalloc(1 << 27).unwrap();
    auto a2 = k_allocator.kmalloc(1 << 12).unwrap();
    auto a3 = k_allocator.kmalloc(1 << 27).unwrap();
    auto a4 = k_allocator.kmalloc(1 << 12).unwrap();
    auto a6 = k_allocator.kmalloc(1 << 13).unwrap();
    auto a7 = k_allocator.kmalloc(1 << 15).unwrap();

    k_allocator.kfree(a6);
    k_allocator.kfree(a1);
    k_allocator.kfree(a2);
    k_allocator.kfree(a4);
    k_allocator.kfree(a7);
    k_allocator.kfree(a3);
    k_allocator.kfree(a5);

    k_allocator.print_memory_map();
	k_console.print(3 / 0);
}

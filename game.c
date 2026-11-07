#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        puts("用法: ./game ./fire.so");
        return 1;
    }

    void *module = dlopen(argv[1], RTLD_NOW);
    if (module == NULL) {
        puts(dlerror());
        return 1;
    }

    void (*attack)(void) = (void (*)(void))dlsym(module, "attack");

    if (attack == NULL) {
        puts(dlerror());
        dlclose(module);
        return 1;
    }

    puts("🎮 怪物出现了！");
    attack();

    dlclose(module);
    return 0;
}
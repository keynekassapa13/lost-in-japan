void a_julia();
void a_cameras();
void a_solids();
void a_indexing();
void a_instancing();
void a_lighting();
void a_materials();
void a_textures();
void a_local();
void a_mappers();
void a_distributed();
void a_smooth();
void a_bumpmappers();
void a_volume();
void a_competition();

#include <stdexcept>
#include <iostream>
#include <core/assert.h>
#include <chrono>
#include <time.h> 

int main(int argc, char* argv[])
{
    // Assignment 1
    // a_julia();
    // a_cameras();

    // Assignmenet 2
    // a_solids();

    // Assignment 3
    // a_indexing();

    // Assignment 4
    // a_instancing();

    // Assignment 5
    // a_lighting();

    // Assignment 6
    // a_materials();
    // a_textures();
    // a_local();
    // a_mappers();

    // Assignment 7
    // a_distributed();
    // a_smooth();

    // Assignment 8
    // a_bumpmappers();
    // a_volume();
    

    time_t start_time = time(NULL); \

    a_competition();

    time_t end_time = time(NULL); \
    printf("%s", ctime(&start_time));
    printf("%s", ctime(&end_time));
    
    return 0;
}

#include "sse_test.hpp"
#include <stdlib.h>
#include <time.h>
#include <chrono>

float randFloat() {
    return (float) (rand()) / (float) (RAND_MAX);
}

float4 randFloat4() {
    float4 res;
    res.x = randFloat();
    res.y = randFloat();
    res.z = randFloat();
    res.w = randFloat();
    return res;
}

void sse_test(Mesh &mesh) {

    //Not allowed to change:
    unsigned int const loadFactor = 1000;
    //
    std::vector<sse_float4> vertices;
    std::vector<sse_float4> rand1;
    std::vector<sse_float4> rand2;
    std::vector<sse_float4> rand3;
    std::vector<sse_float4> rand4;
    srand(time(NULL));

    vertices.resize(mesh.vertexCount);

    rand1.resize(vertices.size());
    rand2.resize(vertices.size());
    rand3.resize(vertices.size());
    rand4.resize(vertices.size());


    auto start_sse = std::chrono::high_resolution_clock::now();

    std::cout << "SSE_TEST: Initializing vectors... " << std::flush;
    for (unsigned int i=0; i < vertices.size(); i++) {
        vertices[i].f4vector = mesh.vertices[i];
        rand1[i].f4vector = randFloat4();
        rand2[i].f4vector = randFloat4();
        rand3[i].f4vector = randFloat4();
        rand4[i].f4vector = randFloat4();
    }
    std::cout << "finished!"  << std::endl;
    for (unsigned int j = 0; j < loadFactor; j++) {
        std::cout << "SSE_TEST: " << (j+1) << "/" << loadFactor << " Crunching numbers on " << vertices.size() << " vertices... " << "\r" << std::flush;
        for (unsigned int i=0; i < vertices.size(); i++) {
            sse_float4 current = vertices[i];
            sse_float4 rand1f = rand1[i];
            sse_float4 rand2f = rand2[i];
            sse_float4 rand3f = rand3[i];
            sse_float4 rand4f = rand4[i];
            vertices[i].vector = current.vector + rand1f.vector;
            vertices[i].vector = current.vector - rand2f.vector;
            vertices[i].vector = current.vector * rand3f.vector;
            if (rand4[i].f4vector != 0) {
                vertices[i].vector = current.vector / rand4f.vector;
            }
        }
    }

    auto end_sse = std::chrono::high_resolution_clock::now();

    auto timeTakensse = std::chrono::duration_cast<std::chrono::milliseconds>(end_sse - start_sse).count();


    std::cout << std::endl;
    std::cout << "time taken SSE: " << double(timeTakensse) << "ms"<< std::endl;
}

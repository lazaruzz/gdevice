#include <stdio.h>

//////////////////////////////////////////
//// WIP: Dealing with GPU multi-threading

#define __CPU_KERNEL__(A) A 
#define __GPU_KERNEL__(A) //

#include "type/gpu.h"
//#include "type/array.h"
#include "__temp/texture.h"


__CPU_KERNEL__(
// The execution statement will tell the workload size
// https://chatgpt.com/c/672c7b56-116c-8011-b16a-adaa201c2f2d
void vecAdd(vec3* A, vec3* B, vec3* C) 
{
	uint index = gl_GlobalInvocationID.x; 	
	if (index < a.length()) {
		C[index] = A[index] + B[index];
	}
});



const int N = 1024;

vec3 color;
vec<float, 3> normal;
vec<float, 50> vector1;

//vec<vec3, 2> vector2; // TODO in gdevice this is resolved by Texture<T>
//Array<vec3> vector3;
Texture<vec3> buffer;
// TODO Can this be something like Array<T> ?
Array<vec3, 320, 200, 2> screens;

// https://claude.ai/chat/20b0365a-bec0-4347-bd81-6264b303739a
/*
//__CPU_KERNEL__( // C++ that looks like GLSL
void vecAdd(vec<vec3, N> A, vec<vec3, N> B, vec<vec3, N> C) 
{
	uint index = gl_GlobalInvocationID.x; 	
	if (index < a.length()) {
		C[index] = A[index] + B[index];
	}
}
//);
*/

__GPU_KERNEL__( // GLSL
void vecAdd(vec<vec3, N> A, vec<vec3, N> B, vec<vec3, N> C) 
{
	uint index = gl_GlobalInvocationID.x; 	
	if (index < a.length()) {
		C[index] = A[index] + B[index];
	}
});

int main()
{
    printf("Hello Bob!\n");

    // TODO: Invoke CPU kernel
    // TODO: Invoke GPU kernel


    return 0;
}
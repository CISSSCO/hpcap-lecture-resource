__kernel void vecAdd(__global int* A, __global int* B, __global int* C)
{
    int gid = get_global_id(0);

    C[gid] = A[gid] + B[gid];
}

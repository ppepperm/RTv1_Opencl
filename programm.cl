#define CONFIG_USE_DOUBLE 1

#if CONFIG_USE_DOUBLE

#if defined(cl_khr_fp64)  // Khronos extension available?
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE
#elif defined(cl_amd_fp64)  // AMD extension available?
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE
#endif

#endif // CONFIG_USE_DOUBLE

#if defined(DOUBLE_SUPPORT_AVAILABLE)

// double
typedef double real_t;
typedef double2 real2_t;
typedef double3 real3_t;
typedef double4 real4_t;
typedef double8 real8_t;
typedef double16 real16_t;
__constant real_t inc = 0.11111;
#define PI 3.14159265358979323846

#else

// float
typedef float real_t;
typedef float2 real2_t;
typedef float3 real3_t;
typedef float4 real4_t;
typedef float8 real8_t;
typedef float16 real16_t;
__constant real_t inc = 0.222222;
#define PI 3.14159265359f

#endif

typedef struct __attribute__ ((packed))	s_data
{
	real_t	param1;
	int		param2;
	char	param3;
}										t_data;


__kernel void vector_add(__global const real_t *A, __global const real_t *B, __global double *C) {

	// Get the index of the current element to be processed
	int i = get_global_id(0);
	// Do the operation
	C[i] = A[i] + B[i] + inc;
}
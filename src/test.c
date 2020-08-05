#include "../includes/cl_rt.h"

#define MAX_SOURCE_SIZE (0x100000)


typedef struct	s_data
{
	char	param3;
	int		param2;
	double	param1;
	t_p3	pos;
}				t_data;

int main(void) {
	// Create the two input vectors
	int i;
	const int LIST_SIZE = 1024;
	double *A = (double*)malloc(sizeof(double)*LIST_SIZE);
	double *B = (double*)malloc(sizeof(double)*LIST_SIZE);
	for(i = 0; i < LIST_SIZE; i++) {
		A[i] = i;
		B[i] = LIST_SIZE - i;
	}
	t_data	*test = (t_data*)malloc(sizeof(t_data)*LIST_SIZE);
	for(i = 0; i < LIST_SIZE; i++)
	{
		test[i].param1 = i;
		test[i].param2 = i;
		test[i].param3 = 'a';
		test[i].pos.x = 3;
		test[i].pos.y = 4;
		test[i].pos.z = 5;
	}

	// Loading source code of all files composing a Kernel program
	int fd;
	char *source_str;
	size_t source_size;

	fd = open("src/programm.cl", O_RDWR);
	if (fd < 0) {
		printf("Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = read(fd, source_str, MAX_SOURCE_SIZE);
	close(fd);

	char *header_str;
	size_t	header_size;
	fd = open("includes/cl_header.h", O_RDWR);
	if (fd < 0) {
		printf("Failed to load header.\n");
		exit(1);
	}
	header_str = (char*)malloc(MAX_SOURCE_SIZE);
	header_size = read(fd, header_str, MAX_SOURCE_SIZE);
	close(fd);
	//printf("header %s", header_str);

	char *function_str;
	size_t	function_size;
	fd = open("src/abs.cl", O_RDWR);
	if (fd < 0) {
		printf("Failed to load abs.cl \n");
		exit(1);
	}
	function_str = (char*)malloc(MAX_SOURCE_SIZE);
	function_size = read(fd, function_str, MAX_SOURCE_SIZE);
	close(fd);

	// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,
						  &device_id, &ret_num_devices);
	printf("%d\n", ret_num_platforms);

	// Create an OpenCL context
	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	// Create memory buffers on the device for each vector
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
									  LIST_SIZE * sizeof(double), NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
									  LIST_SIZE * sizeof(t_data), NULL, &ret);
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
									  LIST_SIZE * sizeof(double), NULL, &ret);

	// Copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
							   LIST_SIZE * sizeof(double), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,
								LIST_SIZE * sizeof(t_data), test, 0, NULL, NULL);

	// Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1,
													(const char **)&source_str, (const size_t *)&source_size, &ret);
	// Create a program obj from header src
	cl_program header = clCreateProgramWithSource(context, 1,
													(const char **)&header_str, (const size_t *)&header_size, &ret);
	// Create a program obj from function src
	cl_program func = clCreateProgramWithSource(context, 1,
													(const char **)&function_str, (const size_t *)&function_size, &ret);
	// Build the program
	char *h_str = "../includes/cl_header.h";
	ret = clCompileProgram (program, ret_num_devices, &device_id, NULL, 1, &header, (const char **)&h_str, NULL, NULL);

	ret = clCompileProgram (func, ret_num_devices, &device_id, NULL, 1, &header, (const char **)&h_str, NULL, NULL);

	char *ret_str = (char*)malloc(sizeof(char)*100000);
	ret = clGetProgramBuildInfo (program, device_id, CL_PROGRAM_BUILD_LOG, 100000, ret_str, NULL);
	printf("%d main BUILD_INFO: %s\n", ret, ret_str);
	free(ret_str);
	ret_str = (char*)malloc(sizeof(char)*100000);
	ret = clGetProgramBuildInfo (func, device_id, CL_PROGRAM_BUILD_LOG, 100000, ret_str, NULL);
	printf("%d funk BUILD_INFO: %s\n", ret, ret_str);
	free(ret_str);
	cl_program objs[2];

	objs[0] = program;
	objs[1] = func;

	program = clLinkProgram(context, ret_num_devices, &device_id, NULL, 2, objs, NULL, NULL, &ret);
	ret_str = (char*)malloc(sizeof(char)*100000);
	ret = clGetProgramBuildInfo (program, device_id, CL_PROGRAM_BUILD_LOG, 100000, ret_str, NULL);
	printf("%d all BUILD_INFO: %s\n", ret, ret_str);
	// Create the OpenCL kernel
	cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);

	// Set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);

	// Execute the OpenCL kernel on the list
	size_t global_item_size = LIST_SIZE; // Process the entire lists
	size_t local_item_size = 1; // Divide work items into groups of 64
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
								 &global_item_size, &local_item_size, 0, NULL, NULL);

	// Read the memory buffer C on the device to the local variable C
	double *C = (double*)malloc(sizeof(double)*LIST_SIZE);
	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0,
							  LIST_SIZE * sizeof(double), C, 0, NULL, NULL);

	// Display the result to the screen
	for(i = 0; i < 3; i++)
		printf(" %f\n", C[i]);

	// Clean up
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj);
	ret = clReleaseMemObject(c_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(A);
	free(B);
	free(test);
	free(C);
	return 0;
}
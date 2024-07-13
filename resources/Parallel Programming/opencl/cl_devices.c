#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __APPLE__

#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
//
//  define VERBOSE if you want to print info about work groups sizes
//#define  VERBOSE 1
#ifdef VERBOSE
 extern int err_code(cl_int);
#endif

//int output_device_info(cl_device_id device_id)
int main()
{
	int error, i;
	cl_device_id device_id;
	cl_device_type device_type; 
	cl_uint num_units; 
	cl_char vendor_name[1000] = {0};
	cl_char device_name[1000] = {0};
	cl_uint max_work_item_dims;
	size_t max_workgroup_size;
	size_t *max_dims_size;

	cl_uint numPlatforms;

	// Get number of platforms
	error = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (numPlatforms == 0)
	{
		printf("\nError!! No platforms found!!!\n");
		return 1;
	}
	
	printf("\nTotal %d platforms found!!!",numPlatforms);
	
	// Get all platforms
	cl_platform_id Platform[numPlatforms];
	error = clGetPlatformIDs(numPlatforms, Platform, NULL);
	
	for (i = 0; i < numPlatforms; i++)
	{
		error = clGetDeviceIDs(Platform[i], CL_DEVICE_TYPE_DEFAULT, 1, &device_id, NULL);
		if (error == CL_SUCCESS)
		{
			break;
		}
	}

	if (device_id == NULL)
	{
		printf("\nError!! Cannot get device ID...");
		return 1;
	}

	error = clGetDeviceInfo(device_id, CL_DEVICE_NAME, sizeof(device_name), &device_name, NULL);
	if (error != CL_SUCCESS)
	{
		printf("\nError!! Cannot get device name!\n");
		return 1;
	}
	printf("\nDevice Name :  %s ",device_name);

	error = clGetDeviceInfo(device_id, CL_DEVICE_TYPE, sizeof(device_type), &device_type, NULL);
	if (error != CL_SUCCESS)
	{
		printf("\nError!! Cannot access device type!\n");
		return 1;
	}
	if(device_type  == CL_DEVICE_TYPE_GPU)
	printf("\nDevice Type : GPU ");

	else if (device_type == CL_DEVICE_TYPE_CPU)
	printf("\nDevice Type : CPU");

	else 
	printf("\nThe device is neither CPU nor GPU!!!");

	error = clGetDeviceInfo(device_id, CL_DEVICE_VENDOR, sizeof(vendor_name), &vendor_name, NULL);
	if (error != CL_SUCCESS)
	{
		printf("\nError!! Cannot get device vendor name!\n");
		return 1;
	}
	printf("\nVendor name : %s ",vendor_name);

	error = clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &num_units, NULL);
	if (error != CL_SUCCESS)
	{
		printf("\nError!! Cannot get device number of compute units!\n");
		return 1;
	}
	printf("\nCompute units: %d",num_units);

	error = clGetDeviceInfo( device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &max_work_item_dims, NULL);
	if (error != CL_SUCCESS)
	{
		printf("\nError!! Cannot get MAX_WORK_ITEM_DIMENSIONS!\n");
		return 1;
	}
	
	max_dims_size = (size_t*)malloc(max_work_item_dims * sizeof(size_t));
	if(max_dims_size == NULL){
	printf("\nError!! Cannot allocate memory for max_work_item_dims!\n");
	return 1;
	}
	error = clGetDeviceInfo( device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, max_work_item_dims*sizeof(size_t), max_dims_size, NULL);
	if (error != CL_SUCCESS)
	{
		printf("\nError!! Cannot get MAX_WORK_ITEM_SIZES!\n");
		return 1;
	}
	
	printf("\nMAX_WORK_ITEM_SIZES :");
	for(int i=0; i< max_work_item_dims; i++)
	{
		printf("\t%d",(int)(*(max_dims_size+i)));
	}
	
	error = clGetDeviceInfo( device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &max_workgroup_size, NULL);
	if (error != CL_SUCCESS)
	{
		printf("\nError!! Cannot get MAX_WORK_GROUP_SIZE!\n");
		return 1;
	}
	
	printf("\nMax work group size: %d\n",(int)max_workgroup_size);
}

 

#include <iostream>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

void init_array(double row, double col, double off, int arrSize, double **array)
{
  int i,j;

  for (i=0; i<arrSize; i++) {
    for (j=0; j<arrSize; j++) {
      array[i][j] = row*i+col*j+off;
    }
  }
}

void print_array(char * name, int arrSize, double **array)
{
  int i,j;

  cout << endl << name << endl;
  for (i=0;i<arrSize;i++){
    for (j=0;j<arrSize;j++) {
      cout << "\t" << array[i][j];
    }
    cout << endl;
  }
}

void multiply_d(int arrSize, double **aMatrix, double **bMatrix, double **product)
{
  for(int i=0;i<arrSize;i++) {
    for(int j=0;j<arrSize;j++) {
      double sum = 0;
      for(int k=0;k<arrSize;k++) {
        sum += aMatrix[i][k] * bMatrix[k][j];
      }
      product[i][j] = sum;
    }
  }
}

int main(int argc, char*argv[]){
  int num=0;

  if(argc !=2) {
    cerr << "Usage: 1_mmult_serial[_debug] arraySize [default is 1024].\n";
    num = 1024;
  } else {
    num = atoi(argv[1]);
    if (num < 2) {
      cerr << "Array dimensions must be greater than 1; setting it to 2. \n" << endl;
      num = 2;
    }
    if (num > 9000) {
      cerr << "Array dimensions must not be greater than 9000; setting it to 9000. \n" << endl;
      num = 9000;
    }
  }

  double** aMatrix = new double*[num];
  double** bMatrix = new double*[num];
  double** product = new double*[num];

  for (int i=0; i<num; i++) {
    aMatrix[i] = new double[num];
    bMatrix[i] = new double[num];
    product[i] = new double[num];
  }

  init_array(3,-2,1,num,aMatrix);
  init_array(-2,1,3,num,bMatrix);

  cout << "Size: " << num <<  " X "<< num << endl;

  struct timeval startTime, endTime;
  gettimeofday(&startTime, NULL);
  multiply_d(num, aMatrix, bMatrix, product);
  gettimeofday(&endTime, NULL);

  if (num < 6) {
    print_array((char*)("aMatrix"), num, aMatrix);
    print_array((char*)("bMatrix"), num, bMatrix);
    print_array((char*)("product"), num, product);
  }

  double useconds = (endTime.tv_sec*1000000 + endTime.tv_usec) - (startTime.tv_sec*1000000 + startTime.tv_usec);
  double seconds = useconds/1000000;
  cout << endl << "Calculations took " << seconds << " sec.\n";

  for (int i=0; i<num; i++) {
    delete [] aMatrix[i];
    delete [] bMatrix[i];
    delete [] product[i];
  }

  delete [] aMatrix;
  delete [] bMatrix;
  delete [] product;

  return 0;
}
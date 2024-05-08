help(){
    echo
    echo "Usage: submit.sh -[flags]"
    echo "-h                : help"
    echo "-f <filename>     : enter file"
    echo "-N <threads>      : number of threads"
    echo "-c <compile>      : first compile"
    echo "-i <iterations>   : enter partition"
    echo 
}

isCompiled=0
nthreads=8

while getopts 'N:f:i:hc' flag; do
  case "${flag}" in
    N) nthreads="${OPTARG}" ;;
    f) file=${OPTARG} ;;
    c) isCompiled=1 ;;
    i) iterations="${OPTARG}" ;;
    h) help 
        exit 1 ;;
    *) echo "Invalid flag...(-h for help)"
       exit 1 ;;
  esac

  
done

if [[ -z $file ]]; then
    echo "You forgot to mention filename!!!"
    exit 1 
fi
if [[ -z $iterations ]]; then
    iterations=1
fi



outputFile="${file%.*}.out"      # extract the name of the file without extension and adding extension .out

if [[ $isCompiled == 1 ]]; then
    gcc $file -o $outputFile -fopenmp -lm 
fi

export OMP_NUM_THREADS=$nthreads

echo "--------------------------------------------------------"
i=1
while [ 1 == 1 ];
do
    ./$outputFile
    if [[ $i == $iterations ]]; then
        exit 1
    fi
    i=$(( $i + 1 ))
    echo "--------------------------------------------------------"
done

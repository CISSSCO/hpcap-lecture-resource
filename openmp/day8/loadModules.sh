# to run this file type the below command in your terminal after login
# . path_to_loadModules.sh (eg: . /home/user1/loadModules)
# this will source your spack 
source /home/apps/spack/share/spack/setup-env.sh

# to load gcc
# enter your version hash after '/'
# the same you'll have to do for every packages you want to load
# general syntax : spack load package_name/package-hash
# if there are only one version of package installed in your system then
# you only need to do : 'spack load gcc' and it will load the available version
spack load gcc/your-version-hash

#!/bin/bash

pushd `dirname "$0"`

export TF_CFLAGS=( $(python -c 'import tensorflow as tf; print(" ".join(tf.sysconfig.get_compile_flags()))') )
export TF_LFLAGS=( $(python -c 'import tensorflow as tf; print(" ".join(tf.sysconfig.get_link_flags()))') )

g++ -std=c++14 -fpermissive -fPIC -shared irods_file_system.cc -o irods_file_system.so -I/opt/irods-externals/boost1.60.0-0/include -I/usr/include/irods -lirods_common -lirods_client ${TF_CFLAGS[@]} ${TF_LFLAGS[@]} -Og

# /opt/irods-externals/clang6.0-0/bin/clang++ -c -stdlib=libc++ -fPIC irods_file_system.cc -I/usr/include/irods -I/opt/irods-externals/boost1.60.0-0/include ${TF_CFLAGS[@]}
# /opt/irods-externals/clang6.0-0/bin/clang++ -c -stdlib=libstdc++ -fPIC irods_file_system.cc -I/usr/include/irods -I/opt/irods-externals/boost1.60.0-0/include ${TF_CFLAGS[@]}
# /opt/irods-externals/clang6.0-0/bin/clang++ -shared irods_file_system.o -Wl,--no-undefined ${TF_LFLAGS[@]} -lirods_client -Og -o irods_file_system.so

#!/bin/bash

pushd `dirname "$0"`

export TF_CFLAGS=( $(python -c 'import tensorflow as tf; print(" ".join(tf.sysconfig.get_compile_flags()))') )
export TF_LFLAGS=( $(python -c 'import tensorflow as tf; print(" ".join(tf.sysconfig.get_link_flags()))') )

g++ -std=c++14 -fpermissive -shared irods_file_system.cc /usr/lib/libRodsAPIs.a -o irods_file_system.so -fPIC -I/opt/irods-externals/boost1.60.0-0/include -I/usr/include/irods ${TF_CFLAGS[@]} ${TF_LFLAGS[@]} -O2

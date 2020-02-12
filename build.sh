#!/bin/bash

pushd `dirname "$0"`

export TF_CFLAGS=( $(python -c 'import tensorflow as tf; print(" ".join(tf.sysconfig.get_compile_flags()))') )
export TF_LFLAGS=( $(python -c 'import tensorflow as tf; print(" ".join(tf.sysconfig.get_link_flags()))') )

g++ -std=c++11 -shared irods_file_system.cc -o irods_file_system.so -fPIC ${TF_CFLAGS[@]} ${TF_LFLAGS[@]} -O2
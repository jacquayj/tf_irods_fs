# tf_irods_fs: TensorFlow iRODS Filesystem

<img title="iRODS <3 TF" width="500px" src="logo.png">

A native iRODS filesystem for TensorFlow

## Helpful Development Links

* https://docs.w3cub.com/tensorflow~guide/extend/add_filesys/
* https://www.tensorflow.org/install/source
* https://github.com/korydraughn/irods_api_examples#irods-filesystem
* https://docs.w3cub.com/tensorflow~guide/extend/adding_an_op/#build_the_op_library

## Usage

```python
import tensorflow as tf

tf.load_file_system_library('irods_file_system.so')

with tf.gfile.Open("irods://path/to/file.txt") as w:
    w.write("hi")

```
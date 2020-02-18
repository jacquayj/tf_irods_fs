import tensorflow as tf

tf.load_library('./irods_file_system.so')

with tf.io.gfile.GFile("irods://path/to/file.txt", mode='w') as f:
    f.write("hi")

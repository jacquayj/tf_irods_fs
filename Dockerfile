FROM tensorflow/tensorflow

RUN apt-get install -y lsb-release wget gpg-agent vim
RUN wget -qO - https://packages.irods.org/irods-signing-key.asc | apt-key add -
#RUN echo "deb [arch=amd64] https://packages.irods.org/apt/ $(lsb_release -sc) main" | tee /etc/apt/sources.list.d/renci-irods.list
RUN echo "deb [arch=amd64] https://packages.irods.org/apt/ trusty main" | tee /etc/apt/sources.list.d/renci-irods.list
RUN apt-get update

RUN apt-get install -y irods-dev irods-runtime irods-externals-boost1.60.0-0 irods-externals-clang3.8-0

RUN ln -s /usr/include/locale.h /usr/include/xlocale.h

COPY . /tf_irods_fs
COPY irods_environment.json /root/.irods/irods_environment.json

WORKDIR /tf_irods_fs

RUN /tf_irods_fs/build.sh

CMD "/usr/bin/python" "/tf_irods_fs/test.py"

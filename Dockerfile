FROM tensorflow/tensorflow

RUN apt-get install -y lsb-release wget gpg-agent
RUN wget -qO - https://packages.irods.org/irods-signing-key.asc | apt-key add -
RUN echo "deb [arch=amd64] https://packages.irods.org/apt/ $(lsb_release -sc) main" | tee /etc/apt/sources.list.d/renci-irods.list
RUN echo "deb [arch=amd64] https://packages.irods.org/apt/ precise main" | tee /etc/apt/sources.list.d/renci-irods.list
RUN apt-get update

RUN apt-get install -y irods-dev

COPY . /tf_irods_fs

RUN /tf_irods_fs/build.sh


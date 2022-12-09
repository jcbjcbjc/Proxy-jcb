FROM ubuntu:22.04

ARG PROJECT_REPO=https://github.com/jcbjcbjc/Proxy-jcb.git
ARG EXECUTE_FUNCTION
ARG  LISTEN_IP
ARG LISTEN_PORT
ARG HOME=/root
ENV LISTEN_IP=${LISTEN_IP:-0.0.0.0}
ENV LISTEN_PORT=${LISTEN_PORT:-8000}

WORKDIR ${HOME}
RUN git clone ${PROJECT_REPO} --depth=1 \
        && cd src \
        && chmod +x ./build.sh \
        &&./build.sh




WORKDIR /OI-wiki
EXPOSE ${LISTEN_PORT}
CMD ["/bin/bash"]



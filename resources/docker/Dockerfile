# We're using Ubuntu 21.10 because JetBrains CLion doesn't yet support the
# versions of cmake and dbg that install on 22.04.
#
# See: https://blog.jetbrains.com/clion/2021/10/clion-2021-3-eap-new-docker-toolchain/
# and: https://www.jetbrains.com/help/clion/2022.1/clion-toolchains-in-docker.html#create-docker-toolchain
FROM ubuntu:21.10

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y build-essential clang git

# Install ICU
RUN cd /tmp \
    && git clone https://github.com/unicode-org/icu.git \
    && cd icu/icu4c/source/ \
    && git checkout release-71-1 \
    && ./runConfigureICU Linux \
    && make -j$(nproc) \
    && make install

# Install PHP
RUN apt-get update \
    && ln -fs /usr/share/zoneinfo/Etc/UTC /etc/localtime \
    && apt-get install -y \
        apt-transport-https \
        ca-certificates \
        lsb-release \
        software-properties-common \
        tzdata \
    && dpkg-reconfigure --frontend noninteractive tzdata \
    && apt-add-repository -y ppa:ondrej/php \
    && apt-get update \
    && apt-get -y install php8.1 php8.1-dev

# Tools for use with JetBrains CLion
RUN apt-get update \
    && apt-get install -y cmake gdb locales wget \
    && locale-gen en_US.UTF-8 \
    && ln -fs /tmp/ecma_intl/modules/ecma_intl.so "$(php-config --extension-dir)/ecma_intl.so"

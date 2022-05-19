# We're using Ubuntu 21.10 because JetBrains CLion doesn't yet support the
# versions of cmake and dbg that install on 22.04.
#
# See: https://blog.jetbrains.com/clion/2021/10/clion-2021-3-eap-new-docker-toolchain/
# and: https://www.jetbrains.com/help/clion/2022.1/clion-toolchains-in-docker.html#create-docker-toolchain
FROM ubuntu:21.10

ENV DEBIAN_FRONTEND=noninteractive

# Configure the system for building ICU and PHP.
RUN apt-get update \
    && ln -fs /usr/share/zoneinfo/Etc/UTC /etc/localtime \
    && apt-get install -y \
        autoconf \
        automake \
        ca-certificates \
        clang \
        cmake \
        curl \
        g++ \
        gcc \
        gdb \
        libc6-dev \
        libffi7 \
        libpcre2-dev \
        libsqlite3-dev \
        libssl-dev \
        libtool \
        locales \
        make \
        pkg-config \
        shtool \
        tzdata \
    && dpkg-reconfigure --frontend noninteractive tzdata \
    && locale-gen en_US.UTF-8

# Install ICU
RUN cd /tmp \
    && curl -LOs https://github.com/unicode-org/icu/releases/download/release-71-1/icu4c-71_1-src.tgz \
    && tar -zxf icu4c-71_1-src.tgz \
    && cd icu/source/ \
    && ./runConfigureICU Linux \
    && make -j$(nproc) \
    && make install \
    && ldconfig \
    && cd /tmp \
    && rm -rf /tmp/icu /tmp/icu4c-71_1-src.tgz

# Install PHP
RUN cd /tmp \
    && curl -LOs https://www.php.net/distributions/php-8.1.6.tar.xz \
    && tar -Jxf php-8.1.6.tar.xz \
    && cd php-8.1.6/ \
    && ./configure \
        --enable-debug \
        --enable-zts \
        --with-layout=GNU \
        --with-config-file-scan-dir=/usr/local/etc/php.conf.d \
    && make -j$(nproc) \
    && make install \
    && mkdir -p "$(php-config --extension-dir)" \
    && mkdir -p "$(php-config --ini-dir)" \
    && cp php.ini-development "$(php-config --ini-path)/php.ini" \
    && cd /tmp \
    && rm -rf /tmp/php-8.1.6 /tmp/php-8.1.6.tar.xz

# Prepare for running tests with ecma_intl from JetBrains CLion.
RUN ln -fs /tmp/ecma_intl/modules/ecma_intl.so "$(php-config --extension-dir)/ecma_intl.so"

WORKDIR /tmp/ecma_intl

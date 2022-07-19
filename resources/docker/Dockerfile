# We're using Ubuntu 21.10 because JetBrains CLion doesn't yet support the
# versions of cmake and dbg that install on 22.04.
#
# See: https://blog.jetbrains.com/clion/2021/10/clion-2021-3-eap-new-docker-toolchain/
# and: https://www.jetbrains.com/help/clion/2022.1/clion-toolchains-in-docker.html#create-docker-toolchain
FROM ubuntu:21.10

ARG icu=71.1
ARG php=8.1.8

ENV DEBIAN_FRONTEND=noninteractive

SHELL ["/bin/bash", "-c"]

# Configure the system for building ICU and PHP.
RUN apt-get update \
    && ln -fs /usr/share/zoneinfo/Etc/UTC /etc/localtime \
    && apt-get install -y \
        autoconf \
        automake \
        bison \
        ca-certificates \
        clang \
        cmake \
        curl \
        g++ \
        gcc \
        gdb \
        libbz2-dev \
        libc6-dev \
        libcurl4-openssl-dev \
        libffi7 \
        libonig-dev \
        libpcre2-dev \
        libsqlite3-dev \
        libssl-dev \
        libtool \
        libzip-dev \
        locales \
        make \
        pkg-config \
        re2c \
        shtool \
        tzdata \
        zip \
        zlib1g-dev \
    && dpkg-reconfigure --frontend noninteractive tzdata \
    && locale-gen en_US.UTF-8

# Install PHP
RUN cd /tmp \
    && curl -LOs "https://www.php.net/distributions/php-${php}.tar.xz" \
    && tar -Jxf "php-${php}.tar.xz" \
    && cd "php-${php}/" \
    && ./configure \
        --enable-debug \
        --enable-mbstring \
        --enable-zts \
        --with-bz2 \
        --with-config-file-scan-dir=/usr/local/etc/php.conf.d \
        --with-curl \
        --with-ffi \
        --with-layout=GNU \
        --with-openssl \
        --with-zip \
        --with-zlib \
    && make -j$(nproc) \
    && make install \
    && mkdir -p "$(php-config --extension-dir)" \
    && mkdir -p "$(php-config --ini-dir)" \
    && cp php.ini-development "$(php-config --ini-path)/php.ini" \
    && cd /tmp \
    && rm -rf "/tmp/php-${php}" "/tmp/php-${php}.tar.xz"

# Install ICU
RUN export icu_dash="${icu//./-}" \
    && export icu_under="${icu//./_}" \
    && cd /tmp \
    && curl -LOs "https://github.com/unicode-org/icu/releases/download/release-${icu_dash}/icu4c-${icu_under}-src.tgz" \
    && tar -zxf "icu4c-${icu_under}-src.tgz" \
    && cd icu/source/ \
    && ./runConfigureICU Linux \
    && make -j$(nproc) \
    && make install \
    && ldconfig \
    && cd /tmp \
    && rm -rf /tmp/icu "/tmp/icu4c-${icu_under}-src.tgz"

# Prepare for running tests with ecma_intl from JetBrains CLion.
RUN ln -fs /tmp/ext-ecma_intl/modules/ecma_intl.so "$(php-config --extension-dir)/ecma_intl.so"

# Add additional tools
COPY composer-install.sh /usr/bin
RUN apt-get update \
    && apt-get install -y \
        git \
        libcriterion-dev \
        valgrind \
    && /usr/bin/composer-install.sh \
    && mv composer.phar /usr/bin/composer \
    && rm /usr/bin/composer-install.sh

WORKDIR /tmp/ext-ecma_intl

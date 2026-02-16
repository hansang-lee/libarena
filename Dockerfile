FROM debian:11-slim AS builder

RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update \
 && apt-get install -y --fix-missing --no-install-recommends \
    sudo tar wget git cmake make libstdc++6 gcc g++ clang-format ninja-build \
 && rm -rf /var/lib/apt/lists/* \
 && apt-get clean

ARG USERNAME="admin"
ARG UID="1000"
ARG GID="1000"
RUN groupadd --gid ${GID} ${USERNAME} \
 && useradd --uid ${UID} --gid ${GID} -m ${USERNAME} \
 && usermod -a -G video ${USERNAME} \
 && usermod -a -G dialout ${USERNAME} \
 && echo "${USERNAME} ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME} \
 && chmod 0440 /etc/sudoers.d/${USERNAME}

# install sdk
ARG LIBRARY_PATH="/usr/local/lib/arena"
RUN mkdir -p ${LIBRARY_PATH} && \
    wget -qO- --no-check-certificate "https://github.com/hansang-lee/packages/releases/download/arena-0.1.68/ArenaSDK_v0.1.68_Linux_x64.tar.gz" \
    | tar --extract --gzip \
          --directory=${LIBRARY_PATH} \
          --strip-components=1 \
          --exclude=*.conf \
          --exclude=docs \
          --exclude=Examples \
          --exclude=Utilities \
          --exclude=precompiledExamples \
 && echo "${LIBRARY_PATH}/lib64" > "/etc/ld.so.conf.d/ArenaSDK.conf" \
 && echo "${LIBRARY_PATH}/ffmpeg" >> "/etc/ld.so.conf.d/ArenaSDK.conf" \
 && echo "${LIBRARY_PATH}/GenICam/library/lib/Linux64_x64" >> "/etc/ld.so.conf.d/ArenaSDK.conf" \
 && ldconfig

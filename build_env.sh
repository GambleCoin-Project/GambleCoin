#!/bin/bash

export MANPATH=/usr/local/share/man:$MANPATH

brew_pkgconf=/usr/local/opt/pkg-config
PATH=${brew_pkgconf}/bin:$PATH
CPPFLAGS="${CPPFLAGS} -I${brew_pkgconf}/share/aclocal"
m4path="${brew_pkgconf}/share/aclocal"
MANPATH=${brew_pkgconf}/share/man:$MANPATH

brew_libtool=/usr/local/opt/libtool
PATH=${brew_libtool}/bin:$PATH
dyld_library_path=${brew_libtool}/lib:${DYLD_LIBRARY_PATH}

LDFLAGS="${LDFLAGS} -L${brew_libtool}/lib"
CPPFLAGS="${CPPFLAGS} -I${brew_libtool}/include"
m4path="${brew_libtool}/share/aclocal:$m4path"
MANPATH=${brew_libtool}/share/man:$MANPATH

brew_m4=/usr/local/opt/m4
PATH=${brew_m4}/bin:$PATH
MANPATH=${brew_m4}/share/man:$MANPATH

brew_autoconf=/usr/local/opt/autoconf
PATH=${brew_autoconf}/bin:$PATH
# m4path="${brew_autoconf}/share/autoconf/autoconf:${brew_autoconf}/share/autoconf/m4sugar:$m4path"
export MANPATH=${brew_autoconf}/share/man:$MANPATH

brew_automake=/usr/local/opt/automake
PATH=${brew_automake}/bin:$PATH
m4path="${brew_automake}/share/aclocal-1.16:$m4path"
MANPATH=${brew_automake}/share/man:$MANPATH

brew_openssl=/usr/local/opt/openssl
PATH=${brew_openssl}/bin:$PATH
dyld_library_path=${brew_openssl}/lib:${dyld_library_path}
LDFLAGS="${LDFLAGS} -L${brew_openssl}/lib"  #  -lcrypto -lssl"
CPPFLAGS="${CPPFLAGS} -I${brew_openssl}/include"
MANPATH=${brew_openssl}/share/man:$MANPATH

brew_boost=/usr/local/opt/boost
PATH=${brew_boost}/bin:$PATH
dyld_library_path=${brew_boost}/lib:${dyld_library_path}
export LDFLAGS="${LDFLAGS} -L${brew_boost}/lib"
export CPPFLAGS="${CPPFLAGS} -I${brew_boost}/include/boost"

brew_libevent=/usr/local/opt/libevent
PATH=${brew_libevent}/bin:$PATH
dyld_library_path=${brew_libevent}/lib:${dyld_library_path}
LDFLAGS="${LDFLAGS} -L${brew_libevent}/lib"
CPPFLAGS="${CPPFLAGS} -I${brew_libevent}/include"
MANPATH=${brew_libevent}/share/man:$MANPATH

brew_bdb=/usr/local/opt/berkeley-db@4
PATH=${brew_bdb}/bin:$PATH
dyld_library_path=${brew_bdb}/lib:${dyld_library_path}
LDFLAGS="${LDFLAGS} -L${brew_bdb}/lib"
CPPFLAGS="${CPPFLAGS} -I${brew_bdb}/include"

brew_qt=/usr/local/opt/qt
PATH=${brew_qt}/bin:$PATH
dyld_library_path=${brew_qt}/lib:${dyld_library_path}
export LDFLAGS="${LDFLAGS} -L${brew_qt}/lib"
export CPPFLAGS="${CPPFLAGS} -I${brew_qt}/include"

brew_protobuf=/usr/local/opt/protobuf
PATH=${brew_protobuf}/bin:$PATH
dyld_library_path=${brew_protobuf}/lib:${dyld_library_path}
LDFLAGS="${LDFLAGS} -L${brew_protobuf}/lib"
CPPFLAGS="${CPPFLAGS} -I${brew_protobuf}/include"

# Add brew "cmake" formula *last* to environment, 
brew_cmake=/usr/local/Cellar/cmake/3.9.0
PATH=$PATH:${brew_cmake}/bin
MANPATH=${brew_cmake}/share/man:$MANPATH

#Note: ACLOCAL_PATH which points to all important m4 macro definition of PKG_PROG_PKG_CONFIG & others..
export ACLOCAL_PATH=$m4path

export EDITOR=/usr/bin/nano

export bitcoin_enable_qt=yes

my_prefix=/Users/rshaw/local
export PATH=${my_prefix}/bin:$PATH
export DYLD_LIBRARY_PATH=${my_prefix}/lib:${dyld_library_path}
export LDFLAGS
export CPPFLAGS
export MANPATH
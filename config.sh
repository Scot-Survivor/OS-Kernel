SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS='-g'

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

# Setup Path for cross compiler
export PREFIX="$HOME/opt/cross"
export PATH="$PREFIX/bin:$PATH"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi

echo "Configured variables:"
echo "MAKE=$MAKE"
echo "HOST=$HOST"
echo "AR=$AR"
echo "AS=$AS"
echo "CC=$CC"
echo "PREFIX=$PREFIX"
echo "SYSROOT=$SYSROOT"
echo "CFLAGS=$CFLAGS"
echo "CPPFLAGS=$CPPFLAGS"
echo "PATH=$PATH"
echo "LIBDIR=$LIBDIR"
echo "INCLUDEDIR=$INCLUDEDIR"
echo "EXEC_PREFIX=$EXEC_PREFIX"
echo "BOOTDIR=$BOOTDIR"
echo "PROJECTS=$PROJECTS"
echo "SYSTEM_HEADER_PROJECTS=$SYSTEM_HEADER_PROJECTS"

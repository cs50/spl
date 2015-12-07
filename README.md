# Stanford Portable Library (SPL)

This is CS50's fork of Eric Roberts' Stanford Portable Library.

## Building

### Fedora

    sudo yum install -y bash binutils coreutils findutils gcc java-1.?.0-openjdk-devel
    git clone git@github.com:cs50/spl.git
    cd spl
    make
    sudo make install

### Ubuntu

    sudo apt-get install -y build-essential git openjdk-7-jdk
    git clone git@github.com:cs50/spl.git
    cd spl
    make
    sudo make install

## TODO

* Bug fixes.
* Re-generate `docs`.
* Tidy `Makefile`.

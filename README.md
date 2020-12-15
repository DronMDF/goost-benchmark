# goost-benchmark

[goost](https://github.com/DronMDF/goost) library comparsion benchmark.

# Principles of the project

* No code in ctor
* Only one primary ctor (all other are delegating to primary)
* No static
* No null
* No new (use make_unique or make_shared)
* All classes are final
* All base classes are abstract (with default virtual dtor)
* All method are const (exclude private classes)
* All member are private and const (exclude private classes)

# Building

```sh
$ conan remote add mdf https://api.bintray.com/conan/mdf/pureoop
$ conan install <path to goost> -s compiler.libcxx='libstdc++11' --build 2out
$ cmake -GNinja <path to goost>
$ ninja
$ ninja test
```

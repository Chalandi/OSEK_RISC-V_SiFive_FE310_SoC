OSEK_RISC-V_SiFive_FE310_SoC
==================

<p align="center">
    <a href="https://github.com/chalandi/OSEK_RISC-V_SiFive_FE310_SoC/actions">
        <img src="https://github.com/chalandi/OSEK_RISC-V_SiFive_FE310_SoC/actions/workflows/OSEK_RISC-V_SiFive_FE310_SoC.yml/badge.svg" alt="Build Status"></a>
    <a href="https://github.com/chalandi/OSEK_RISC-V_SiFive_FE310_SoC/issues?q=is%3Aissue+is%3Aopen+sort%3Aupdated-desc">
        <img src="https://custom-icon-badges.herokuapp.com/github/issues-raw/chalandi/OSEK_RISC-V_SiFive_FE310_SoC?logo=github" alt="Issues" /></a>
    <a href="https://github.com/chalandi/OSEK_RISC-V_SiFive_FE310_SoC">
        <img src="https://img.shields.io/github/languages/code-size/chalandi/OSEK_RISC-V_SiFive_FE310_SoC" alt="GitHub code size in bytes" /></a>
</p>

This repository implements an OSEK-like, bare-metal
operating system for RISC-V (SiFive RISC-V FE310 SoC).
The goals are to achieve near-compatibility with OSEK (ECC1/BCC1)
and to provide an intuitive, easy-to-understand sample application
that can be extended for your own projects.

Features include:
  - OSEK-like OS implementation with support of most common features.
  - The sample application runs on the SparkFun _Red_ _Thing_ RISC-V FE310 Board.
  - Tasks and events interact to produce a blinky LED show featuring the blue LED toggling at 1/2 Hz (blue).
  - Use a simple self-written bare-metal startup.
  - Power, clock and port initialization.
  - Implementation in C99 with absolute minimal use of assembly.

A clear and easy-to-understand build system based on free GNUmake/GCC.

This repository provides keen insight on writing your own
_bare_ _metal_ operating system from scratch on a modern
microcontroller using entirely free tools and open standards.

## Details on the Application

Following low-level chip initialization, the program jumps
to the `main()` subroutine in [main.c](./Code/main.c).
Here there are two functional lines. The first line initializes the LEDs.
The second line subsequently starts the operatng system via call
to `OS_StartOS()`.

An idle task and one single extended task animate the user LED,
providing a simple blinky LED show featuring the blue
LED toggling at 1/2 Hz (blue). These straightforward sample
tasks can be found in [tasks.c](./Code/tasks.c).

## Toolchain

The toolchain used to build this project is `riscv64-unknown-elf` you can download it using this link:
 https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.12/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz

## Building the Application

### Build with GNUmake on `*nix`

Build on `*nix*` is easy using an installed `riscv64-unknown-elf`

```sh
cd OSEK_RISC-V_SiFive_FE310_SoC
./Rebuild.sh
```

The build results including ELF-file, HEX-mask, MAP-file
can be found in the `Output` directory following the GNUmake build.

## References
Further information on open standard OSEK can be found in ISO 17356 and in the link below:
* https://en.wikipedia.org/wiki/OSEK

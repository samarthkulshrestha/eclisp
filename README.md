<div align="center">
<h1>eclisp</h1>

samarth kulshrestha

![release version](https://img.shields.io/github/v/release/samarthkulshrestha/eclisp?color=%23a039fa&include_prereleases&style=for-the-badge)
![code quality](https://img.shields.io/codefactor/grade/github/samarthkulshrestha/eclisp/main?style=for-the-badge)
![top language](https://img.shields.io/github/languages/top/samarthkulshrestha/eclisp?color=%234877f7&style=for-the-badge)
<br>
![license](https://img.shields.io/github/license/samarthkulshrestha/eclisp?color=%23f2e85a&style=for-the-badge)
![pre-release date](https://img.shields.io/github/release-date-pre/samarthkulshrestha/eclisp?color=%23f76ad4&style=for-the-badge)
![repo size](https://img.shields.io/github/repo-size/samarthkulshrestha/eclisp?color=%2346d4a0&style=for-the-badge)
<br/><br/><br/>
![eclisp logo](assets/eclisp.png)
<br/><br>
</div>

## Introduction

<img src="assets/xkcd_eclipse.png" align="right" style="margin: 16px;" />

**Eclisp** is a [Lisp](https://en.wikipedia.org/wiki/LISP) dialect that focuses on minimalism, simplicity, and clarity. Its design decisions are guided by the following mantras:

+ **Need for speed.** Performance is a priority.
+ **Close to metal.** There is less between you and vanilla Lisp by design. That means less to work around when you tinker.
+ **Different is good.** Eclisp occasionally deviates from the original Lisp in favour of building a better, more modern language.
+ **The smaller the better.** With the binary coming in at `121kb`, and only about a thousand lines of code, Eclisp's core is tiny, without compromising on delivering a full-fledged, functional programming language.

## Prerequisites

+ a C compiler (*GNU C Compiler v12.2+ is recommended*)
+ Git v2.23+

## Install

Only GNU/Linux systems are supported.

#### language core

+ clone the repository
```
git clone https://github.com/samarthkulshrestha/eclisp.git ~/.eclisp
```

+ compile the code
```
cd ~/.eclisp/src
cc -std=c99 -Wall eclisp.c lib/mpc.c -ledit -lm -o eclisp
```

+ make sure the binary is executable
```
chmod +x ./eclisp
```

+ move the binary to somewhere in your shell's $PATH
```
mv ./eclisp ~/.local/bin/
```

#### standard library

+ move the standard library file to library location
```
cd ~/.eclisp/src
sudo cp std.eclp /lib/
```

+ set the environment variable for stdlib's location. add the following line to
  your shell's configuration file (`.bashrc` or `.zshrc`).
```
export ECLISP_ROOT="/lib"
```

## Run

+ running `eclisp` in the terminal launches the interactive prompt
```
eclisp version 1.1.15
author: samarth kulshrestha

eclisp λ
-> 
```

+ files can be executed by running
```
eclisp <filename.elcp>
```

## Contribute

 [![pull requests welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](https://makeapullrequest.com)
 [![c style guide](https://img.shields.io/badge/c-style%20guide-blue?style=flat-square)](https://cs50.readthedocs.io/style/c/)

+ I <3 pull requests and bug reports!
+ Don't hesitate to [tell me my code-fu sucks](https://github.com/samarthkulshrestha/eclisp/issues/new), but please tell me why.

## License

Eclisp is licensed under the MIT License.

Copyright (c) 2023 Samarth Kulshrestha.

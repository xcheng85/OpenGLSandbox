***INSERT GRAPHIC HERE (include hyperlink in image)***

# OpenGL SandBox

> modern opengl sandbox

**Badges will go here**

- build status
- issues
- devDependencies
- npm package
- coverage
- slack
- downloads
- gitter chat
- license
- etc.

[![Build Status](http://img.shields.io/travis/badges/badgerbadgerbadger.svg?style=flat-square)](https://travis-ci.org/badges/badgerbadgerbadger) [![Dependency Status](http://img.shields.io/gemnasium/badges/badgerbadgerbadger.svg?style=flat-square)](https://gemnasium.com/badges/badgerbadgerbadger) [![Coverage Status](http://img.shields.io/coveralls/badges/badgerbadgerbadger.svg?style=flat-square)](https://coveralls.io/r/badges/badgerbadgerbadger) [![Code Climate](http://img.shields.io/codeclimate/github/badges/badgerbadgerbadger.svg?style=flat-square)](https://codeclimate.com/github/badges/badgerbadgerbadger) [![Github Issues](http://githubbadges.herokuapp.com/badges/badgerbadgerbadger/issues.svg?style=flat-square)](https://github.com/badges/badgerbadgerbadger/issues) [![Pending Pull-Requests](http://githubbadges.herokuapp.com/badges/badgerbadgerbadger/pulls.svg?style=flat-square)](https://github.com/badges/badgerbadgerbadger/pulls) [![Gem Version](http://img.shields.io/gem/v/badgerbadgerbadger.svg?style=flat-square)](https://rubygems.org/gems/badgerbadgerbadger) [![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org) [![Badges](http://img.shields.io/:badges-9/9-ff6799.svg?style=flat-square)](https://github.com/badges/badgerbadgerbadger)

- For more on these wonderful ~~badgers~~ badges, refer to <a href="http://badges.github.io/badgerbadgerbadger/" target="_blank">`badgerbadgerbadger`</a>.


## Table of Contents (Optional)

- [Installation](#installation)
- [Features](#features)
- [Contributing](#contributing)
- [Team](#team)
- [FAQ](#faq)
- [Support](#support)
- [License](#license)

## Installation

### Build glew with MING64W + Windows

Step by Step

Download the GLEW Source files 52. DO NOT download the 32/64bit Window Binaries unless you’re using Visual Studio, and if you are, you wouldn’t be reading this.

Download 52, install, and update msys2. Unfortunately, I was unable to find a way to compile GLEW (for mingw-w64) without it, but trust me, it’s painless, and once you’re done, you don’t need msys2, we’re only using it to compile the GLEW lib files. Follow the update instructions at the official msys2 site 52 before you do anything else. It’s only 3 steps long.

Warning: For some strange reason, once you pass the second update step, the msys2 command prompt shortcut stops working on my computer. Just navigate to the c:/msys2 folder and run msys2_shell.cmd if it does.

You’ll need mingw-w64 for msys2. Some Stack Overflow answers suggest downloading both 64bit and 32bit versions of mingw, but since I’m no expert on the matter, it turned into a pain, so I was better off just downloading the 64bit version which is what I’m using and targeting. Run the following cmd in the msys2 cmd prompt: $ pacman -S gcc make mingw-w64-x86_64-gcc

3-a) You’ll need make and gcc for msys2. Run this in the msys2 cmd line: $ pacman -S gcc make

Once you’re done downloading mingw-w64, gcc, and make. You’re ready to compile GLEW. Unzip the source files you downloaded earlier, and put it into you’re C:\msys64\home\yourusername folder.

Open the msys2 cmd prompt, navigate to the glew2.x.x folder and run the following CMDs in the following order (as soon as each one is done):
5-a) make
5-b) make install
5-c) make install.all

You might get some errors and warnings, don’t worry. Look in the lib folder within the glew2.x.x folder, and you’ll see the lib files you’ll need.

Copy glew32.dll into the same folder where your programs executable is, and libglew32.a into your program’s lib folder.


cmake -G "MinGW Makefiles" -S . -B . -DCMAKE_INSTALL_PREFIX=C:\Program Files (x86)\mingw64\x86_64-w64-mingw32

### Clone

- Clone this repo to your local machine using 

### Setup

- If you want more syntax highlighting, format your code like this:

> update and install this package first

```shell
$ brew update
$ brew install fvcproductions
```

> now install npm and bower packages

```shell
$ npm install
$ bower install
```

- For all the possible languages that support syntax highlithing on GitHub (which is basically all of them), refer <a href="https://github.com/github/linguist/blob/master/lib/linguist/languages.yml" target="_blank">here</a>.

---

## Features
## Usage (Optional)
## Documentation (Optional)
## Tests (Optional)

- Going into more detail on code and technologies used
- I utilized this nifty <a href="https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet" target="_blank">Markdown Cheatsheet</a> for this sample `README`.

---

## Team

> Or Contributors/People
- You can just grab their GitHub profile image URL
- You should probably resize their picture using `?s=200` at the end of the image URL.

---

## FAQ

- **How do I do *specifically* so and so?**
    - No problem! Just do this.

---

## Support

Reach out to me at one of the following places!

---

## License

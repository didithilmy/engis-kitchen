# Engi's Kitchen Expansion

[![Build Status](https://travis-ci.org/didithilmy/engis-kitchen.svg?branch=master)](https://travis-ci.org/didithilmy/engis-kitchen)

Engi's Kitchen Expansion is a Dinner Dash-like cli-based game written in C to prove concepts like linked list, queue, and stack.

## Features

  - Players can move with commands (GU GD GR GL) or with the cursor buttons
  - Players can place customers on vacant tables, with variable patience
  - Players can take order and place them in order list
  - Players can take a food from the Kitchen and place them onto a stack
  - Players can give food to customer and get money

### Implemented bonus
  - Variable queueing time
  - Load and save game


### ADTs used

Dillinger uses a number of open source projects to work properly:

* Linear list ADT
* Stack ADT
* Queue ADT
* Point ADT
* Matrix ADT
* Array ADT

### Installation

Engi's Kitchen Expansion requires [ncurses](https://www.gnu.org/software/ncurses/) to run.
Ncurses is only supported in Linux and macOS.

Install the dependencies.

```sh
$ sudo apt install gcc make libncurses-dev
```

Clone the project (using git)

```sh
$ git clone https://github.com/didithilmy/engis-kitchen.git
$ cd engis-kitchen
```

Build the source code

```sh
$ make engi
```

### Credits
Engi's Kitchen Expansion is made with ~~force~~ passion by:

| Name | NIM |
| --- | --- |
| Muhammad Aditya Hilmy | 18217025 |
| Zalikha Adiera Gambetta | 18217027 |
| Muhammad Yanza Hattari | 18217043 |
| Claudia Renata Maharani Danardono | 18217048 |

### License
See [LICENSE](LICENSE)
(you can use this source for your own Tubes, but you should include the name of the authors and the license, which will get you enough trouble anyway)

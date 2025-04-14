# Spider Solitaire

This is a C++ implementation of the Spider Solitaire card game.

## File Structure

The project is broken down into the following files:

*   `main.cpp`: Contains the `main` function, which is the entry point of the program.
*   `card.h`: Defines the `Card` class, which represents a playing card.
*   `card.cpp`: Implements the `Card` class.
*   `cardgroup.h`: Defines the `CardGroup` class, which represents a group of cards.
*   `cardgroup.cpp`: Implements the `CardGroup` class.
*   `deck.h`: Defines the `Deck` class, which represents a deck of cards.
*   `deck.cpp`: Implements the `Deck` class.
*   `io.h`: Defines input/output functions.
*   `io.cpp`: Implements input/output functions.
*   `spider.h`: Defines the `Spider` class, which represents the Spider Solitaire game.
*   `spider.cpp`: Implements the `Spider` class.
*   `spiderPile.h`: Defines the `SpiderPile` class, which represents a pile of cards in the Spider Solitaire game.
*   `spiderPile.cpp`: Implements the `SpiderPile` class.

## Build and Run

To build and run the project, you will need a C++ compiler such as g++.

1.  Save all the files in the same directory.
2.  Open a terminal and navigate to the directory where you saved the files.
3.  Compile the project using the following command:

    ```bash
    g++ -o spider main.cpp card.cpp cardgroup.cpp deck.cpp io.cpp spider.cpp spiderPile.cpp
    ```

4.  Run the project using the following command:

    ```bash
    ./spider
    ```

## How to Play

The goal of Spider Solitaire is to build sequences of cards in the same suit, from King to Ace, in the playing area. Once a complete sequence is built, it is automatically removed from the playing area. The game is won when all cards have been removed from the playing area.

1.  The game starts with 54 cards dealt into ten piles.
2.  The bottom card of each pile is face up, and the rest are face down.
3.  You can move a sequence of cards of the same suit from one pile to another, as long as the bottom card of the sequence can be placed on top of the top card of the destination pile.
4.  When you run out of moves, you can deal a new row of cards by selecting 'D'. This will deal one card to each pile. You can only deal a new row if all piles have at least one card.
5.  You can quit the game at any time by selecting 'Q'.

## Sample Game and Moves

Since the game is text-based, here's a hypothetical example of what the game might look like and some sample moves:

**Initial State:**

```
   Columns:
     0   1   2   3   4   5   6   7   8   9
0:  [?][?][?][?][?][?][?][?][?][KH]
1:  [?][?][?][?][?][?][?][?][QH][?]
2:  [?][?][?][?][?][?][?][JH][?][?]
3:  [?][?][?][?][?][?][TH][?][?][?]
4:  [?][?][?][?][?][9H][?][?][?][?]
5:  [?][?][?][?][8H][?][?][?][?][?]
6:  [?][?][?][7H][?][?][?][?][?][?]
7:  [?][?][6H][?][?][?][?][?][?][?]
8:  [?][5H][?][?][?][?][?][?][?][?]
9:  [4H][?][?][?][?][?][?][?][?][?]
```

**Move 1:**

Move the sequence `4H` `5H` `6H` `7H` `8H` `9H` from column 9 to column 3.

Input: `9 4 3`

**State After Move 1:**

```
   Columns:
     0   1   2   3   4   5   6   7   8   9
0:  [?][?][?][?][?][?][?][?][?][?]
1:  [?][?][?][?][?][?][?][?][QH][?]
2:  [?][?][?][?][?][?][TH][?][?][?]
3:  [?][?][?][4H][?][?][?][?][?][?]
4:  [?][?][?][5H][?][?][?][?][?][?]
5:  [?][?][?][6H][?][?][?][?][?][?]
6:  [?][?][?][7H][?][?][?][?][?][?]
7:  [?][?][?][8H][?][?][?][?][?][?]
8:  [?][?][?][9H][?][?][?][?][?][?]
9:  [?][?][?][?][?][?][?][?][?][?]
```

(Note: This is a simplified example. A real game would have more cards and more complex moves.)

Winning the game requires careful planning and strategic moves to uncover hidden cards and build complete sequences. Good luck!


GAME OF YUKON CREATED BY GROUP 38

DESCRIPTION
This is a game of Yukon. It's a russian game that is almost the same as Solitary,
but 10x harder (or at least it feels like it). Don't worry if you lose a lot,
the game has a 1/5 chance of being completely unwinnable - without even telling you!

The goal is to move all the cards in the 7 piles to their corresponding end pile based
on their suit, from the lowest valued card to the highest.


USAGE
To run the YukonGameDtu.exe file, you will need to place the SDL2.dll file
in your /Windows/System32 folder.

When you start the game, you need to try and close the 'Yukon Game' window twice.
You are now in the Start Menu in the console window. Here, you have some options:

P: Play the game.
QQ: Quit the program
Q: Quit the game (if currently in game after pressing P)


HOW TO PLAY THE GAME
When you want to move a card from one pile to another,
you can do so in two different ways:

Move a top card to another top card: ex C1->C7

Move a specific card (non-flipped), and all
other cards on top of it, to another pile: ex C2:5H->C6

Move a top card to its 'goal' pile: ex C5->F1


EXAMPLE GAMEPLAY
Note: the game is case-sensitive
_________
C1->F1
C5:3H->C4
C7->C1
C3->C1
C4:5S->C2
C4->F2
C2:8C->C4
C2->F1
C4:KH->C2
C7:7S->C4
C3:2D->C7
C3->C5
C3->F1
C2:KD->C3
C3:6H->C2
C4->C3
C6->C1
C6:TH->C1
C7->C2
C7->F3
C4:7S->C7
C4:9D->C7
C7->C5
C4->C6
C7->F3
_________


CONTRIBUTING
To edit the code yourself, you need to set up the development environment.
You would need to install SDL2 and MinGW64 and set up the right environmental paths.
If you don't already have the GitHub project set up on your computer,
you can find it here: https://github.com/luucmeldgaard/YukonGameDTU.git

If you are having trouble setting up SDL2,
you can follow this guide: : https://lazyfoo.net/tutorials/SDL/
If you need more information about SDL, go see: http://libsdl.org/

To run the YukonGameDtu.exe file from the cmake-build folder,
you will need to unzip the SDL2.zip file, which can be found in
the root folder, and place the SDL2.dll file
in your /Windows/System32 folder.


COMMON ERRORS:
SDL2.dll is missing: To run the YukonGameDtu.exe file, you will need to place the SDL2.dll file
                     in your /Windows/System32 folder.


CREDITS
With love, from:
HAIDAR, ANTON, LUCAS, EMIL


LICENSE
This program is released under the MIT License (opensource.org/license/mit/)
You are free to use, modify, and distribute this software for any purpose,
as long as the original copyright and license notice is retained.
Please see the LICENSE file for more information.


CONTACT
Please contact 224868@student.dtu.dk
for more information about the project
or if you run into any issues.


           .'\   /`.
         .'.-.`-'.-.`.
    ..._:   .-. .-.   :_...
  .'    '-.(o ) (o ).-'    `.
 :  _    _ _`~(_)~`_ _    _  :
:  /:   ' .-=_   _=-. `   ;\  :
:   :|-.._  '     `  _..-|:   :
 :   `:| |`:-:-.-:-:'| |:'   :
  `.   `.| | | | | | |.'   .'
    `.   `-:_| | |_:-'   .'
 jgs  `-._   ````    _.-'
          ``-------''
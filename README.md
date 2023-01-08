# WormsGame

## Description
Physics logic game based on 'Worms' game for the physics subject.

**Original game:** Worms

**Github Link:** https://github.com/SRRafael8/WormsGame

## Features
 - 1 vs 1 game in turns.
 - The player can move horizontally and climb the vine.
 - The player's turn is marked by the bar on the side. Each turn is 8 seconds.
 - To win you have to defeat the enemy by shooting them, with only one shot available per turn.
 - Player can change the angle and force of the shot.
 - During the other player's turn the player cannot move.
 - If you fall into the water you die automatically.
 - Game loop available.

## Controls
Player 1(Left):
 - D: Move right
 - A: Move left
 - N: Shoot

Player 2 (Right):
 - L: Move right
 - J: Move left
 - M: Shoot

Aim (Both players):
Have to spam the corresponding button
 - Up arrow: augment angle
 - Down arrow: lower angle
 - Right arrow: augment power
 - Left arrow: lower power

## Debug
 - F1: Activate/Deactivate gravity
 - F2: Activate/Deactivate aerodynamicsb
 - F3: Activate/Deactivate drag
 - F4: Activate/Deactivate bouyancy
 - F6: Show collisions
 - F7: Hide collisions
 - F8, F9, F10: Game runs at 30, 60 or 90 fps respectively

## Developers
 - Iván Bermúdez Sagra
 - Rafael Esquius Pérez
 - Pau Garriga Brotons
 - Joel Romero Botella

## Solved Bugs
 - Bullets trespassing ground barriers --> solved
 - Player taking damage when shooting -->solved
 - Bullets damaging enemy more than one time per turn -->solved
 - Players shooting the same bullet at the same time --> solved

## License
This project is licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

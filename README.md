# tanX
A multiplayer online tank game using SDL and UDP

## Library
+ Pthread (for c++14 multithread)
+ SDL 1.2
+ SDL_mixer 1.2

## ToDo
+ add game props such as weapons and vehicles
+ display game status in the sidebar
+ add more kinds of terrain grids
+ add some sound effects (wait for someone to do)

## Futue Plan
1. AI interface
2. Reliable transmission

## How to Play
Build this project to get server and client.

```
$ cd src/
$ make
```

Start the server (only one player needs to do this).

`$ ./lnX number_of_players`

Start the client.

`$ ./tanX server_ip`

Use arrow keys to move, spacebar to shoot.

You can edit the map in map/demo.map.

##Screenshot
![screenshot](screenshot.png)

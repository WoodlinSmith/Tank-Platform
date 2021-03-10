# How to Run the Tournament
Steps for running the tournament:

1) Create a .txt file with the list of tanks. The tank list should be formatted
where the classname of each tank is on its own line with no extra whitespace or newlines.

2) Run the '1v1' command in the  `tournament_1v1/` directory. This will generate
a 1v1 config for every possible combination of tanks.

```
./1v1.helper <tank_list> map_list_2p
```

3) Run `run_1v1_game.sh' in the root directory. This will generate a text file
named 'outcomes' that holds the data from each match including who played, and the winner.

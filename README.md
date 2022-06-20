# CLI-Timer
Countdown timer in the terminal. The timer class was *borrowed* from [Birb2D](https://github.com/Toasterbirb/Birb2D)

## Usage
Without any arguments timer will close immediately. You can give it the target time with 3 different arguments: h, m and s
For example:
```
./timer -h 1 -m 5 -s 25
```
would time for 1 hour, 5 minutes and 25 seconds

The remaining time is shown in digital format
```
toasterbirb@tux ~/git/cli-timer $ ./timer -h 1 -m 5 -s 25
01:05:18
```

## Dependencies
- libnotify [optional]

## Compiling
Simply run `make` or `make no-notify` if you don't want desktop notifications when the time is up.

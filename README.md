<p align="center">
    <picture>
        <source media="(prefers-color-scheme: dark)" srcset="./images/dark.svg" | width=300>
        <source media="(prefers-color-scheme: light)" srcset="./images/light.svg" | width=300>
        <img alt="sammich" src="./images/dark.svg">
    </picture>
</p>

## PR and what now?
PR&J is the second name of this project after realizing two things:
- I'd like to be able to put this on a resume.
- Realizing the main features are as follows:
    - Probing
    - Runout detection
    - & Jam detection
> This board also is sandwiched between the hotend and extruder, thus a PR&J.

## How does a load cell do all that?
The way this design is set to work is there will be a strain gauge between the extruder and hotend with a set of resistors on it.
When the board experiences even the slightest bit of strain, the value of these resistors changes slightly.
This change is amplified by the tried and true HX717 24 bit amplifier, allowing for over 16 million unique values.
This signal is then read by an on board ATTiny202, and then sent to a klipper MCU via I<sub>2</sub>C.

Though the first idea that comes to mind with load cells is probing (which is still the main feature of this project), the ability to detect this strain can also be used to interpret forces between the hotend and extruder in both positive and negative directions.
We're still workshopping ideas that could come from this one feature, but some we would like to consider are:
- Runout detection
- Jam detection
- Detecting skipped steps
- One-click pressure advance tuning
- One-click max flow rate calculation

Some "theoreticals" that will need extensive testing but may be possible:
- Spaghetti detection
- Crash detection
- Flow rate change compensation

## Sign me up!
Actually I'd love to!
We're in the process of establishing a small beta test group for main boards and two types of strain gauges. The initial testing phase likely won't involve much printing, focusing instead on gathering data to study the behavior of these strain gauges, as well as test consistency.
As we develop more, the strain gauges we currently have may be adapted to some toolheads, so it's likely that new hardware won't even have to be sent for real world testing.
We're also looking for people that may have experience with any of the following for helping with development of the project itself.
- Skilled programmers, especially those familiar with klipper
- Electronics engineers
- CAD experts
If you're interested in contributing, ongoing discussions are hosted on the [Armchair Engineering discord server](https://discord.gg/armchairengineeringsux) in [this specific channel](https://discord.com/channels/1029426383614648421/1141480604844703745).

## What now?
As of the repository's creation, parts are on the way, and the board ordering process is nearly finalized. The initial batch of test boards will comprise approximately 10 main boards and 20 strain gauges (10 of each design).
Regular updates will be posted in the Armchair engineering project thread. Feel free to reach out to me there or through [my discord](https://discord.com/users/96435324275658752) if you have any questions.

Here's what we've got so far :)

<picture>
  <source srcset="./images/boards.png">
  <img alt="sammich" src="./images/boards.png">
</picture>

## Helpers
- Electronics
    - fisheiyy
    - [tanaes](https://github.com/tanaes)
    - [calithameridi](http://github.com/calithameridi/)
- Hardware
    - [tanaes](https://github.com/tanaes)
    - [bwnance](https://github.com/bwnance)
- Software
    - [detunedcalliope](https://github.com/detunedcalliope)
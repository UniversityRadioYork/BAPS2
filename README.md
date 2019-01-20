# BAPS2

This is BAPS (Broacast And Presenting Suite), URY's long-lived playout system.

## Features
  - 3 Audio channels of (simultaneous) audio playback - backend mostly supports unlimited
  - Single server (BAPS Server Service), multiple client (BAPS Presenter) architecture
  - Loading of preplanned shows, beds, jingles (currently using Show Planner in MyRadio)
  - Loading of music library tracks (from MyRadio database)
  - Sidebar with 3 drag & drop audio resource boxes with customizable title and filepath (supports network shares)
  - Automated tracklisting
  - Remote playback trigger support (Arduino sketch provided)
  - Auto advance, repeat and play on load options
  - "Audio Wall" for touchscreen / mouse trigger soundboard (per channel)
  - Basic user management (regular and admin roles)
  - Pretty reliable (as long as you don't plug in USB audio devices or update Windows)
  - Many more random hidden/removed features still hanging around.

## Requirements
  - Windows 7+ (Windows 10 is recommended for recent versions)
  - (At least the database tables from) MyRadio
  - 3 separate stereo sound outputs (shown in Windows Sound Devices)
  

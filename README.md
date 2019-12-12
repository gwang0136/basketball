# Basketball Game

A basketball game using C++ in OpenFrameworks.

![game-screenshot](https://user-images.githubusercontent.com/35745514/70671909-4d179880-1c43-11ea-8d0c-071c16018e37.png)

## Installation & Setup

How to install and run:

1. Download OpenFrameworks: [https://openframeworks.cc](https://openframeworks.cc)

2. Download this repository within the `[openframeworks directory]/apps/myApps/`

3. Download [ofxBox2D](https://github.com/vanderlin/ofxBox2d) and [ofxProgressBar](https://github.com/atduskgreg/ofxProgressBar) into `[openframeworks directory]/addons/`

4. Using the [Project Generator](https://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/), navigate to the repository, and click on "Update"

## Usage

### Constant Settings

Change the number of consecutive shots needed before leveling up in [globals.h](https://github.com/CS126FA19/fantastic-finale-gwang0136/blob/master/Final%20Project/src/globals.h).

- **to_level_up**: Default set to 3 shots to be made in a row per level.

### Game Instructions

1. Pressing and holding the space bar will charge up the power used on each shot. The power is displayed in the progress bar.

2. Releasing the space bar will release the shot.

3. Making a certain amount of consecutive shots in a row will move you on to the next level.

4. Missing a shot will move you back to level one and reset your score.

## Development

### Dependencies

[ofxBox2D](https://github.com/vanderlin/ofxBox2d)

[ofxProgressBar](https://github.com/atduskgreg/ofxProgressBar)

### Code Style

All code follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

# Matrix Project.


### Bomberman (OLD VERSION) !

#### Documentation - [short video (2 min)](https://youtu.be/wZcfJnbsGgI)

#### Menu presentation - [short video (3 min)](https://youtu.be/C2Ci4uytHbY)

#### Bomb deployment (pre-alpha) - [short video (1 min)](https://youtu.be/DVPk5EeuUPI)

The project had reached the point where it was **playable** in "player vs player" mode, with walking animations...
However, it lacked in-game sound and the item functionality (non-essential, but fun).

I was planning to record the gameplay after fixing these ishues, but I haven't found the time. Later, after the pandemic striked and I returned to my home city, I wanted to finish the project, but a malfunction caused during transportation appeared. I realised it was possible, but difficult to fix the problem and I decided to start over and build the project in a better, more modular way, such that any component could be easily replaced should a malfunction appear again. Thus I could not take the final footage and I did not finish the documentation for this version. :(


## Bomberman (THE CURRENT VERSION) - SPOILER: IT'S AWESOME !!!


### PCB Layout - [pdf (2 pages)](https://github.com/24Arys11/Robotica/blob/master/The%20Matrix%20Project/Current%20Version/docs/PCBs.pdf)

### Menu - [pdf (1 page)](https://github.com/24Arys11/Robotica/blob/master/The%20Matrix%20Project/Current%20Version/docs/Menu.pdf)

### Levels - [pdf (1 page)](https://github.com/24Arys11/Robotica/blob/master/The%20Matrix%20Project/Current%20Version/docs/levels.pdf)

### Character animations - [pdf (1 page)](https://github.com/24Arys11/Robotica/blob/master/The%20Matrix%20Project/Current%20Version/docs/animations.pdf)

### Construction insights - [short video (2 min)](https://youtu.be/aUcalQiRNsg)

### Wellcome screen - [short video (29 sec)](https://youtu.be/PIbAACZ1w9Q)

### Menu presentation - [short video (5 min)](https://youtu.be/3MC6CFNlwqA)

### Credits animation - [short video (39 sec)](https://youtu.be/r5yEWpp2Rvw)

### Gameplay 1 - [short video (3 min)](https://youtu.be/_2kjGHCBAJk)

### Gameplay 2 - [short video (4 min)](https://youtu.be/AhGbZA6XfVw)

### Neat things:
* Sound system could play up to 30 songs (sound effects, mellodies, ...) simultaneously ! Only the sound with the highest priority (or the most recent if priorities are equal) will be heard, however, a background song will continue after the top song finishes. Thus, songs can interrupt each other dynamically.
* Matrix Manager renders every position (set of 4 leds) individually, each having it's own refresh rate. Thus the game displays very efficiently and is able to run smoothly.

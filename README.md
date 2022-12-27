# tamagotchi_uni

University project to create a replica of Tamagotchi on the Landtiger.

## Architecture

The program starts in the `sample.c`, all the initializations are done there. There are two main files: controller.c and tamagotchi, both contains the data structure that represents the game logic. On the init of timer0, there are 3 mr that are inialized, every mr increases when the it launches an interrupt:
- mr0: exception every 8us, handels the `CON_on_click_listener()` callback;
- mr1: exception every 1s, updates the logic with the `CON_update` callback;
- mr2: exception every 1/30s, render refresh rate of the screen handled by the `CON_render_data()`;
Because the mr operates by increasing their value the simulator must not implement time scaling on TIM0, if it's enabled the program would not function correctly.

The RIT handles the logic for the managment of the joystick, it operates in polling mode, checking periodically the value of the FIOPIN. When a button is checked the action associtated with the direction is started. Every action is guraded so it cannot be executed multiple times in a row, avoiding the problem of rescheduling the interrupt of the RIT.

## Rendering

The two main classes are initialized at beginning of the program setting up the realative states and the scaling of the sprites, the first render of the screen draws the boxes and the buttons with the tamagotchi (that thing I've come up with), the next render only draws the the things that change over time: the tamagotchi, the food, the batteries, the change of the button. Every time that one of those elements are drawn they need to be canceled from the screen, avoiding multiple objects drawn on the screen, every second the sprite to draw on the screen is updated throgh the `update()` funciotn. The contrller act as a ViewModel for the tamagotchi (sort of MVVM architecture), if fact he decides how to draw the tamagotchi and how to modify it's properties. The main functions are `update()` and `render()`.
- `update()`: updates the properties of the elements that need an update every 1 sec;
- `render()`: renders the elements on 30 FPS, and moves the character if needed;

## Chasing

When a button is pressed the food appers on the screen. On every render the tamagotchi moves towords the food by calculating the current offset that it needs to take by using vectors, and not other action is possible, if the tamagotchi reaches the food it starts eating it, the animation is the sprite being flipped for 1 second (I'did not want to create another sprite for the eating animation), at the end of it the tamagotchi returns back to the normal position and it is possible to eat again.

## Death

When boath the bars reached 0 the tamagotchi dies and leaves the screen an no other action is possible, at the end of the animation

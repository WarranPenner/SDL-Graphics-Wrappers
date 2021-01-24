# SDL Graphics Wrappers
*Provides basic wrapper classes for windows and 2D rendering processes with SDL2/C++. Includes TTF text and viewport functionality.
Currently designed for BMP textures only.*
<br />
<br />
### Windows and Viewports
* These wrapper classes center around a `Window` class, which wraps the functionality for an `SDL_Window` and its `SDL_Renderer`.
* A `Window` object can be given a pointer to a `Viewport` object. The `Viewport` class holds an `SDL_Rect` (the viewport itself),
  and functions for getting and setting its variables. A viewport can be initialized/moved in one of two ways:
  * It can be manually placed and moved with the `init` and `move` functions.
  * It can be set to follow a "target" object through a couple of pointers for coordinates (`targetX_` and `targetY_`). These are
    set through the `initWithTarget` and/or `setToFollow` functions. The viewport will return a position based on these target 
    coordinates when `getRect` is called.
* On-screen objects can be scaled and resized, either for variable window sizes or full-screen mode, by changing `nativeW_` and 
  `nativeH_`.
* It is absolutely possible to use more than one window. With a bit more work, it would be possible to use multiple viewports,
  dividing up a window.
    
### Rendering Objects to a Window
* The `Texture` class wraps a BMP `SDL_Texture` and all of its basic functionality. It's currently designed to use an `SDL_Color`
  variable called `COLOR_KEY_` as the transparency color for an image. The `paint` function is called every frame - in which the
  SDL_Texture is sent through a pointer to a `Window` object to renderered.
* The `Text` class is derived from the `Texture` class. Its text can be set through the `init` or `write` functions. It replaces
  its `SDL_Texture` when its text, font, or color values are changed.
* After initializing `Texture` and/or `Text` objects, their `paint` functions must be called from within an application's loop
  every frame. I have put two demonstration objects (`picture_` and `message_`) in the `run` function of a class called `SDLApp`.
  *Remember to always make a similar loop in your app, otherwise the window will immediately close.*
* Functions for drawing primitive shapes have been included in the `Window` class - however, *they are not designed to work with
  viewport scrolling*. These were included for very basic applications and any testing purposes a developer might have.
  
### Quick Set-Up
1.  In your own application, initialize SDL and TTF as I have in the `SDLApp` constructor.
1.  Create a `Window` object and call its `init` functions.
1.  Create any `Texture` or `Text` objects that you want to display, then call their init functions.
1.  In your application's main loop, add another `SDL_PollEvent` `while` loop, terminating the loop only for specific conditions
    like an `SDL_QUIT` event. Also, within this loop, call the `handleEvent` function for your window.
1.  Back in your application's main loop, call the `paint`/`write` functions for any textures of text that you want displayed.
1.  Finally, at the end of the main loop, call the `render` function for your window.

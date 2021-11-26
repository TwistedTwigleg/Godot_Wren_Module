# Godot Wren Module

This module adds a new node, called WrenManager, that allows for executing [Wren](https://wren.io/) code in Godot during runtime! [Wren](https://wren.io/) is a cool lightweight programming language that can be easily added to C++ projects to add real-time scripting. The idea behind the module was not to add another scripting language for editor support like GDScript or C#, but instead to add support for a scripting language that can be used while the game is running in Godot itself.

**Please note that this module is just a proof-of-concept!** It does not add full Wren support to Godot! It was made while evaluating Wren for a potential Godot-powered project. While I decided not to use Wren for the project, I wanted to release this module as a point of reference for anyone looking to add Wren support to their projects.

## How to use

Download the Wren source code and place the `src` folder in the `Modules/wren` folder of this repository. Then copy the `Modules/wren` folder from this repository from and place it in the `modules` folder of the Godot engine source. Then you can compile Godot like normal to use the module!

_______

Again, this is just a proof of concept and not a fully-featured integration, but hopefully it will provide useful for anyone looking to add [Wren](https://wren.io/) support to Godot.

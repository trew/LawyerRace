Lawyer Race
-----------
Story:
Once mr O needed a lawyer for some reason, and so he hired one.
When the case was lost and all mr O:s money was gone with the
wind, the lawyer office still wanted its fee, and they set after
mr O, who had fled to the mountains, looking for dollars. Rocks
are falling all around him while mr O is struggling to escape
wild lawyers and to collect money enough to set him free.
Play the game to find out if mr O will make it!!


Compilation instructions
------------------------

###Linux:

- Required runtime libraries
 - SDL
 - SDL_image
 - SDL_ttf
 - Boost

On debian distributions use:

    sudo apt-get install sdl sdl_image sdl_ttf boost

On arch:

    sudo pacman -S sdl sdl_image sdl_ttf boost

On fedora:

    sudo yum install SDL SDL-devel SDL_image SDL_image-devel SDL_ttf SDL_ttf-devel
    sudo yum install boost boost-devel


  1. Run this script to create the configuration script

    $ ./autogen.sh

  2. To compile:

    $ ./configure && make

  3. To install:

    $ make install

  4. To run:

    $ ./lwrace

###Windows:

####Visual Studio 2010:

  1. Open up the solution ( /vs2010/vs2010.sln )
  2. Compile 
  3. Move all .dll-files from /lib/win32/SDL to /vs2010/Debug/
  4. Run the game from /vs2010/Debug/
  5. Create a link and append "-p ../.." in the end to specify path where Lawyer Race should run from.


####Windows / Mingw 
  NOT TESTED

###Mac OS X:
  Tested, and it worked, but I don't have instructions.

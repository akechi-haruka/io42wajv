io42wajv
generic wajvio I/O replacement DLL for using a physical IO4 board for games that expect WAJV input
2024 Haruka
Licensed under the GPLv3.

Specialized for Synchronica, but can be used for any game.

--- Usage ---

* Place io42wajv.dll, io42wajv.ini and hidapi.dll in your game directory.
* Rename io42wajv.dll to wajvio.dll (and make a backup of the original)
* Make sure [wajv] is set to enable=0 in segatools.ini.
* Synchronica: Make sure [side] is set correctly in io42wajv.ini.

See io42io3.example_sync.ini for an example config (FGO io4 to Synchronica WAJV)

--- Compiling ---

have msys2 installed at the default location and run compile.bat

or use CLion

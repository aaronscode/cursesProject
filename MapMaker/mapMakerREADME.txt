=========================================================
= Readme for SWMapMaker (SpankWagonMapMaker)            =
=========================================================

=========================================================
= The Short Reference                                   =
=========================================================

1. Run from command line with form
   
   > ./SWMapMaker NameOfFile.txt
 
   Will create or load specified file

2. If creating a file, provide a description, then procede to ignore
   instructions.

3. Use arrow keys to move cursor. Use <F1> to save, <F2> to cycle edit mode,
   <F3> to cycle movement mode.

4. Edit Modes: <F2> cycles
   - 1 - Character insertion mode. Press alpha-numeric-symbolic keys on
         keyboard to insert character into cell cursor is on. Backspace will
	 delelete the contents of the cell before the cursor.
   - 2 - Color selection mode. You have 64 color pairs to chose from. 8
         background colors, 8 foreground colors. Use 'c' and 'z' to increment
	 or decrement the currently selected color pair by 1. Use 'a' and 'd'
	 to increment or decrement by 8. (this effectively keeps the same
	 foreground color, while advancing to the next background color). Use
	 'x' to color a cell. Note the that currently selected color pair will
	 be used when entereing characters in insertion mode, as well.
   - 3 - Property edit mode. Edit the properties of an individual cell. Use 0
         through 9 to change the value of this cell.
	 0 - a normal cell, can be walked through
	 1 - a solid cell, cannot be walked through
	 2 - a npc, cannot be walked through, can be spoken to
	 3 - random encounters can occur on this cell. Think tall grass from
	     Pokemon.
	 9 - a warp cell, acts as a connection to another cell, can be on the
	     same map, can be on a different map. The specifics will be
	     specified later, just mark any cell that will serve as a doorway,
	     cave entrance, portal, or connection between maps with this
	     number

5. Movement Modes: <F3> cycles
   These control how the cursor automaticall advances upon entering a 
   character, coloring a cell, or editing cell properties. Designed to make 
   changing a bunch of characters in a row or column relatively simple. Note
   that pressing backspace will apply the deletion in whatever direction is
   opposite the current movement mode. I.E., cursor will move left instead of
   right, or up instead of down.

   - 1 - Cursor will move to the right automatically upon character insertion, 
         coloring, or property edits.
   - 2 - Cursor will move down automatically.
   - 3 - Cursor does not move automatically.

=====================================================
= The Long Reference (Work in progress)             =
=====================================================

1. To start the map maker, call it from the command line. The map maker takes
   a single argument, the name of a file to open. Usage looks like
   
   > ./SWMapMaker NameOfFile.txt

   The map maker will check if the file exists. If it does, it will load the 
   map data. If the file doesn't exist, as will be the case when you first
   make the map, then it will ask for a description of the map, and create a
   file with the name given as an argument when the map is saved for the first
   time. NOTE: Please make sure your description is brief and no longer than
   one line. If there is no file specified to open, the map maker will ask you 
   for a description, and by defualt save the map as the file "MapUnamed.txt" 
   Note that in this case (meaning, when no filename is specified), the map 
   maker will not attempt to load any previous maps that had been saved in 
   "MapUnamed.txt", and will simply overwrite any map previously saved in that
   file. You have been warned.

2. After the file has been loaded or you've provided a description, you will
   be shown a brief summary of instructions for the map maker, which should be
   unnecessary assuming you've already read this file. Press any key to
   advance to the next page of instructions. On the final page, a key press
   will take you to the map editor proper. 

3. Once you get into the editor proper, you should notice several things.
   First, at the top, is the status bar. This displays several important
   pieces of information. First, is your edit mode, the number next to the EM.
   By default it should be one. More will be said about edit modes later.
   Next, is your movement mode, next to the MM. This should also be one, and
   will be explained in more detail later. In the next cell is your currently
   selected color pair (CP), which is by default zero. In the same cell should
   be an '@' which will change color depending on your currently selected
   color pair, to indicate which color you are currently using. Finally, the
   description of the map (or however much of it will fit in the remaining
   space), should be displayed to the right of the color pair indicator.

4. Next, take note of the little blinking bar near the center of your screen.
   This is the cursor, or the point at which character insertion will occur.
   Pressing most of the alpha-numeric keys on the keyboard, and some symbols
   too (e.g. '!', '@', '~', ...) will cause them to be entered into the map at
   the position of the cursor. Note that the cursor will automacally advance
   to the left upon character insertion. This is to make it easer to enter
   rows of characters. More on that later. The arrow keys can also be used to
   change the position of the cursor, although when the map is initially
   created, it is difficult to see this since there is nothing for the cursor
   to been seen moving relative too. Speaking of the map, it is comprised of a
   160 X 160 grid of characters. The cursor starts automatically in the upper
   left corner of this grid at (0,0).

5. Pressing <F1> will save the map to a text file. Pressing <F2> will cycle
   through the 3 edit modes. Pressing <F3> will cycle through the 3 movement
   modes.

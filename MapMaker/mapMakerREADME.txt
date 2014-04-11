=========================================================
= Readme for SWMapMaker (SpankWagonMapMaker)            =
=========================================================

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

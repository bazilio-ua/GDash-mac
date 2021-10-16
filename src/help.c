/*
 * Copyright (c) 2007, 2008, 2009, Czirkos Zoltan <cirix@fw.hu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include "cave.h"
#include "cavedb.h"
#include "config.h"
#include "gtkui.h"
#include "gtkgfx.h"
#include "caveobject.h"

struct helpdata {
    char *stock_id;
    char *heading;
    GdElement element;
    char *description;
};

/********
 *
 * HELP FOR GAME
 * 
 */

static const struct helpdata gamehelp[] = {
        {NULL, NULL, O_NONE, N_("The primary objective of this game is to collect required number of diamonds in defined time and exit the cave. You control your player's movement to solve given cave.")},
        {NULL, NULL, O_NONE, NULL},
        {GTK_STOCK_CDROM, N_("Caves"), O_NONE,
             N_("The game comes with many built-in and pre-installed cave sets, and you can also make "
                "up your own levels. Just use the options in the File menu. You can load caves stored in the BDCFF format, and import "
                "from other older file formats, like the No One's Final Boulder, the Construction Kit file format, "
                "No One's Delight Boulder, an Atari game format and many more.")},
        {NULL, NULL, O_NONE, NULL},

        {GTK_STOCK_MEDIA_PLAY, N_("Playing the game"), O_NONE,
            N_("The main idea of this game is very simple. You have to guide your player through the mazes of dirt and stones, to collect "
            "diamonds within a given time limit. Make sure not to let stones fall on your head or enemies touch you! After you collect "
            "the correct amount of diamonds, the screen will flash quickly and a secret door is revealed for you to advance to the next level. "
            "As the game progresses, levels usually become more intricate and difficult.")},

        {NULL, NULL, O_PLAYER, N_("This is the player. He can move through space and dirt. He can pick up diamonds and push stones, but he should avoid flies.")},
        {NULL, NULL, O_SPACE, N_("Stones and diamonds fall down in space, creatures can freely move here.")},
        {NULL, NULL, O_DIRT, N_("You can move through dirt leaving empty space behind. Amoeba eats it.")},
        {NULL, NULL, O_DIRT2, N_("This is also dirt, but has a different color. In any other sense, it is identical to the above one.")},
        {NULL, N_("Dirt ball and loose dirt"), O_DIRT_BALL, N_("A rolling ball and a falling piece of dirt. You cannot push them, but you can dig them away. Sometimes they help you to solve puzzles.")},
        {NULL, NULL, O_DIAMOND, N_("The main object of the game is to collect required number of diamonds.")},
        {NULL, NULL, O_STONE, N_("Stones can be pushed by the player, and he can drop them on flies to make an explosion.")},
        {NULL, NULL, O_NUT, N_("These nuts contain diamonds. If you crack them with a stone, they will be opened.")},
        {NULL, NULL, O_FLYING_DIAMOND, N_("Exactly like a diamond, but instead of falling down, it flies upwards, as high as it can.")},
        {NULL, NULL, O_FLYING_STONE, N_("The flying variant of a stone. Note that this one can also crush enemies as well as the player!")},
        {NULL, NULL, O_MEGA_STONE, N_("Like ordinary stones, but these are so heavy, that you cannot push them.")},
        {NULL, NULL, O_BRICK, N_("The wall can't be moved but an explosion destroys it. You can't pass through the wall - instead try to blow it up.")},
        {NULL, NULL, O_STEEL, N_("This is rock stable wall. It's impossible to move or blow it up.")},
        {NULL, N_("Sloped steel wall"), O_STEEL_SLOPED_UP_RIGHT, N_("Acts like an ordinary steel wall, but it is sloped: stones and diamonds will roll down on it in some direction. Brick walls and dirt also have sloped variations.")},
        {NULL, NULL, O_PRE_OUTBOX, N_("After collecting the required number of diamonds, look for a flashing out box to exit the cave. "
"Closed out box looks like steel wall, but beware of explosions near the out box: "
"you could accidentally destroy an exit. This prevents you from successfully finishing the cave.")},
        {NULL, NULL, O_PRE_INVIS_OUTBOX, N_("This is also an exit, but it remains non-flashing and thus is difficult to find.")},
        {NULL, N_("Firefly"), O_FIREFLY_1, N_("Fireflies move through the space. They can fly in the entire cave. Fireflies blow up when hit by falling stone or diamond. Amoeba is also deadly for them. They explode into space, producing 3x3 square of empty space. Fireflies are left spinning - they prefer turning left, usually counter clockwise.")},
        {NULL, N_("Alternative firefly"), O_ALT_FIREFLY_1, N_("Just like a normal firefly, but it is right spinning.")},
        {NULL, N_("Dragonfly"), O_DRAGONFLY_1, N_("These creatures also guard the diamonds you would like to collect. But they move very differently. They like to run straight ahead, and only change direction if they bump into something. Like normal guards, you must not touch them. But you can easily crush them with stones.")},
        {NULL, N_("Butterfly"), O_BUTTER_1, N_("Butterflies are similar to guards. In contrast to guards they explode into diamonds, producing 3x3 square of diamonds. Butterflies are right spinning, they usually fly clockwise.")},
        {NULL, N_("Alternative butterfly"), O_ALT_BUTTER_1, N_("Just like a normal butterfly, but it is left spinning.")},
        {NULL, N_("Stonefly"), O_STONEFLY_1, N_("This flying moth behaves just like a butterfly, except that it explodes into stones instead of diamonds.")},
        {NULL, N_("Cow"), O_COW_1, N_("This creature wanders around the cave like a guard, but you can touch it. If it is enclosed, it turns into a skeleton.")},
        {NULL, NULL, O_GHOST, N_("This is ghost which wanders aimlessly. If it touches you, it will explode in an x-shape to many different elements.")},
        {NULL, N_("Biter"), O_BITER_1, N_ ("Biters will eat all the dirt they can reach. They move in a predictable way. They also can eat diamonds, so better don't let them be taken away. They will move through stones throwing them behind if there is no space for turning. That way, you can get rid of stones blocking your way.")},
        {NULL, NULL, O_CHASING_STONE, N_("A chasing stone looks like an ordinary stone, it can even pass slime. It is lightweight, you can push it at once, as long as it is sleeping. Once it begins to fall, it wakes up and begins chasing you. You can also push awakened stones, if you have eaten the sweet.")},
        {NULL, NULL, O_AMOEBA, N_("Amoeba grows randomly through space and dirt. When it is closed, stops growing and transforms into diamonds. When it is grown too big, it suddenly transforms into stones. At the beginning it can grow slowly, but after some time it starts growing very rapidly.")},
        {NULL, NULL, O_AMOEBA_2, N_("Another amoeba, which behaves exactly like the above one. But it lives its own life. Sometimes, when they collide, they produce an explosion.")},
        {NULL, NULL, O_SLIME, N_("Slime is permeable. It means that stones and diamonds laying on the slime can randomly pass on.")},
        {NULL, NULL, O_ACID, N_("Acid eats dirt. Sometimes it spreads in all four directions, leaving a small explosion behind. If there is no dirt to swallow, it just disappears.")},
        {NULL, NULL, O_WATER, N_("Water, which floods all empty space slowly.")},
        {NULL, NULL, O_MAGIC_WALL, N_("This very special wall converts stones into diamonds and vice versa. Note that a magic wall can only be activated for some limited time. It can also turn mega stones into nitro packs, nitro packs into mega stones. Even flying diamonds and stones pass them to be converted to each other - but these two do that from bottom to up, of course.")},
        {NULL, NULL, O_EXPANDING_WALL, N_("Expanding wall expands in horizontal or vertical (or both) direction, if there is an empty space to fill up. You should be very careful not to be catched by the expanding wall.")},
        {NULL, NULL, O_EXPANDING_STEEL_WALL, N_("Expanding wall, but made of steel. You cannot even blow it up!")},
        {NULL, NULL, O_FALLING_WALL, N_("Whenever there is a falling wall above the player merely separated by empty space, it starts falling. It does so at any distance. If it hits the player, it explodes. If hit on anything else, it just stops.")},
        {NULL, NULL, O_BOMB, N_("You can pick up this bomb like a diamond. To use it, press control and a direction... and then quickly run away! You can hold only one bomb at a time.")},
        {NULL, NULL, O_SWEET, N_("Eat this sweet and you will become strong. You will be able to push stones at once. You will "
"also be able to push chasing stones.")},
        {NULL, NULL, O_TRAPPED_DIAMOND, N_("This is an indestructible door with a diamond.")},
        {NULL, NULL, O_DIAMOND_KEY, N_("If you get this key, all doors will convert into diamonds you can collect.")},
        {NULL, N_("Keys"), O_KEY_1, N_("There are three types of keys, which open three different colored doors. You can collect more from these; and for every door, always one key is used.")},
        {NULL, N_("Doors"), O_DOOR_1, N_("This is a door which can only be opened by the key of the same color.")},
        {NULL, NULL, O_BOX, N_("Sometimes you have to block a passage, for example to protect a voodoo. This is when a box like this comes handy. You can push it in every direction using the Ctrl key.")},
        {NULL, NULL, O_PNEUMATIC_HAMMER, N_("Sometimes diamonds or keys are buried in brick walls. You can use a pneumatic hammer to break these walls, or simple brick walls which contain nothing. Stand on something, and press fire and left or right to use the hammer on a wall which is near the player, next to the element you stand on.")},
        {NULL, NULL, O_REPLICATOR, N_("This machine replicates the element which is on the top of it. At regular intervals, a new element drops out underneath; if there is space to do this. The rate of materializing the new elements can be different in every cave.")},
        {NULL, N_("Conveyor belt"), O_CONVEYOR_LEFT, N_("The indestructible and immobile conveyor belt carries free-moving elements. Its direction can be changed or its power can be turned completely off with a switch. It only carries the elements which are resting on it (ie. it will not move a piece of dirt or a firefly.) Flying stones and diamonds under it will also be carried.")},
        {NULL, NULL, O_LAVA, N_("Heavy elemenets sink into the lava and disappear without any trace left. Creatures can also step into the lava.")},
        {NULL, NULL, O_CLOCK, N_("Collect this to get extra time.")},
        {NULL, NULL, O_BLADDER, N_("Bladders can be pushed around easily. They slowly climb up; if they touch a voodoo, they convert into clocks. They can also pass slime.")},
        {NULL, NULL, O_BLADDER_SPENDER, N_("If there is space above it, the bladder spender turns to a bladder.")},
        {NULL, NULL, O_VOODOO, N_("This is your player's look-alike. You must protect him against flies. If a voodoo dies by one of them, your player dies immediately too. This doll can have different properties: sometimes it can collect diamonds for you. Sometimes it must be also protected from falling stones, as if hit by a stone, it turns into a gravestone surrounded by steel walls. Also, it may or may not turn into a gravestone by nearby explosions.")},
        {NULL, NULL, O_TELEPORTER, N_("The teleporter will move you from one place to another, if you step into it. The destination teleporter depends on which direction you step the current one into.")},
        {NULL, NULL, O_POT, N_("Stir the pot, and then you will be able to use the gravitation switch. While you are stirring the pot, there is no gravitation at all. Press fire after using the pot.")},
        {NULL, NULL, O_SKELETON, N_("Sometimes you have to collect skeletons before you can use the pot. In some other caves, they must be collected like diamonds to open the exit.")},
        {NULL, NULL, O_GRAVITY_SWITCH, N_("When this switch is active, you can use it to change the gravitation. The direction from which you use it will determine the direction the gravitation will change to.")},
        {NULL, NULL, O_EXPANDING_WALL_SWITCH, N_("With this switch you can controll the direction of the expanding wall.")},
        {NULL, NULL, O_CREATURE_SWITCH, N_("With this you can change the direction of creatures, like guards and butterflies. Sometimes it works automatically.")},
        {NULL, NULL, O_BITER_SWITCH, N_("This switch controls the speed of biters.")},
        {NULL, NULL, O_REPLICATOR_SWITCH, N_("This turns the replicator on or off.")},
        {NULL, NULL, O_CONVEYOR_DIR_SWITCH, N_("This switch can be used to reverse the direction of conveyor belts.")},
        {NULL, NULL, O_CONVEYOR_SWITCH, N_("The conveyor belts also have a switch which can completely stop their action.")},
        {NULL, N_("Strange elements"), O_DIRT_GLUED, N_("Some caves contain strange elements, for example, diamonds which cannot be collected, a player that cannot move... Don't be surprised!")},

        {GTK_STOCK_DIALOG_INFO, N_("Playing hints"), O_NONE, N_("Obviously, holding fire and pushing a direction causes you to 'touch' an adjacent square without moving into it, collecting diamonds or removing dirt, but a move which is very useful is to push a stone in this way. It's a good way of making sure you don't 'overpush' the stone and later on you will have to use this.")},
        {NULL, NULL, O_NONE, N_("Stones do not roll off of the side of magic walls. In some caves it is shown where these walls are by placing a stone to show you that it's magic.")},
        {NULL, NULL, O_NONE, N_("Expanding walls are always horizontally expanding on both sides. In some caves it is shown which parts of the wall are expanding by forcing you to pass it on the other side. You will see the passage close in behind you and this eliminates some guessword in the next puzzle.")},
        {NULL, NULL, O_NONE, N_("The screen starts scrolling at the edge of the screen. This means it's a bad idea to run in places where enemies are likely to be, since you won't have time to react. Either move very carefully in these situations, keep track of where the enemies roughly are in the cave, or take a different route away from danger - for example in empty space (where enemies are less likely to travel) or through undug mud. Never rush unless you're sure you can or you need to.")},
        {NULL, NULL, O_NONE, N_("Enemies like to have dirt to move around on. Clearing lots of dirt can create safe patches for you. This technique can be used on levels where you let several fireflies loose and it's hard to kill them. Beware though - certain formations of enemies can hover in 'mid air' and even move slowly through empty space (when two enemies are circling each other in a certain way).")},
        {NULL, NULL, O_NONE, N_("Magic walls often have a fairly strict time limit, some more than others. Collect up as many stones as you can just above the magic wall, leaving one strip of mud, and then finally remove this strip and watch the goods get delivered. Just make sure you've cleared an appropriate amount of space under the wall ;)")},
        {NULL, NULL, O_NONE, N_("Voodoo dolls need to be protected from enemies at all costs, but dropping a stone on one is usually harmless!")},
        {NULL, NULL, O_NONE, N_("You can't collect diamonds which are falling, but you can collect them when they momentarily bounce off of something or down the side of a pile.")},
        {NULL, NULL, O_NONE, N_("Some levels have hidden exits. These always look like titanium wall, but don't flash. You can always tell where they are by visual clues and deduction.")},
        {NULL, NULL, O_NONE, N_("Don't blindly take all diamonds. Some of them are red herrings, some may be unobtainable or part of a trap, and believe it or not, sometimes a diamond is more useful to you on the screen than it is collected, due to some sadistic puzzles :)")},
        {NULL, NULL, O_NONE, NULL},

        {GD_ICON_KEYBOARD, N_("Keys to control the player"), O_NONE,
N_("To play the game, press the New Game button. You can select which level you start playing at. During the game, you can control your player with the cursor keys. The Ctrl key has a special meaning: you can snap items, ie. pick up things without moving. If you get stuck, press Escape to restart the level. If there are too many players in the cave and you cannot move, pressing F2 causes the active one to explode. With F11, you can switch to full screen mode. To view the alternative status bar which show keys and skeletons collected, hold down the left shift button.\nThese are the game elements:")},
        {NULL, NULL, O_NONE, NULL},

        {GD_ICON_SNAPSHOT, N_("Snapshots"), O_NONE, N_("You can experiment with levels by saving and reloading snapshots. However, if you are playing a reloaded cave, you will not get score or extra lives.")},
        {GD_ICON_REPLAY, N_("Replays"), O_NONE, N_("Every time you play a game, GDash records all your movements. These recordings can be viewed later, and can be saved with the caveset. To check them out, click on Show replays in the Play menu.")},
        {NULL, NULL, O_NONE, N_("If you were very lucky in a cave, or something interesting happened, you do not have to be worry, as all played caves are recorded. In the Replays window, you can select some of them to be saved with the caveset. You can also add comments to selected movies. The replays are stored no matter if the cave was solved or not, so you can even send the recording of your unsuccessful missions for others to discuss.")},
        {NULL, NULL,O_NONE, N_("During the replay of the cave, you can gain control of the replay if you use the usual cursor keys (left, up, etc.) to move. From that point, you can continue playing the cave as if it was a snapshot. You can answer your 'what would have happened if...' questions. Or see if you can do better than the original player!")},
        {NULL, NULL, O_NONE, NULL},

        {GTK_STOCK_SELECT_COLOR, N_("Themes"), O_NONE, N_("The game also supports themes. You can use the installed png file as a template. Cells can have any arbitrary size, not necessarily 16x16 pixels. However, they must be squares, and the image must have an alpha channel (or transparent layer in some graphics editors). If the image has only a small number of colors (fully saturated red for foreground color 1, fully "
        "saturated green for amoeba...), the game will use original C64 colors, different ones for every cave. Whether the png file is interpreted as a true color "
        "image or one with C64 colors, depends on the color values used, and is autodetected. An image file with only #000000, #00FF00 and the like is taken as "
        "a C64 theme.\n"
        "For C64 themes, the meaning of colors are these:\n"
        "- Transparent: you should use it everywhere where there is no drawing.\n"
        "- Black 0x000000: background color.\n"
        "- Red 0xff0000: foreground color 1.\n"
        "- Purple 0xff00ff: foreground color 2.\n"
        "- Yellow 0xffff00: foreground color 3.\n"
        "- Green 0x00ff00: amoeba.\n"
        "- Blue 0x0000ff: slime.\n"
        "- Cyan 0x00ffff: used internally for the editor, will be converted to black pixels around arrows.\n"
        "- White 0xffffff: for the editor; will the color of arrows.\n"
        )},
        {GTK_STOCK_DIALOG_WARNING, N_("Some words of warning"), O_NONE,N_(
            "- Importing may not be complete and correct for all games and engines. There may be some unplayable caves, as older games had no precise timing.\n"
            "- As the game is sometimes changed, highscores may be lost due to the changing checksums generated.\n"
            "- Default values for cave properties are sometimes changed, as the file format evolves. Some properties might change if a caveset is loaded, "
                "which was saved with an older version. You can use the 'Remove all unknown tags' option in the editor menu to get rid of older or unknown options.\n")},
};


/********
 *
 * HELP FOR EDITOR
 */

static const struct helpdata editorhelp[] = {
    {NULL, NULL, O_NONE, N_("This editor lets you create your own levels and cave sets. It can operate in two modes, a game editor mode, and a cave edit mode.\n")},
    {GTK_STOCK_INDEX, N_("Game editor"), O_NONE, N_("In this one, you are presented with an overview of your game. You can click on any cave to select it. Then you can select File|Edit Cave to view or modify the particular cave. You can also use the standard clipboard actions like cut and paste, also between different games. You can reorder the caves with your mouse, simply by using drag and drop. To create a new cave, select File|New Cave.")},
    {GTK_STOCK_PROPERTIES, N_("Cave editor"), O_NONE, N_("In this mode, you can edit a cave.")},
    {NULL, N_("How a cave is generated"), O_NONE, N_("A cave is built up of different objects. First, it is filled with random elements, of which there can be five. The probabilities of each can be set. (This random data can be substituted by a cave map, which was required for the ability to import different file formats, used by other games.)")},
    {NULL, NULL, O_NONE, N_("After this step, series of cave objects are rendered over the random data, which can be of various types: points, lines, rectangles and so. These are the following:")},
    {GD_ICON_EDITOR_POINT, N_("Point"), O_NONE, N_("This is a single element. Click anywhere on the cave map to create one.")},
    {GD_ICON_EDITOR_FREEHAND, N_("Freehand"), O_NONE, N_("This is a freehand editing tool, which places many points as you click and drag the mouse. Use it wisely; lines and other drawing elements are more simple and the resulting cave is easier to edit.")},
    {GD_ICON_EDITOR_LINE, N_("Line"), O_NONE, N_("Click on the map to select the start point, then drag the mouse and finally release the button, to set the end point.")},
    {GD_ICON_EDITOR_RECTANGLE, N_("Outline"), O_NONE, N_("Click on the map and then drag the mouse, to define the two corners of the rectangle.")},
    {GD_ICON_EDITOR_FILLRECT, N_("Rectangle"), O_NONE, N_("Similar to the above, but this is filled with a second element.")},
    {GD_ICON_EDITOR_RASTER, N_("Raster"), O_NONE, N_("This one is like a filled rectangle, but the horizontal and vertical distance of the elements can be changed. Use the object properties dialog to set the distances after creating the raster.")},
    {GD_ICON_EDITOR_JOIN, N_("Join"), O_NONE, N_("This one is tricky. A join object scans the map, from top to bottom, searching for a specific element. If it finds one, it draws the second element, in the given distance. This can be used, for example, if you create a cave, where every diamond is guarded by a creature. To create one, select the two elements from the combo boxes above the cave map. Click anywhere on the map, and then drag the mouse to set the distance. Note that if the join object finds nothing during its scan, it still exists, and by reordering the elements it can be made visible. Also keep in mind that by connecting the same element (for example connecting a diamond to every diamond), elements may multiply. This effect was used by many older caves to create identical cave parts.")},
    {GD_ICON_EDITOR_FILL_BORDER, N_("Fill to border"), O_NONE, N_("This tool places a flood fill object. The object will fill an area of any shape in the cave with a specific element. The border of the area is set by another element in the cave. Use this tool, for example, if you want to fill an irregular shaped box of brick wall with space. Make sure that the boundary of the area to be filled is set by objects, not random data; otherwise it might fill the whole cave for different random seed values.")},
    {GD_ICON_EDITOR_FILL_REPLACE, N_("Fill by replacement"), O_NONE, N_("This tool places another kind of fill object. This one will replace an element with another one; "
    "the area in which this replacement takes place must be continuous. Use this tool, for example, if you want to replace a continuous area of dirt with diamonds. "
    "You only have to set the new element; the one to be found is selected automatically when you click on the map to place the object.")},
    {GD_ICON_EDITOR_MAZE, N_("Maze"), O_NONE, N_("You can use random generated mazes in cave designs. The walls and paths of the maze can be made from any freely chosen element. Also you can select 'No element' to skip drawing; this way, you can have randomly placed diamonds in a maze, for example. The random seed value determines the shape of the maze. For positive values, the same maze is generated every time the cave is played. If the seed value is -1, the maze is always different.")},
    {GD_ICON_EDITOR_MAZE_UNI, N_("Unicursal maze"), O_NONE, N_("The unicursal maze is a long and curvy path.")},
    {GD_ICON_EDITOR_MAZE_BRAID, N_("Braid maze"), O_NONE, N_("The maze like that in PacMan: there are no dead ends.")},
    {GD_ICON_RANDOM_FILL, N_("Random Fill"), O_NONE, N_("This tool can be used to fill a part of a cave with random elements. It is similar to the random cave setup. At most five elements can be specified. You can also set a replace element; in that case, only that one will be changed to the randomly chosen ones. This can be used to fill the paths of a maze or the border of the cave with random elements. If you are statisfied with the size and position of the randomly filled area after placing, click the 'Object Properties' button to setup its elements. The random seed values can be specified independently for each level. You can also set them to -1, so the cave will be different every time you play.")},
    {GTK_STOCK_COPY, N_("Copy and paste"), O_NONE, N_("This tool is simple: copies a rectangular part of the cave, and pastes it into a new location. The source and destination area may overlap. To select the area to be copied, use the copy and paste tool and then click and drag the mouse. The paste object immediately appears at the same location; the move tool can be used to move it to its final place. The contents of the rectangle can also be mirrored horizontally or flipped vertically: open the object properties window to set this behavior.")},
    {GTK_STOCK_SELECT_COLOR, NULL, O_NONE, N_("To select an element, you can middle-click any time on the cave map to pick one you already use. Use Ctrl together with middle-click to pick a fill element. With Shift and middle-click you can pick an object type from the cave.")},
    {GD_ICON_EDITOR_MOVE, N_("Managing cave objects"), O_NONE, N_("Use this tool to modify already existing cave objects.")},
    {NULL, NULL, O_NONE, N_("By looking at the cave, you can see that every object is drawn with a slight yellowish color to distinguish them from random data. Click on any object to select it.")},
    {NULL, NULL, O_NONE,
        N_("A selected object can be repositioned with the mouse by clicking and dragging. You can resize lines and rectangles by moving them by "
        "their end points or corners. Dragging any other part of these objects moves the whole thing. For joins, you can set "
        "the distance of the added elements this way. The origin of the flood fill objects is marked with an X, if you select them to edit. ")},
    {NULL, NULL, O_NONE, N_("By double-clicking on an object, or selecting object properties from the menu, a dialog pops up, which shows its parameters that you can modify.")},
    {NULL, NULL, O_NONE, N_("The order these objects are drawn also affects the cave. To reorder them, you can click on the To top and To bottom menu items. The object list on the right hand side can also be used to change the order cave objects are drawn. You can also delete them, or use the standard cut, copy and paste operations.")},
    {GTK_STOCK_PROPERTIES, N_("Cave properties"), O_NONE, N_("To view cave properties, select Edit|Cave properties from the menu. A dialog will pop up with many different options. Those are not explained here; most of the settings also have a long explanation, which shows up if you point to them with your mouse.")},
    {GTK_STOCK_CLEAR, NULL, O_NONE, N_("If you want to restart editing, all cave objects can be deleted at once. A cave map can also "
        "be deleted by selecting Remove map from the menu.")},
    {NULL, NULL, O_NONE, N_("Cave objects can be merged into a single map. If you designed a new cave, this has no particular use; but for editing an imported, map-based cave, it might be useful. If you need this behaviour, choose Convert to map from the menu. (It might be useful if you want to load your cave in another application, which does not support BDCFF cave objects.)")},
    {GD_ICON_RANDOM_FILL, N_("More on random cave data"), O_NONE,
        N_("The elements which fill the cave initially are not really random. "
           "They are generated using a predictable random number generator, which can come up with the same series of number "
           "every time. Therefore the cave looks the same every time. The generator is configured by a seed number, which can be "
           "set in the cave random setup dialog. Note that in this way, five different levels for each cave can easily be created! "
           "Each of the levels will be a bit different, because they are filled with different random data. But the main challenge "
           "will be the same, as it is defined by the drawing object in essence. The level at which the cave is shown can be "
           "changed by the scale on the top right corner of the editor window.")},
    {NULL, NULL, O_NONE, 
     N_("A cave can be made totally random, by entering -1 in the random seed entry. Remember that you cannot test "
     "every cave that is generated this way, and there may be for example some diamonds which cannot be collected. If you "
     "enter a negative number to the diamonds needed field, at the start of the game they are counted, and the number you specify is subtracted.")},
    {NULL, NULL, O_NONE, N_(
       "The Edit menu contains a random elements setup tool, which can be used to setup the random number generator for the cave. "
       "It is able to edit all five levels, and updates the cave at every change.")},
    {GTK_STOCK_ZOOM_FIT, N_("Visible region of a cave"), O_NONE,
        N_("Every cave can have a rectangular area, which may be smaller than the cave itself, and will be visible during the game. "
        "Cave elements outside this visible area, for example stones or creatures, also move. "
        "You can also use the Auto shrink tool to set this size automatically by checking "
        "steel walls and inbox/outbox elements.")},
    {GTK_STOCK_GO_FORWARD, N_("Shift cave map"), O_NONE,
        N_("If the cave is map-based, you can use the shift tools to move the map. This might be useful if you want to enlarge it "
        "and otherwise there would be no place to do this. Remember to check the visible region of the cave after shifting it in any "
        "direction! For object-based caves, you can select all object at once and move them together.")},
    {GTK_STOCK_FILE, N_("Cave stories"), O_NONE,
        N_("Every cave can have a story associated to it, which will be shown when the cave is played. This story can connect the "
            "caves to each other.")},
    {GD_ICON_IMAGE, N_("Title screen"), O_NONE,
        N_("A caveset can have its own title screen. To add one, click Cave set title image in the File menu. If your image is transparent "
        "(has a transparent layer or alpha channel, the term depends on the graphics editor you use), you can also add a small background "
        "image, which will be tiled and scrolled beneath the big one.") },
    {GD_ICON_AWARD, N_("Highscores"), O_NONE, N_("The editor can also be used to delete highscore files of a game or any of the caves.")},
    {NULL, NULL, O_NONE, N_("GDash uses two mechanisms to store "
        "highscores: it can save them in a separate file (this is done automatically), and it can also save them in the BDCFF file. Separate files are always "
        "used for imported cavesets. When you load a BDCFF file, you have the option to use the highscore list from the file or the one saved automatically in "
        "the configuration directory of GDash.")},
    {GTK_STOCK_MEDIA_PLAY, N_("Test cave"), O_NONE, N_("If you are finished with drawing, use this button to test the cave.")},
    {GTK_STOCK_FLOPPY, N_("Loading and saving"), O_NONE, N_("To save your work, use the File|Save button from the main window. You can save games in a BDCFF file, which is a text format used widely on the Internet.")},
    {GTK_STOCK_FILE, N_("HTML Galleries"), O_NONE, N_("This program is able to save cave sets in a HTML gallery, which you can "
        "put on a web server, so other ones can preview them online. To do this, select File|Save HTML gallery, and select a "
        "file name for the HTML file. The .PNG files will be put in the same directory and with a similar name.")},
    {GTK_STOCK_CONVERT, N_("Converting to a cavepack"), O_NONE, N_("You can convert your individual caves or the complete caveset to a cavepack, which is a file format readable by the Crazy Light Construction Kit, written by LogicDeLuxe. The conversion can be reached from the File menu. The cavepack format is map-based, so there will only be one level (the currently selected one) exported. Be aware, that many elements and effects GDash uses cannot be converted back to the C64 engine. GDash tries to detect these, and after the conversion, it pops up a windows which describes possible mistakes. You do not have to transfer the files to a C64 disk image; emulators (like VICE) are able to load it directly. To create a self-running game on a C64, you can use the 'Link Game' utility from Crazy Light Construction Kit. For further information, refer to the documentation of these applications.")},
};

/* opens a dialog, containing help. */
static void
show_help_window (const struct helpdata *help_text, int lines, GtkWidget * parent)
{
    GtkWidget *dialog, *sw, *view;
    unsigned int i;
    
    /* create text buffer */
    GtkTextIter iter;
    GtkTextBuffer *buffer=gtk_text_buffer_new (NULL);
    gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
    gtk_text_buffer_create_tag(buffer, "heading", "weight", PANGO_WEIGHT_BOLD, "scale", PANGO_SCALE_XX_LARGE, NULL);
    gtk_text_buffer_create_tag(buffer, "name", "weight", PANGO_WEIGHT_BOLD, "scale", PANGO_SCALE_X_LARGE, NULL);
    gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, "GDash " PACKAGE_VERSION "\n\n", -1, "heading", NULL);
    for (i = 0; i<lines; i++) {
        GdElement element = help_text[i].element;
        
        if (help_text[i].stock_id) {
            GdkPixbuf *pixbuf = gtk_widget_render_icon(parent, help_text[i].stock_id, GTK_ICON_SIZE_LARGE_TOOLBAR, NULL);
            gtk_text_buffer_insert_pixbuf(buffer, &iter, pixbuf);
            gtk_text_buffer_insert(buffer, &iter, " ", -1);
            g_object_unref(pixbuf);
        }
        if (element!=O_NONE) {
            gtk_text_buffer_insert_pixbuf(buffer, &iter, gd_get_element_pixbuf_simple_with_border (element));
            gtk_text_buffer_insert(buffer, &iter, " ", -1);
            if (help_text[i].heading == NULL) {
                /* add element name only if no other text given */
                gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, _(gd_elements[element].name), -1, "name", NULL);
                gtk_text_buffer_insert (buffer, &iter, "\n", -1);
            }
        }
        if (help_text[i].heading) {
            /* some words in big letters */
            gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, _(help_text[i].heading), -1, "name", NULL);
            gtk_text_buffer_insert(buffer, &iter, "\n", -1);
        }
        if (help_text[i].description)
            /* the long text */
            gtk_text_buffer_insert(buffer, &iter, gettext(help_text[i].description), -1);
        gtk_text_buffer_insert(buffer, &iter, "\n", -1);
    }

    dialog=gtk_dialog_new_with_buttons (_("GDash Help"), GTK_WINDOW (parent), GTK_DIALOG_NO_SEPARATOR, GTK_STOCK_CLOSE, GTK_RESPONSE_OK, NULL);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
    gtk_window_set_default_size(GTK_WINDOW (dialog), 512, 384);
    sw=gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start_defaults(GTK_BOX (GTK_DIALOG (dialog)->vbox), sw);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW (sw), GTK_SHADOW_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    /* get text and show it */
    view=gtk_text_view_new_with_buffer(buffer);
    gtk_container_add(GTK_CONTAINER(sw), view);
    g_object_unref(buffer);

    /* set some tags */
    gtk_text_view_set_editable(GTK_TEXT_VIEW (view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW (view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW (view), GTK_WRAP_WORD);
    gtk_text_view_set_pixels_above_lines(GTK_TEXT_VIEW (view), 3);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW (view), 6);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW (view), 6);
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);
}

void
gd_show_game_help(GtkWidget *parent)
{
    show_help_window(gamehelp, G_N_ELEMENTS(gamehelp), parent);
}

void
gd_show_editor_help(GtkWidget *parent)
{
    show_help_window(editorhelp, G_N_ELEMENTS(editorhelp), parent);
}


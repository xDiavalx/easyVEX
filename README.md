![easyVex logo](https://github.com/xDiavalx/easyVEX/blob/master/icon/easyVex1.0%20128.png)

EasyVEX
======

### Purpose:
EasyVex is a library of helper functions and classes for Vex. Vex is a scripting language in Houdini (https://www.sidefx.com/).
Each .h-file contains different types of functions.
## easyVex.h:
Combines all other parts of the library.
## easyVexGeneral.h:
Contains a series of uncategorized helper functions for reoccuring tasks. For example, a function that removes duplicate values from an array and one that calculates the angle between two vectors.
## easyVexGeo.h:
Contains functions that generate or modify geometry. For example, a function that creates a circle with UVs.
## easyVexEdges.h:
Contains a class "edgeStruct" that describes a geometry edge and various functions for it. It is intended to be more intuitive than the use of hedges.
## easyVexLines.h:
Contains a class "lineStruct" that describes a mathematical line and various functions for it. The line can be defined as infinite, finite on either end, or as a line segment. Helper functions allow you to mathematicaly analyse lines. For example, you can get the intersection position and or shortest distance between two lines.
## easyVexPlanes.h:
Contains a class "planeStruct" that describes a mathematical plane and various functions for it. Helper functions allow you to mathematicaly analyse the plane in combination with the lineStruct and others. For example, you can get the intersection position and or shortest distance between a plane and a position.

### WARNING: This project is still under development. Major changes to naming and parameter conventions are still possible.

### License and ownership:
## License:
The License allows you to do pretty much anything you want with this code (http://unlicense.org/). 

## Credits and contributions:
Author: Dimitri Shimanovskiy

Generally I try to credit contributers. I will probably change the way I do that in the near future.

You don't have to mention me when you use this stuff, but I appreciate it if you do. Please send me a message to dimitri.shima.dev@gmail.com or on Github, if you mention me somewhere, want to thank me, want to collaborate, or anything like that.

Please contribute to this project!

Tell me what I am doing wrong.

Tell me how I can improve the code.

Tell me how I can improve performance.

Add and suggest new functions.

I want to learn from you!

### Installation:

## A short introduction to Git:
For beginners I recommended the following process. This has been tested under Windows with a Firefox browser. Please consult other guides for more in-depth instructions.

** Step A: Make a github account at github.com.

** Step B: Make sure you are logged in at github.com with your internet browser of choice.

** Step C: Download and install GitHub Desktop.

** Step D: Log into your GitHub Desktop application with your github.com account.

** Step E: Use your browser to navigate to the desired package on github.com. In our example: 
https://github.com/xDiavalx/easyVEX

** Step F: Press on the green button and click "Open with GitHub Desktop".
![tutorial github button](https://github.com/xDiavalx/easyVEX/blob/master/Tutorial/Install/Github_green_button.png)

** Step G: Your browser will prompt you to allow github.com to open links of this type with the associated app (GitHub Desktop). Allow this to happen and open the link in GitHub Desktop.

** Step H: Github Desktop will prompt you to clone (that means download) the repository. At that point you will be able to choose where on your hard-drive it should be stored. See the instructions below for more information on that.

** Step I: In GitHub desktop you can press "Fetch origin" or "Pull" to update to the latest version of the repository.

## Download and install:
** Step 1: Download the library to anywhere on your harddisk.

** Step 2:
Go to:
`$HOUDINI_USER_PREF_DIR\packages` 

You can find out what that means by opening Houdini, click File -> Open...
Then paste $HOUDINI_USER_PREF_DIR into the search bar, rightclick on "Look in" and click "Expand Path"
![tutorial expand path](https://github.com/xDiavalx/easyVEX/blob/master/Tutorial/Install/expand_path.png)

In windows this should resolve to:

[USER] - Your windows user name

[VERSION] - Your major Houdini release version. For example: 17.0, 17.5, or 18.0

`C:\Users\[USER]\Documents\houdini[VERSION]\packages`

** Step 3: Create the "packages" subfolder if it does not exist, yet.

** Step 4: Copy paste the easyVEX.json file from the easyVex download directory into the packages folder. 

** Step 5: Open the easyVEX.json with a text editor.

** Step 8: Replace C:/[MY_PATH]/ with the path to your easyVEX download directory.

In my case that would make it look like this:

""" {
	"env": [
		{
			"EASYVEX": "C:/Projects/easyVEX/"
		},
	],
	"path": "$EASYVEX"
} """

You need to close and open Houdini so Houdini registers the package.

### How to use:
When you write VEX code and want to use easyVex functions, just type the following line at the top of your wrangle: 
`#include "easyVex.h"`

Then you can just use functions and classes defined in the easyVex.h file.
Check easyVex_Demo.hiplc for a few examples.

### Documentation:
There is an automatically generated code documentation.
Open:
\easyVexDocs\html\index.html
in a browser of choice.

Then go to Files/File List/easyVex.h and you will get a full overview of all functions, structs and the sturct's functions!

### Legal notice:
This software is provided AS-IS, with absolutely no warranty of any kind, express or otherwise. We disclaim any liability for damages resulting from using this software.

Enjoy! XD

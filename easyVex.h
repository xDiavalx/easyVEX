#ifndef __easyVex_h__
#define __easyVex_h__

/**
 * Includes all parts of easyVex
 */

//#include "tester.h"
#include "easyVexGeneral.h"
#include "easyVexGeo.h"
#include "easyVexEdges.h"
#include "easyVexLines.h"
#include "easyVexPlanes.h"

/*
* This Software was originally developed by Dimtiri Shimanovskiy.
* Feel free to use as you wish (http://unlicense.org/). 
* Feedback is highly appreciated.
* Giving credit is requested and appreciated.
* If you credit me in a project, please tell me (via dimitri.shima.dev@gmail.com), so I can find out!
* 
* Contributers:
* Matthew Hendershot
* bhenriksson (https://github.com/bhenriksson031/easyVEX_beh)
* Kyro from Think Procedural (Discord) - helped with a bug in circle
*
* 
* License:
* This is free and unencumbered software released into the public domain.
*
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.
*
* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* For more information, please refer to <http://unlicense.org/>
*
*
* NAME:	easyVex.h (VEX)
*
* COMMENTS:	This include file contains functions to improve quality of life and geometry editing.
*
* Instrcutions:
* 1. Put the easyVex.h file into 
* $HOUDINI_USER_PREF_DIR/vex/include/
* Just create the folders, if they don't exist already.
* 2. Type
* #include "easyVex.h"
* in the wrangle to be able to use the functions.
* If the file is in a subfolder it will be something like:
* #include "subfolder/easyVex.h"
* 
* 
* 
* DESIGN CHOICES
* 
* Structs and functions:
* Usually an input parameter is the first input. 
* (example: point(0,"P",@ptnum) //0 is the input)
* If a function is defined inside the Struct definition the first paramater will be the Struct.
* To uphold convention, we put such functions outside the struct defintion.
* 
* -So what goes into the Struct defintion?
* It should probably only contain the most basic getters, setters and trivial operations.
* But I am not sure where the line is, yet.
*
* Functionnames:
* When possible override similar functions of existing name. 
* But instead of srcpoint and dstpoint we use pointa and pointb.
* When returning an array the name should include a plural "s". Example: getints() 
* Suffix _n stands for normalized output
* Suffix _d stands for degrees (as opposed to radians)
* Function-names are subject to change at the current stage of development.
*/

//General utility functions

//Function mappings //That doesn't work properly
//#define pointp(inp,pn) point(inp,"P",pn) //That doesn't work properly

#endif


## your_font
This is an indipended project included in *cub3d*, the 42-common-core RayCasting project. It's a font renderer library for other CPU drawing libraries (like MinilibX).
<br>
Designed and realized by Tommaso Piana Agostinetti.

### Contents
 - source code in C to create the yft library
 <!-- - man pages (in `man/` directory) -->
 <!-- - a **test** program (in `test/` directory) is built
   with the library -->
 - 1 default **font** (in `fonts/` directory) is included
 - a public include file **yft.h**

### Requirements
 - gcc
 - make

```bash
sudo apt-get install gcc make #(Debian/Ubuntu)
```

### How to compile
Run `make` in the root folder


### Installation
No installation script is provided. You may want to install
- **yft.a** in `/usr/local/lib`
- **yft.h** in `/usr/local/include`
<!-- - **man/man3/yft*.3** `/usr/local/man/man3` -->


## How to use your_font

The user must implement a 'pixel_put' function with this prototype
```c
void	pixel_put(t_img img*, unsigned int x, unsigned int y, unsigned int color);
```
This function will be used by the library to draw each pixel of the font on the image.
Then a font can be loaded with a [yft_is_better](#functions) call. If the font is correctly parsed it can be accessed via [yft_string_put](#functions) to write on the image.

The library exposes a structure and two functions:

### Structure(s)

```c
typedef struct s_img
{
	void	*img_ptr;
	void	*pre_loaded;
	int		width;
	int		height;
}				t_img;
```
This wrapper for the external library image provides all that's needed for *your_font* to operate. *img_ptr* and *pre_loaded* aren't used internally by the library, they are for the user to access inside the *pixel_put* implementation.

### Function(s)

```c
int		yft_is_better(const char *path);
```
Loads the font from the specified path. The format is JSON-like with C-like comments\* (e.g. '//' or '/\* \*/'). The whole file is converted into a oneliner after removing each comment. On a successful call the function will return 0, a positive integer otherwise:
- 1: Font limit *(only *MAX_FONTS* (default: 10) fonts can be stored at the time)*
- 2: Parsing error
- 3: Error while reading the file *(malloc failure, missing file/permissions)*
- 4+: Internal errors

\* *More about it in the [Format](#the-yft-format) section.*

---
<br>

```c
int		yft_string_put(t_img *img,
			void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
			unsigned int x, unsigned int y, const char *string, const char *font_name);
```
Attempts to write on the image passed (wrapped in t_img), using the **pixel_put** function. If no font was loaded an error 'yft: Font not found\n' will be written on the standard error. If the **string** pointer is NULL the function will fail silently. If the string contains a character not included in the font the character will be omitted. Omitted characters will not be filled with the background specified color.


## The .yft format

The .yft format is a plain-text file and it's designed to be easily verified by hand. Each character has it's own portion of the file and it's drawn in a grid, mimicking what will be seen on the screen.

### Comments

*Comments* can be added inside the .yft format.
- The double-slash syntax **'//'** excludes the whole line from the file.
```c
// this is a comment
```
- The slash-star syntax **/\* \*/** excludes a region of file
```c
ascii=65, /* also this is a comment */
{
	...
```

The caracter that will removed from the file while parsing are the one verified by the isspace(3) function or the ones inside a comment. The whole so is clamped in a single line before parsing, multi-line is incentivised for better readability.

### Structure

The .yft format is structured in **blocks**. A block is confined inside curly brackets.
<br>
Each block can contain one or more **directives**. A directive is like a variable with an unspecified type. Each directive inside a block is separated by a comma `,`.
<br>
The syntax is `<name> = <value>` where `value` can be `16` or `"yellow"`.
<br><br>
Three types of blocks exist: the [Definition](#definition-block) block, the [Character](#character-block) block and the [Glyph](#glyph-block) block.

### Definition block

The Definition block it's unique and must be the first block of the file. If multiple or none Definition block are found or the Definition block isn't at the beginning of the file, `yft: Invalid definition block` will be written on the standard error and the font will fail to load.
<br>
The Definition block contains at least 4 directives:
- The **font** directive: specifying the name of the font (between dquotes, e.g. "MyCoolFont")
- The **width** directive: specifying the width of each character.
- The **height** directive: specifying the height of each character.
- The **space** directive: specifying the spacing between each character.
- The **color** directive: specifying the number of colors used in the font.

The colors' definition is also inside the Definition block, right after the `color` directive.
The syntax used to define a color is the following: `"<ascii> c <hexa>"`, where `ascii` is the ascii character used to identify that color in the characters glyph, and `hexa` is the hexadecimal representation of the color, like `0xffffff` for white or `0xff0000` for red. `Void` it's also a valid hexa, it indicates that the background shouldn't be filled with any color.

Below an example of a valid definition block.
```c
{
	/* This is a valid definition block */
	font = "MyCoolFont",
	width = 4,
	height = 3,
	space = 0,
	colors = 4,
	"` c Void",
	"$ c 0xff20ac", // 0x0f213f <-- also this is nice
	"= c 0xa0ffa2",
	"0 c 0xff00c3"
}
```

### Character block

The Character block contains the definition of a single character. It must contain the **ascii** directive which specifies the ascii value it wants to represent, e.g. `ascii=97` for the lowercase `a`. The `ascii` directive must be at the top of each Character block. If two Character block containing the same `ascii` directive are found, `yft: Multiple definition of <ascii>` will be written on the standard error and the font will fail to load.
<br>
The Character block then contains a child block called the Glyph block.

### Glyph block

The Glyph block contains *strings* of character each one representing a row of the character glyph. Each string should contain exactly **width** characters (as specified in the **width** directive inside the Definition block). Each string is separated from each other by a comma `,`. There must be exactly **height** strings inside each Glyph block (as specified in ... you get it).
<br>
This is the 'string' syntax: `"<ascii><ascii><ascii>..."`.

Below an example of a valid Character + Glyph block.
```c
{
	/* this is the Character block of the letter 'A' */
	ascii=65,
	{
		"`$=`",
		"$0`=",
		"$``=",
	}
}
```
---
<br>

>That's pretty much it, go and draw your font.

— Tommaso Piana Agostinetti - 2026-02-08 -
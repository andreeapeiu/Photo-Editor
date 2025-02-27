## Copyright Peiu Andreea, Group 324CA

### Photo-Editor

### -ALGORITHM-

The presented source code contains basic functions for editing images.  
The algorithm reads the command from the file and splits it into words using the
`strtok` function. Then, it relies on decision structures to apply the
modifications read from the keyboard, displaying error messages if necessary.
The algorithm uses nested data structures to store image information more
easily. The `apply` function is designed similarly to the `main` function,
separating its parameter according to which the filter selection is made.

Images are loaded into memory with the `loading` function, which checks whether
the file is binary or text. It uses specific I/O functions to read the input data
and load them into memory. Similarly, the save function checks whether the
keyboard parameter is `"ascii"` or not, then saves the file, changing its type
accordingly. Image trimming is done by the `crop` function, which also checks,
like the other functions, whether an image is loaded into memory or not and
whether the selection data is valid.

Each command that uses dynamic allocation also includes defensive programming to
better handle any errors that may occur. The structure contains two verification
parameters, namely `img.loaded` and `img.selected_with_function`. If
`img.loaded` is 1, there is an image loaded in memory that can be used.
Otherwise, the message `"no image loaded"` is displayed when attempting to run a
command. Similarly, for the `select` function, if a portion is selected,
`img.selected_with_function` is 1.

The function `verify_number` checks whether the string `p` contains numeric
parameters or invalid commands. If they are numbers and all 4 coefficients are
present, the function `parse_assign_coord` converts them from `char` to `int`
using `atoi` and passes them as parameters to `sel`, which performs the
selection.

### -COMMAND ANALYSIS-

The algorithm uses the `strtok` function to split the command into keywords and
parameters. Based on these elements, decisions are made using `if-else`
statements, ensuring the correct interpretation of each command and the
execution of the associated action.

### -FUNCTIONALITY-

I have created custom libraries: `functions.h`, `apply.h`, `image_utils.h`,
`rotate.h`. I wrote a function for each command, and each command is further
modularized into smaller functions.  
I created functions for memory allocation and deallocation, to simplify reading
and writing to a file, and to check whether the input data is valid. Thus, the
program input is made more straightforward.

### -EFFICIENCY-

The program is efficient regarding memory usage, because it frees memory when it
is no longer needed. Furthermore, I only allocated the necessary memory for a
grayscale matrix or a color matrix, depending on the image type. The color
matrix is designed such that each pixel has `r`, `g`, `b` values, making it
easier to modify. I chose not to use three separate matrices because this way
the code is easier to modularize.

### -DATA STRUCTURES-

Image data is stored in data structures that allow efficient management of
information about the image type, dimensions, selection coordinates, and pixel
data. The program uses the following data structures:

- **Structure `image`**: Stores information about the image, including:
  - Image dimensions: `width` and `height`.
  - Image type: P2, P5, P3, or P6.
  - Pixel matrix:
    - For grayscale images: A two-dimensional array of type `int**`.
    - For color images: A two-dimensional array of `color_rgb` structures.
  - Current selection in the image:
    - `x1`, `y1`: Coordinates of the top-left corner of the selection.
    - `x2`, `y2`: Coordinates of the bottom-right corner of the selection.

- **Structure `color_rgb`**: Used to represent a color pixel, containing:
  - `r`: Red color channel value.
  - `g`: Green color channel value.
  - `b`: Blue color channel value.

ImageResizer
============

An c++ program to resize an image with anti-aliasing using multiple filters.

Users stories
--------------
- Choose the filter type: gaussian, mitchell, hamming, and hann, triangle (tent), and box.
- Choose algorithm to fill up border: zero, freeze and circular.
- Handle negative scale factors. A negative scale should reflect as well as resize

![Image Alt](/Assignment3_ImageResizer/demo/1.png)
- Original Photo

![Image Alt](/Assignment3_ImageResizer/demo/8.png)
- Double image with negative parameter.

![Image Alt](/Assignment3_ImageResizer/demo/pooh.png)
- Original Photo

![Image Alt](/Assignment3_ImageResizer/demo/pooh_border_circular.png)
- Double zoom in image with circular algorithm.

![Image Alt](/Assignment3_ImageResizer/demo/pooh_box.png)
- Double zoom in image with using Box filter.

![Image Alt](/Assignment3_ImageResizer/demo/pooh_gaussian1.png)
- Double zoom in image with using Gaussian at width 1.

![Image Alt](/Assignment3_ImageResizer/demo/pooh_gaussian4.png)
- Double zoom in image with using Gaussian at width 4.

![Image Alt](/Assignment3_ImageResizer/demo/pooh_hamming.png)
- Double zoom in image with using Hamming filter.

![Image Alt](/Assignment3_ImageResizer/demo/pooh_hann.png)
- Double zoom in image with using Hann filter.

![Image Alt](/Assignment3_ImageResizer/demo/pooh_lanczos.png)
- Double zoom in image with using Lanczos filter.

![Image Alt](/Assignment3_ImageResizer/demo/pooh_mitchell.png)
- Double zoom in image with using Mitchell filter.

![Image Alt](/Assignment3_ImageResizer/demo/pooh_triangle.png)
- Double zoom in image with using Triangle filter.

# Compilation
To compile, if you are using Ubuntu 12.04 or later. Uncomment //for ubuntu in the Makefile and comment out //for other system. And run the "make" command from the console.

#How to run
From the console, run"./main", you will see a window popping up with grids of black and white squares. Input dummy command with parameters.

"read test.cli" tests all dummy command at one time.

# x86-Fun
Amalgamation of a few assembly routines I did for fun many years back (2010-ish). It is not intended to be comprehensive. May or may not be amended. As is in the name, all for "fun." :)

I had learned both Sobel and Laplace edge detection algorithms and initially implemented them in C, as well as a color conversion to greyscale. I then began incremental improvements, first converting the function to inline assembly, and then moving up the various SIMD instruction sets available to my hardware at the time. I benchmarked each version to measure improvements.

Some used prefetch hints; I also tried a color variant on the algorithms, as there is a small space among green and red values that produce identical greyscale values.

I would be interested in seeing how this runs on my current hardware (Threadripper 2950 vs. Pentium ???) and seeing further improvements using AVX and AVX2 which were not available at the time when I first wrote these.

### References:

[Instruction Metrics per CPU Architecture](http://agner.org/optimize/instruction_tables.pdf)

[Intel Instruction Set Reference Vol 2: A,B,C,D](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-instruction-set-reference-manual-325383.pdf)

## What

Benmarks for the "divide up to power of 2" problem:

http://stackoverflow.com/questions/40431599/efficiently-dividing-unsigned-value-by-a-power-of-two-rounding-up

## Building

    make

## Adding an algorithm

Add both `uint32_t` and `uint64_t` variants just like the existing algorithms in `algos.h`, and add your function to the
`X_MARCO` list in `allx.h`. That should be it.


# Haskell implementation: the mathematical approach

**Authors:** Baptiste Joubert, Julien Albinet

Educational code, not for protecting real data. See the [root README](../README.md) for build instructions and tests.

## Files

### Group.hs and Anneau.hs
Define the `Groupe` and `Anneau` (group and ring) type classes. They helped us understand classes and instances before writing `Corps.hs`, which is central because all the mathematics of the project takes place in sets of polynomials with coefficients in fields.

### Corps.hs
Defines the `Corps` (field) class, used to define the operations needed by AES.

### ZsurNZ.hs
Defines the types `Z_sur5Z` and `Z_sur_6Z` with their inverse and addition. These examples were later used to build the field `Z_sur2Z`.

### Z_sur_2Z.hs
Defines the field `Z_sur_2Z`, later used to represent bits (1 or 0). It is declared as a field rather than a group because polynomials and AES need the full set of field operations (addition, multiplication, inverse, equality).

### Polynome.hs
Defines the type `Pol`, simply a list of `a`, with the lowest-degree term first (e.g. 2x² + 1 is `[1, 0, 2]`), which made the operations simpler to write. Polynomials are an instance of ring (addition, negation, multiplication), with the extra constraint that coefficients live in a field, so field functions can be reused. The file also contains helpers such as `take_last` and `cut_last`, and `algo_euclide`, the extended Euclidean algorithm used to compute modular inverses. These modular functions are the building blocks of GF(2⁸).

### GF28.hs
Implements the field GF(2⁸). Each byte is represented by a polynomial of degree ≤ 7, i.e. 8 coefficients in `Z_sur_2Z`. The `GF28` type is a polynomial over `Z_sur_2Z`, so the previous mathematical functions apply directly to bytes. A dedicated type is used because polynomials over a field form a ring, while GF(2⁸) is a quotient of that ring.

### AES.hs
Columns are represented as polynomials so that our existing functions apply to them; blocks are lists of columns.

- `SubBytes`: implemented with the multiplication/affine transformation given in FIPS 197.
- `ShiftRows`: moves the elements of the block.
- `MixColumns`: first written as a matrix product, then replaced by a polynomial product (following feedback from our instructor).
- `AddRoundKey`: a polynomial addition.
- `KeySchedule`: three separate functions (128, 192, 256-bit keys) rather than one parametrised function, for simplicity.

The inverse functions are in this file too, along with `hextobin` / `bintohex` helpers that make blocks easier to read and to write tests with.

### Cypher.hs
The two top-level functions, `cypher` and `inv_cypher`, which encrypt and decrypt a block using everything above.

## Running the tests

```bash
ghci Cypher.hs
ghci> :script test_Cypher.ghci
```

## Retrospective

We ran into organisation problems: sometimes we both worked on the same thing, and we misjudged the workload between sessions. We also did not always communicate progress or update our logbook. We improved on these points over time, and applied the lessons in the C part.

# advent-of-code-2023

## Day 1: Trebuchet?!

**Topics:** String manipulation <br>
**Difficulty:** 1/10

## Day 2: Cube Conundrum

**Topics:** String manipulation, Simple math <br>
**Difficulty:** 1/10

## Day 3: Gear Ratios
**Topics:** 2D Array, Indexing <br>
**Difficulty:** 2/10 <br>
**My solution:** <br>
**Part 1:** Iterate through the grid to find numbers. If found, check around the number to see if there are any symbols. If so, add the number to the sum and return the sum at the end. <br>
**Part 2:** Iterate through the grid to find numbers and check if there are any * around it. Record the location of * and the number. If the location of * is already stored, then it means there was already a number associated with it. Multiply the stored number with the current number and add it to the sum. If the location of * is not stored, then it means this is the first number we found around the *, store the location of * and the current number.

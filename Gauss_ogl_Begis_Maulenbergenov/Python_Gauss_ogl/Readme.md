# Gaussian Elimination Method: Step-by-Step Guide

## Introduction
Gaussian elimination is a mathematical procedure used to solve systems of linear equations. It involves row operations on the augmented matrix to bring it into a row-echelon form. From there, back-substitution is applied to find the solution.

This guide provides a step-by-step walkthrough for solving the following system of linear equations using Gaussian elimination:

```
2x - 3y = -9
3x - 2y = -1
```

We will solve this system by performing five key steps and also visualize the process with slope representations.

### Prerequisites
Ensure the following Python libraries are installed before proceeding:
```bash
pip install pygame PyOpenGL numpy
```

---

## Steps

### Step 1: Draw Initial Slopes
#### Equations:
1. **First equation:** `2x - 3y = -9`
2. **Second equation:** `3x - 2y = -1`

#### Range:
We use the range \([-8, 8]\) for \(x\). By substituting the minimum and maximum values of \(x\), we calculate the endpoints of each slope:

**For the first equation:**
- When x = -8:
   2*(-8) - 3y = -9 -> y = -7/3
- When x = 8:
  2*8 - 3y = -9 -> y = 25/3

Coordinates for the **first slope (red):** (-8, -7/3) and (8, 25/3).

**For the second equation:**
- When x = -8:
 3*(-8) - 2y = -1 -> y = -23/2 -> y = -11.5
- When x = 8:
  3*8 - 2y = -1 -> y = 25/2 -> y = 12.5 

Coordinates for the **second slope (green):** (-8, -11.5) and (8, 12.5).

---

### Step 2: Normalize the First Row
Divide the first row by 2 to normalize it:

**Original matrix representation:**
```
[ 2  -3 | -9 ]
[ 3  -2 | -1 ]
```
**After dividing the first row by 2:**
```
[ 1 -1.5 | -4.5 ]
[ 3  -2  | -1   ]
```
Equation now becomes:
- First row: \(x - 1.5y = -4.5\)
- Second row: \(3x - 2y = -1\)

Since we only scaled the first row, the slope coordinates for the first equation remain unchanged.

#### Eliminate the \(x\) coefficient in the second equation:
Subtract first row from the second row:
\[ 3x - 2y - 3(x - 1.5y) = -1 - 3(-4.5) \]
\[ 2.5y = 12.5 \]

**New matrix representation:**
```
[ 1 -1.5 | -4.5 ]
[ 0  2.5 | 12.5 ]
```

---

### Step 3: Solve for \(y\)
Divide the second row by 2.5:
 y = 12.5 / 2.5 => y = 5 

**Updated matrix:**
```
[ 1 -1.5 | -4.5 ]
[ 0   1  |  5 ]
```

#### Update Slope Coordinates
The second equation now only depends on \(y\). Its slope becomes horizontal:
- Coordinates: (-8, 4) and (8, 4).

---

### Step 4: Eliminate the \(y\) Coefficient in the First Row
Eliminate the y coefficient from the first row by adding 1.5 (second row) to the first row:
\[ x - 1.5y + 1.5y = -4.5 + 1.5(5) \]
\[ x = 3 \]

**Final matrix representation:**
```
[ 1  0 | 3 ]
[ 0  1 | 5 ]
```

---

### Step 5: Final Coordinates
With \(x = 3\) and \(y = 5\), update the first slope to reflect these values. The new slope coordinates are:
- (3, -8)
- (3, 8)

The solution to the system of equations is:
\[ x = 3, y = 5 \]

---

## Summary
1. Install necessary libraries with:
   ```bash
   pip install pygame PyOpenGL numpy
   ```
2. Visualize the system of equations as slopes.
3. Perform Gaussian elimination step-by-step to solve the system:
   - Normalize rows.
   - Eliminate variables.
   - Update coordinates accordingly.

---

### Example Output
**Initial Matrix:**
```
[ 2  -3 | -9 ]
[ 3  -2 | -1 ]
```
**Final Matrix:**
```
[ 1  0 | 3 ]
[ 0  1 | 5 ]
```
**Solution:**
\[ x = 3, y = 5 \]


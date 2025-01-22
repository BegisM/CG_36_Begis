# Gaussian Elimination Method: Step-by-Step Guide

## Introduction
Gaussian elimination is a mathematical procedure used to solve systems of linear equations. It involves row operations on the augmented matrix to bring it into a row-echelon form. From there, back-substitution is applied to find the solution.

This guide provides a step-by-step walkthrough for solving the following system of linear equations using Gaussian elimination:

```
2x - 3y = -14
3x + 2y = 5
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
1. **First equation:** `2x - 3y = -14`
2. **Second equation:** `3x + 2y = 5`

#### Range:
We use the range \([-6, 6]\) for \(x\). By substituting the minimum and maximum values of \(x\), we calculate the endpoints of each slope:

**For the first equation:**
- When x = -6:
   2*(-6) - 3y = -14 -> y = 2/3
- When x = 6:
  2*6 - 3y = -14 -> y = 26/3

Coordinates for the **first slope (red):** (-6, 2/3) and (6, 26/3).

**For the second equation:**
- When x = -6:
 3*(-6) + 2y = 5 -> y = 11.5 
- When x = 6:
  3*6 + 2y = 5 -> y = -6.5 

Coordinates for the **second slope (green):** (-6, 11.5) and (6, -6.5).

---

### Step 2: Normalize the First Row
Divide the first row by 2 to normalize it:

**Original matrix representation:**
```
[ 2  -3 | -14 ]
[ 3   2 |   5 ]
```
**After dividing the first row by 2:**
```
[ 1 -1.5 | -7 ]
[ 3   2   |  5 ]
```
Equation now becomes:
- First row: \(x - 1.5y = -7\)
- Second row: \(3x + 2y = 5\)

Since we only scaled the first row, the slope coordinates for the first equation remain unchanged.

#### Eliminate the \(x\) coefficient in the second equation:
Subtract \(3 \cdot\) (first row) from the second row:
\[ 3x + 2y - 3(x - 1.5y) = 5 - 3(-7) \]
\[ 6.5y = 26 \]

**New matrix representation:**
```
[ 1 -1.5 | -7 ]
[ 0  6.5 | 26 ]
```

---

### Step 3: Solve for \(y\)
Divide the second row by 6.5:
 y = 26 / 6.5 => y = 4 

**Updated matrix:**
```
[ 1 -1.5 | -7 ]
[ 0   1  |  4 ]
```

#### Update Slope Coordinates
The second equation now only depends on \(y\). Its slope becomes horizontal:
- Coordinates: (-6, 4) and (6, 4).

---

### Step 4: Eliminate the \(y\) Coefficient in the First Row
Eliminate the y coefficient from the first row by adding 1.5 (second row) to the first row:
\[ x - 1.5y + 1.5y = -7 + 1.5(4) \]
\[ x = -1 \]

**Final matrix representation:**
```
[ 1  0 | -1 ]
[ 0  1 |  4 ]
```

---

### Step 5: Final Coordinates
With \(x = -1\) and \(y = 4\), update the first slope to reflect these values. The new slope coordinates are:
- (-1, -6)
- (-1, 6)

The solution to the system of equations is:
\[ x = -1, y = 4 \]

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
[ 2  -3 | -14 ]
[ 3   2 |   5 ]
```
**Final Matrix:**
```
[ 1  0 | -1 ]
[ 0  1 |  4 ]
```
**Solution:**
\[ x = -1, y = 4 \]

